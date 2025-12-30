module;
#if defined(LIGHT_PLATFORM_LINUX)
	#include <wayland-client.h>
	#include <xdg-shell.h>
#else
	#error "Unsupported platform"
#endif

import logger;
export module surface.system;
export import :components;
import debug.assertions;
import app.system;
import ecs.registry;
import math.vec2;
import surface.requests;
import memory.reference;
import memory.null_on_move;
import std;

export namespace lt::surface {

class System: public app::ISystem
{
public:
	[[nodiscard]] System(memory::Ref<ecs::Registry> registry);

	~System() override;

	System(System &&) = default;

	System(const System &) = delete;

	auto operator=(System &&) -> System & = default;

	auto operator=(const System &) -> System & = delete;

	void on_register() override;

	void on_unregister() override;

	void create_surface_component(ecs::EntityId entity, SurfaceComponent::CreateInfo info);

	void tick(app::TickInfo tick) override;

	[[nodiscard]] auto get_last_tick_result() const -> const app::TickResult & override
	{
		return m_last_tick_result;
	}

private:
#if defined(LIGHT_PLATFORM_LINUX)
	static void handle_globals(
	    void *data,
	    wl_registry *registry,
	    std::uint32_t name,
	    const char *interface,
	    std::uint32_t version
	);
#endif

	void on_surface_destruct(ecs::Registry &registry, ecs::EntityId entity);

	void handle_requests(SurfaceComponent &surface);

	void handle_events(SurfaceComponent &surface);

	void modify_title(SurfaceComponent &surface, const ModifyTitleRequest &request);

	void modify_resolution(SurfaceComponent &surface, const ModifyResolutionRequest &request);

	void modify_position(SurfaceComponent &surface, const ModifyPositionRequest &request);

	void modify_visiblity(SurfaceComponent &surface, const ModifyVisibilityRequest &request);

	void modify_position(ecs::EntityId surface_entity, const math::ivec2 &new_size);

	void modify_position(ecs::EntityId surface_entity, const math::uvec2 &new_size);

	void set_visibility(ecs::EntityId surface_entity, bool visible);

	memory::Ref<ecs::Registry> m_registry;

	app::TickResult m_last_tick_result;

#if defined(LIGHT_PLATFORM_LINUX)
	memory::NullOnMove<wl_display *> m_wl_display {};

	memory::NullOnMove<wl_registry *> m_wl_registry {};

	wl_registry_listener m_wl_registry_listener {};

	memory::NullOnMove<wl_compositor *> m_wl_compositor {};

	memory::NullOnMove<xdg_wm_base *> m_shell = {};
#endif
};

} // namespace lt::surface

module :private;
namespace lt::surface {

#ifdef LIGHT_PLATFORM_LINUX

void handle_shell_ping(void *data, xdg_wm_base *shell, std::uint32_t serial)
{
	std::ignore = data;

	xdg_wm_base_pong(shell, serial);
}
const auto shell_listener = xdg_wm_base_listener {
	.ping = &handle_shell_ping,
};

void handle_shell_surface_configure(void *data, xdg_surface *shell_surface, std::uint32_t serial)
{
	std::ignore = data;

	xdg_surface_ack_configure(shell_surface, serial);
}
const auto shell_surface_listener = xdg_surface_listener {
	.configure = &handle_shell_surface_configure
};

void handle_toplevel_configure(
    void *data,
    xdg_toplevel *toplevel,
    std::int32_t width,
    std::int32_t height,
    wl_array *states
)
{
	// TODO(Light): handle resizing
}
void handle_toplevel_close(void *data, xdg_toplevel *toplevel)
{
	// TODO(Light): handle quitting
}
const auto toplevel_listener = xdg_toplevel_listener {
	.configure = &handle_toplevel_configure,
	.close = &handle_toplevel_close,
};

void System::handle_globals(
    void *data,
    wl_registry *registry,
    std::uint32_t name,
    const char *interface,
    std::uint32_t version
)

{
	auto *system = std::bit_cast<System *>(data);

	if (std::strcmp(interface, wl_compositor_interface.name) == 0)
	{
		system->m_wl_compositor = std::bit_cast<wl_compositor *>(
		    wl_registry_bind(registry, name, &wl_compositor_interface, 1)
		);
		log::info("Bound successfuly to the wl_compositor global");
	}

	if (std::strcmp(interface, xdg_wm_base_interface.name) == 0)
	{
		system->m_shell = std::bit_cast<xdg_wm_base *>(
		    wl_registry_bind(registry, name, &xdg_wm_base_interface, 1)
		);
		xdg_wm_base_add_listener(system->m_shell, &shell_listener, {});
		log::info("Bound successfuly to the xdg_wm_base global");
	}
}

void registry_handle_global_remove(void *data, wl_registry *registry, std::uint32_t name)
{
	log::trace("Registry global remove:");
	log::trace("\tname: {}", name);
}

System::System(memory::Ref<ecs::Registry> registry)
    : m_wl_registry_listener(
          {
              .global = handle_globals,
              .global_remove = registry_handle_global_remove,
          }
      )
    , m_registry(std::move(registry))
{
	// NOLINTNEXTLINE
	m_wl_display = wl_display_connect({});
	debug::ensure(m_wl_display, "Failed to connect to Wayland display");

	// NOLINTNEXTLINE
	m_wl_registry = wl_display_get_registry(m_wl_display);
	debug::ensure(m_wl_registry, "Failed to get Wayland display's registry");

	// TODO(Light): "this" could be moved around... replace with a pointer to some heap allocation
	wl_registry_add_listener(m_wl_registry, &m_wl_registry_listener, this);
	wl_display_roundtrip(m_wl_display);

	debug::ensure(m_wl_compositor, "Failed to bind to the Wayland's compositor global");
	debug::ensure(m_shell, "Failed to bind to the Wayland's  XDG-shell global");
}

System::~System()
{
	if (m_wl_display)
	{
		log::debug("Closing Wayland display...");
		wl_display_disconnect(m_wl_display);
		log::debug("Closed Wayland display");
	}
	else
	{
		log::debug("Wayland display nulled on move!");
	}
}

void System::on_register()
{
}

void System::on_unregister()
{
}

void System::create_surface_component(ecs::EntityId entity, SurfaceComponent::CreateInfo info)
{
	auto &component = m_registry->add<SurfaceComponent>(entity, info);
	auto &surface = m_registry->get<SurfaceComponent>(entity);
	const auto &resolution = surface.get_resolution();
	const auto &position = surface.get_position();

	auto *wayland_surface = (wl_surface *)nullptr;
	auto *shell_surface = (xdg_surface *)nullptr;
	auto *shell_toplevel = (xdg_toplevel *)nullptr;

	wayland_surface = wl_compositor_create_surface(m_wl_compositor);
	debug::ensure(wayland_surface, "Failed to create Wayland surface");

	shell_surface = xdg_wm_base_get_xdg_surface(m_shell, wayland_surface);
	debug::ensure(shell_surface, "Failed to get XDG-shell surface");
	xdg_surface_add_listener(shell_surface, &shell_surface_listener, {});

	shell_toplevel = xdg_surface_get_toplevel(shell_surface);
	debug::ensure(shell_toplevel, "Failed to get XDG-shell toplevel");
	xdg_toplevel_add_listener(shell_toplevel, &toplevel_listener, {});

	xdg_toplevel_set_title(shell_toplevel, "Wayland Vulkan Example");
	xdg_toplevel_set_app_id(shell_toplevel, "Wayland Vulkan Example");

	wl_surface_commit(wayland_surface);
	wl_display_roundtrip(m_wl_display);
	wl_surface_commit(wayland_surface);

	surface.m_native_data.surface = wayland_surface;
	surface.m_native_data.display = m_wl_display;
}

void System::tick(app::TickInfo tick)
{
}

#endif

#ifdef LIGHT_PLATFORM_WINDOWS
#endif

} // namespace lt::surface
