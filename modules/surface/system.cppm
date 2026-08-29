module;

#include <wayland-client.h>
#include <xdg-shell.h>

export module surface.system;
export import :components;

import preliminary;
import app.system;
import ecs.registry;
import math.vec2;
import input.codes;
import surface.requests;
import logger;
import preliminary;
import surface.constants;
import surface.requests;
import surface.events;
import logger;
import ecs.registry;
import ecs.entity;
import time;

export namespace lt::surface {

class System: public app::ISystem
{
public:
	[[nodiscard]] System(ref<ecs::Registry> registry);

	~System() override;

	System(System &&) = default;

	System(const System &) = delete;

	auto operator=(System &&) -> System & = default;

	auto operator=(const System &) -> System & = delete;

	void on_register() override;

	void on_unregister() override;

	void create_surface_component(ecs::EntityId entity, const SurfaceComponent::CreateInfo &info);

	void tick(app::TickInfo tick) override;

	[[nodiscard]] auto get_last_tick_result() const -> const app::TickResult & override
	{
		return m_last_tick_result;
	}

private:
	static void wayland_registry_listener(
	    void *data,
	    wl_registry *registry,
	    u32 name,
	    const char *interface,
	    u32 version
	);

	static void wayland_seat_capabilities_listener(void *data, wl_seat *seat, u32 capabilities);

	static void wayland_pointer_leave_listener(
	    void *data,
	    wl_pointer *pointer,
	    u32 serial,
	    wl_surface *surface
	);

	static void wayland_pointer_enter_listener(
	    void *data,
	    wl_pointer *pointer,
	    u32 serial,
	    wl_surface *surface,
	    wl_fixed_t surface_x,
	    wl_fixed_t surface_y
	);

	static void wayland_pointer_motion_listener(
	    void *data,
	    wl_pointer *listener,
	    u32 time,
	    wl_fixed_t surface_x,
	    wl_fixed_t surface_y
	);

	static void wayland_pointer_button_listener(
	    void *data,
	    wl_pointer *pointer,
	    u32 serial,
	    u32 time,
	    u32 button,
	    u32 state
	);

	static void wayland_pointer_axis_listener(
	    void *data,
	    wl_pointer *pointer,
	    u32 time,
	    u32 axis,
	    wl_fixed_t value
	);

	static void wayland_pointer_axis_source_listener(
	    void *data,
	    wl_pointer *pointer,
	    u32 axis_source
	);

	static void wayland_pointer_axis_stop_listener(
	    void *data,
	    wl_pointer *pointer,
	    u32 time,
	    u32 axis_source
	);

	static void wayland_pointer_axis_discrete_listener(
	    void *data,
	    wl_pointer *pointer,
	    u32 axis,
	    i32 discrete
	);

	static void wayland_pointer_frame_listener(void *data, wl_pointer *pointer);

	void on_surface_destruct(ecs::Registry &registry, ecs::EntityId entity);

	void handle_requests(SurfaceComponent &surface);

	void handle_events(SurfaceComponent &surface);

	void modify_title(SurfaceComponent &surface, const ModifyTitleRequest &request);

	void modify_resolution(SurfaceComponent &surface, const ModifyResolutionRequest &request);

	void modify_position(SurfaceComponent &surface, const ModifyPositionRequest &request);

	void modify_visibility(SurfaceComponent &surface, const ModifyVisibilityRequest &request);

	ref<ecs::Registry> m_registry;

	app::TickResult m_last_tick_result {};

	null_on_move<wl_display *> m_wl_display {};

	wl_registry *m_wl_registry {};

	wl_registry_listener m_wl_registry_listener {};

	wl_seat_listener m_wl_seat_listener {};

	wl_pointer_listener m_wl_pointer_listener {};

	wl_compositor *m_wl_compositor {};

	xdg_wm_base *m_shell {};

	wl_seat *m_wl_seat {};

	wl_keyboard *m_wl_keyboard {};

	wl_pointer *m_wl_pointer {};

	wl_touch *m_wl_touch {}; // TODO(Light): Add touch support
};

} // namespace lt::surface

namespace lt::surface {

template<class... Ts>
struct overloads: Ts...
{
	using Ts::operator()...;
};

void ensure_component_sanity(const SurfaceComponent &component);

void handle_shell_ping(void *data, xdg_wm_base *shell, u32 serial)
{
	ignore = data;
	xdg_wm_base_pong(shell, serial);
}
const auto shell_listener = xdg_wm_base_listener {
	.ping = &handle_shell_ping,
};
void handle_shell_surface_configure(void *data, xdg_surface *shell_surface, u32 serial)
{
	ignore = data;

	xdg_surface_ack_configure(shell_surface, serial);
}
const auto shell_surface_listener = xdg_surface_listener {
	.configure = &handle_shell_surface_configure
};

void handle_toplevel_configure(
    void *data,
    xdg_toplevel *toplevel,
    i32 width,
    i32 height,
    wl_array *states
)
{
	// @todo(Light): implement

	ignore = data;
	ignore = toplevel;
	ignore = states;
	ignore = width;
	ignore = height;
}

void handle_toplevel_close(void *data, xdg_toplevel *toplevel)
{
	// @todo(Light): implement
	ignore = data;
	ignore = toplevel;
}
const auto toplevel_listener = xdg_toplevel_listener {
	.configure = &handle_toplevel_configure,
	.close = &handle_toplevel_close,
};

void wayland_pointer_leave_listener(
    void *data,
    wl_pointer *pointer,
    u32 serial,
    wl_surface *surface
)
{
	// @wip(Light): implement
	ignore = data;
	ignore = pointer;
	ignore = serial;
	ignore = surface;

	// void *system = std::bit_cast<System *>(data);
}

/* static */ void System::wayland_seat_capabilities_listener(
    void *data,
    wl_seat *seat,
    u32 capabilities
)
{
	ignore = seat;

	auto *system = std::bit_cast<System *>(data);
	const auto have_pointer = capabilities & WL_SEAT_CAPABILITY_POINTER;

	if (have_pointer && !system->m_wl_pointer)
	{
		system->m_wl_pointer = wl_seat_get_pointer(system->m_wl_seat);
		wl_pointer_add_listener(system->m_wl_pointer, &system->m_wl_pointer_listener, system);
		log::info("Added Wayland pointer (0x{:x})", std::bit_cast<size_t>(system->m_wl_pointer));
	}
	else if (!have_pointer && system->m_wl_pointer)
	{
		wl_pointer_release(system->m_wl_pointer);
		system->m_wl_pointer = nullptr;

		log::info("Released Wayland pointer (0x{:x})", std::bit_cast<size_t>(system->m_wl_pointer));
	}
}

/* static */ void System::wayland_pointer_leave_listener(
    void *data,
    wl_pointer *pointer,
    u32 serial,
    wl_surface *surface
)
{
	// @todo(Light): implement
	ignore = data;
	ignore = pointer;
	ignore = serial;
	ignore = surface;

	log::debug("Pointer leave...");
}

/* static */ void System::wayland_pointer_enter_listener(
    void *data,
    wl_pointer *pointer,
    u32 serial,
    wl_surface *surface,
    wl_fixed_t surface_x,
    wl_fixed_t surface_y
)
{
	// @todo(Light): implement
	ignore = data;
	ignore = pointer;
	ignore = serial;
	ignore = surface;
	ignore = surface_x;
	ignore = surface_y;

	log::debug("Pointer enter...");
}

/* static */ void System::wayland_pointer_motion_listener(
    void *data,
    wl_pointer *listener,
    u32 time,
    wl_fixed_t surface_x,
    wl_fixed_t surface_y
)
{
	// @todo(Light): implement
	ignore = data;
	ignore = listener;
	ignore = time;

	log::debug("Pointer motion: [{} - {}]", surface_x, surface_y);
}

/* static */ void System::wayland_pointer_button_listener(
    void *data,
    wl_pointer *pointer,
    u32 serial,
    u32 time,
    u32 button,
    u32 state
)
{
	// @todo(Light): implement
	ignore = data;
	ignore = pointer;
	ignore = serial;
	ignore = time;
	ignore = button;
	ignore = state;

	log::debug("Pointer button");
}

/* static */ void System::wayland_pointer_axis_listener(
    void *data,
    wl_pointer *pointer,
    u32 time,
    u32 axis,
    wl_fixed_t value
)
{
	// @todo(Light): implement
	ignore = data;
	ignore = pointer;
	ignore = time;
	ignore = axis;
	ignore = value;

	log::debug("Pointer axis listener");
}

/* static */ void System::wayland_pointer_axis_source_listener(
    void *data,
    wl_pointer *pointer,
    u32 axis_source
)
{
	// @todo(Light): implement
	ignore = data;
	ignore = pointer;
	ignore = axis_source;

	log::debug("Pointer axis source listener");
}

/* static */ void System::wayland_pointer_axis_stop_listener(
    void *data,
    wl_pointer *pointer,
    u32 time,
    u32 axis_source
)
{
	// @todo(Light): implement
	ignore = data;
	ignore = pointer;
	ignore = time;
	ignore = axis_source;

	log::debug("Pointer axis stop listener");
}

/* static */ void System::wayland_pointer_axis_discrete_listener(
    void *data,
    wl_pointer *pointer,
    u32 axis,
    i32 discrete
)
{
	// @todo(Light): implement
	ignore = data;
	ignore = pointer;
	ignore = axis;
	ignore = discrete;

	log::debug("Pointer axis discrete listener");
}

/* static */ void System::wayland_pointer_frame_listener(void *data, wl_pointer *pointer)
{
	// @todo(Light): implement
	ignore = data;
	ignore = pointer;

	log::debug("Pointer frame...");
}

void seat_name_listener(void *data, wl_seat *seat, const char *name)
{
	// @todo(Light): implement
	ignore = data;

	log::info("Wayland seat:");
	log::info("\tname: {}", name);
	log::info("\taddr: 0x{:x}", std::bit_cast<size_t>(seat));
}

void System::wayland_registry_listener(
    void *data,
    wl_registry *registry,
    u32 name,
    const char *interface,
    u32 version
)

{
	ignore = version;

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
		xdg_wm_base_add_listener(system->m_shell, &shell_listener, system);
		log::info("Bound successfuly to the xdg_wm_base global");
	}

	if (std::strcmp(interface, wl_seat_interface.name) == 0)
	{
		system->m_wl_seat = std::bit_cast<wl_seat *>(
		    wl_registry_bind(registry, name, &wl_seat_interface, 7u)
		);
		wl_seat_add_listener(system->m_wl_seat, &system->m_wl_seat_listener, system);
		log::info("Bound successfuly to the wl_seat_interface global");
	}
}

void registry_handle_global_remove(void *data, wl_registry *registry, u32 name)
{
	// @todo(Light): implement
	ignore = data;
	ignore = registry;

	log::trace("Registry global remove:");
	log::trace("\tname: {}", name);
}

void System::on_surface_destruct(ecs::Registry &registry, ecs::EntityId entity)
try
{
	auto &surface = registry.get<SurfaceComponent>(entity);
	xdg_toplevel_destroy(surface.m_xdg_toplevel);
	xdg_surface_destroy(surface.m_xdg_surface);
	wl_surface_destroy(surface.m_wl_surface);
}
catch (const std::exception &exp)
{
	log::error("Uncaught exception in surface::on_surface_destruct:");
	log::error("\twhat: {}", exp.what());
}

System::System(ref<ecs::Registry> registry)
    : m_wl_registry_listener(
          {
              .global = wayland_registry_listener,
              .global_remove = registry_handle_global_remove,
          }
      )
    , m_wl_seat_listener(
          wl_seat_listener {
              .capabilities = &wayland_seat_capabilities_listener,
              .name = &seat_name_listener,
          }
      )
    , m_registry(std::move(registry))
    , m_wl_pointer_listener(
          {
              .enter = &wayland_pointer_enter_listener,
              .leave = &wayland_pointer_leave_listener,
              .motion = &wayland_pointer_motion_listener,
              .button = &wayland_pointer_button_listener,
              .axis = &wayland_pointer_axis_listener,
              .frame = &wayland_pointer_frame_listener,
              .axis_source = &wayland_pointer_axis_source_listener,
              .axis_stop = &wayland_pointer_axis_stop_listener,
              .axis_discrete = &wayland_pointer_axis_discrete_listener,
          }
      )
{
	m_registry->connect_on_destruct<SurfaceComponent>([this](auto &registry, auto entity_id) {
		on_surface_destruct(registry, entity_id);
	});

	ensure(m_registry, "Failed to construct surface::System: null ecs::Registry");

	m_wl_display = wl_display_connect({});
	ensure(m_wl_display, "Failed to connect to Wayland display");

	// NOLINTNEXTLINE
	m_wl_registry = wl_display_get_registry(m_wl_display);
	ensure(m_wl_registry, "Failed to get Wayland display's registry");

	// TODO(Light): "this" could be moved around... replace with a pointer to some heap allocation
	wl_registry_add_listener(m_wl_registry, &m_wl_registry_listener, this);
	wl_display_roundtrip(m_wl_display);

	// Wayland seat gets named after the second roundtrip....
	// For reasons beyond my fragile comprehension :(
	wl_display_roundtrip(m_wl_display);

	ensure(m_wl_compositor, "Failed to bind to the Wayland's compositor global");
	ensure(m_shell, "Failed to bind to the Wayland's  XDG-shell global");
}

System::~System()
{
	if (!m_wl_display)
	{
		return;
	}

	try
	{
		/** @todo(Light): make registry.remove not invalidate iterators */
		auto entities_to_remove = std::vector<ecs::EntityId> {};
		for (auto &[entity, surface] : m_registry->view<SurfaceComponent>())
		{
			entities_to_remove.emplace_back(entity);
		}

		for (auto entity : entities_to_remove)
		{
			m_registry->remove<SurfaceComponent>(entity);
		}

		m_registry->disconnect_on_construct<SurfaceComponent>();
		m_registry->disconnect_on_destruct<SurfaceComponent>();

		wl_display_roundtrip(m_wl_display);
		wl_display_roundtrip(m_wl_display);
		wl_display_roundtrip(m_wl_display);

		if (m_wl_pointer)
		{
			wl_pointer_release(m_wl_pointer);
			m_wl_pointer = nullptr;
			wl_display_roundtrip(m_wl_display);
		}

		if (m_wl_keyboard)
		{
			wl_keyboard_release(m_wl_keyboard);
			m_wl_keyboard = nullptr;
			wl_display_roundtrip(m_wl_display);
		}

		if (m_wl_touch)
		{
			wl_touch_release(m_wl_touch);
			m_wl_touch = nullptr;
			wl_display_roundtrip(m_wl_display);
		}

		if (m_wl_seat)
		{
			wl_seat_release(m_wl_seat);
			m_wl_seat = nullptr;
			wl_display_roundtrip(m_wl_display);
		}

		if (m_shell)
		{
			xdg_wm_base_destroy(m_shell);
			m_shell = nullptr;
			wl_display_roundtrip(m_wl_display);
		}

		if (m_wl_compositor)
		{
			wl_compositor_destroy(m_wl_compositor);
			m_wl_compositor = nullptr;
			wl_display_roundtrip(m_wl_display);
		}

		if (m_wl_registry)
		{
			wl_registry_destroy(m_wl_registry);
			m_wl_registry = nullptr;
			wl_display_roundtrip(m_wl_display);
		}

		if (m_wl_display)
		{
			wl_display_roundtrip(m_wl_display);
			wl_display_roundtrip(m_wl_display);
			wl_display_disconnect(m_wl_display);
			m_wl_display = nullptr;
		}
	}
	catch (const std::exception &exp)
	{
		log::error("Uncaught exception in surface::~System:");
		log::error("\twhat: {}", exp.what());
	}
}

void System::on_register()
{
	log::info("surface::System::on_register");
}

void System::on_unregister()
{
	log::info("surface::System::on_unregister");
}

void System::create_surface_component(
    ecs::EntityId entity,
    const SurfaceComponent::CreateInfo &info
)
try
{
	auto &component = m_registry->add<SurfaceComponent>(entity, info);
	ensure_component_sanity(component);

	auto &surface = m_registry->get<SurfaceComponent>(entity);
	const auto &resolution = surface.get_resolution();
	const auto &position = surface.get_position();
	surface.m_wl_display = m_wl_display;

	surface.m_wl_surface = wl_compositor_create_surface(m_wl_compositor);
	ensure(surface.m_wl_surface, "Failed to create Wayland surface");

	surface.m_xdg_surface = xdg_wm_base_get_xdg_surface(m_shell, surface.m_wl_surface);
	ensure(surface.m_xdg_surface, "Failed to get XDG-shell surface");
	xdg_surface_add_listener(surface.m_xdg_surface, &shell_surface_listener, {});

	surface.m_xdg_toplevel = xdg_surface_get_toplevel(surface.m_xdg_surface);
	ensure(surface.m_xdg_toplevel, "Failed to get XDG-shell toplevel");
	xdg_toplevel_add_listener(surface.m_xdg_toplevel, &toplevel_listener, {});

	xdg_toplevel_set_title(surface.m_xdg_toplevel, info.title.c_str());
	xdg_toplevel_set_app_id(surface.m_xdg_toplevel, "Wayland Vulkan Example");

	wl_surface_commit(surface.m_wl_surface);
	wl_display_roundtrip(m_wl_display);
	wl_surface_commit(surface.m_wl_surface);
}
catch (const std::exception &exp)
{
	log::error("Exception thrown when on_constructing surface component");
	log::error("\tentity: {}", u32 { entity });
	log::error("\twhat: {}", exp.what());

	try
	{
		auto &surface = m_registry->get<SurfaceComponent>(entity);

		if (surface.m_xdg_toplevel)
		{
			xdg_toplevel_destroy(surface.m_xdg_toplevel);
		}

		if (surface.m_xdg_surface)
		{
			xdg_surface_destroy(surface.m_xdg_surface);
		}

		if (surface.m_wl_surface)
		{
			wl_surface_destroy(surface.m_wl_surface);
		}
	}
	catch (const std::exception &exp)
	{
		log::error("Exception thrown when freeing a throwing surface component");
		log::error("\tentity: {}", u32 { entity });
		log::error("\twhat: {}", exp.what());
	}

	m_registry->remove<SurfaceComponent>(entity);
}

void System::tick(app::TickInfo tick)
{
	ignore = tick;

	wl_display_roundtrip(m_wl_display);

	for (auto &[id, surface] : m_registry->view<SurfaceComponent>())
	{
		// TODO(Light): This is flipped between win32 and wayland...
		// Temporary fix, in wayland we need the resize request to
		// put a resize event to be picked up by the renderer.
		//
		// but in win32 we need to resize before handling events
		// so we make sure to set the correct dimensions when receiving WM_SIZE
		// figure out a way to simplify this mess
		handle_events(surface);
		handle_requests(surface);
	}

	const auto now = std::chrono::steady_clock::now();
	m_last_tick_result = app::TickResult {
		.info = tick,
		.duration = now - tick.start_time,
		.end_time = now,
	};
}

void System::handle_events(SurfaceComponent &surface)
{
	/** @WIP(Light) */
	ignore = surface;

	auto &queue = surface.m_event_queue;
	queue.clear();

	const auto roundtrip = wl_display_roundtrip(m_wl_display);
	ensure(roundtrip != -1, "Wayland roundtrip error"); // WIP(Light)
}

void System::handle_requests(SurfaceComponent &surface)
{
	const auto visitor = overloads {
		[&](const ModifyTitleRequest &request) { modify_title(surface, request); },
		[&](const ModifyResolutionRequest &request) { modify_resolution(surface, request); },
		[&](const ModifyPositionRequest &request) { modify_position(surface, request); },
		[&](const ModifyVisibilityRequest &request) { modify_visibility(surface, request); }
	};

	for (const auto &request : surface.peek_requests())
	{
		std::visit(visitor, request);
	}

	wl_display_roundtrip(m_wl_display);

	surface.m_requests.clear();
}

void System::modify_title(SurfaceComponent &surface, const ModifyTitleRequest &request)
{
	auto *toplevel = surface.m_xdg_toplevel;
	ensure(toplevel, "Failed to modify surface title: null shell toplevel");
	ensure(!request.title.empty(), "Failed to modify surface title: null titlle");

	xdg_toplevel_set_title(toplevel, request.title.c_str());
	wl_surface_commit(surface.m_wl_surface);
	surface.m_title = request.title;
}

void System::modify_resolution(SurfaceComponent &surface, const ModifyResolutionRequest &request)
{
	const auto [width, height] = request.resolution;
	ensure(width, "Failed to modify resolution: invalid width: {}", width);
	ensure(height, "Failed to modify resolution: invalid height: {}", height);

	// Window size on Wayland is determined by the underlying swapchain's extent.
	// Hence we only need to change the internal variables AND simply generate a resized event for
	// the swapchain to be recreated.
	surface.m_resolution = request.resolution;
	surface.m_event_queue.emplace_back<ResizedEvent>(request.resolution);
}

void System::modify_position(SurfaceComponent &surface, const ModifyPositionRequest &request)
{
}

void System::modify_visibility(SurfaceComponent &surface, const ModifyVisibilityRequest &request)
{
}

void ensure_component_sanity(const SurfaceComponent &component)
{
	const auto [width, height] = component.get_resolution();

	ensure(width != 0u, "Received bad values for surface component: width({}) == 0", width);

	ensure(height != 0u, "Received bad values for surface component: height({}) == 0", height);

	ensure(
	    width < SurfaceComponent::max_dimension,
	    "Received bad values for surface component: width({}) > max_dimension({})",
	    width,
	    SurfaceComponent::max_dimension
	);

	ensure(
	    height < SurfaceComponent::max_dimension,
	    "Received bad values for surface component: height({}) > max_dimension({})",
	    height,
	    SurfaceComponent::max_dimension
	);

	ensure(
	    component.get_title().size() < SurfaceComponent::max_title_length,
	    "Received bad values for surface component: title.size({}) > max_title_length({})",
	    component.get_title().size(),
	    SurfaceComponent::max_title_length
	);
}

} // namespace lt::surface
