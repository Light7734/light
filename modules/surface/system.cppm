module;
#if defined(LIGHT_PLATFORM_LINUX)
	#define _POSIX_C_SOURCE 200112L
	#include <errno.h>
	#include <fcntl.h>
	#include <sys/mman.h>
	#include <time.h>
	#include <unistd.h>
	#include <wayland-client.h>
	#include <wayland-protocols/xdg-shell.h>
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
	static void registry_handle_global(
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
	wl_display *m_wl_display {};

	wl_registry *m_wl_registry {};

	wl_registry_listener m_wl_registry_listener {};

	wl_compositor *m_wl_compositor {};

	wl_surface *m_wl_surface {};

	wl_shm *m_wl_shm {};

	wl_shm_pool *m_wl_shm_pool {};
#endif
};

} // namespace lt::surface

module :private;
namespace lt::surface {

#ifdef LIGHT_PLATFORM_LINUX

void System::registry_handle_global(
    void *data,
    wl_registry *registry,
    std::uint32_t name,
    const char *interface,
    std::uint32_t version
)

{
	auto *system = std::bit_cast<System *>(data);

	// log::trace("Registry global:");
	// log::trace("\tinterface: {}", interface);
	// log::trace("\tversion: {}", version);
	// log::trace("\tname: {}", name);

	if (std::strcmp(interface, wl_compositor_interface.name) == 0)
	{
		system->m_wl_compositor = std::bit_cast<wl_compositor *>(
		    wl_registry_bind(registry, name, &wl_compositor_interface, 4)
		);
		log::info("Bound successfuly to the wl_compositor global");

		system->m_wl_surface = wl_compositor_create_surface(system->m_wl_compositor);

		if (system->m_wl_surface)
		{
			log::info("Created a wl_surface from the compositor");
		}
		else
		{
			log::critical("Failed to create a wl_surface from the compositor");
			std::terminate();
		}
	}

	if (std::strcmp(interface, wl_shm_interface.name) == 0)
	{
		system->m_wl_shm = std::bit_cast<wl_shm *>(
		    wl_registry_bind(registry, name, &wl_shm_interface, 1)
		);

		log::info("Bound successfuly to the wl_shm global");
	}


	if (std::strcmp(interface, xdg_))
}

void registry_handle_global_remove(void *data, wl_registry *registry, std::uint32_t name)
{
	log::trace("Registry global remove:");
	log::trace("\tname: {}", name);
}

void read_name(char *buffer)
{
	auto time_spec = timespec {};
	clock_gettime(CLOCK_REALTIME, &time_spec);
	auto nanoseconds = time_spec.tv_nsec;

	for (auto idx = std::uint32_t { 0u }; idx < 6u; ++idx)
	{
		buffer[idx] = 'A' + (nanoseconds & 15) + (nanoseconds & 16) * 2; // NOLINT
		nanoseconds >>= 5;                                               // NOLINT
	}
}

[[nodiscard]] auto create_shm_file() -> int
{
	auto retries = 100u;
	do // NOLINT
	{
		char name[] = "/wl_shm-XXXXXX";
		read_name(name + sizeof(name) - 7);
		--retries;
		auto file_descriptor = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0600);
		if (file_descriptor >= 0)
		{
			shm_unlink(name);
			return file_descriptor;
		}
	} while (retries > 0 && errno == EEXIST);
	return -1;
}

[[nodiscard]] auto allocate_shm_file(std::size_t size) -> int
{
	auto file_descriptor = create_shm_file();
	if (file_descriptor < 0)
	{
		return -1;
	}

	auto ret = 0;
	do // NOLINT
	{
		ret = ftruncate(file_descriptor, size); // NOLINT

	} while (ret < 0 && errno == EINTR);

	if (ret < 0)
	{
		close(file_descriptor);
		return -1;
	}

	return file_descriptor;
}

System::System(memory::Ref<ecs::Registry> registry)
    : m_wl_registry_listener(
          {
              .global = registry_handle_global,
              .global_remove = registry_handle_global_remove,
          }
      )
{
	// NOLINTNEXTLINE
	m_wl_display = wl_display_connect({});

	debug::ensure(m_wl_display, "Failed to connect to Wayland display");

	log::info("Wayland connection established");

	// NOLINTNEXTLINE
	m_wl_registry = wl_display_get_registry(m_wl_display);

	// TODO(Light): "this" could be moved around... replace with a pointer to some heap allocation
	wl_registry_add_listener(m_wl_registry, &m_wl_registry_listener, this);

	wl_display_roundtrip(m_wl_display);

	debug::ensure(m_wl_compositor, "Could not bind to the Wayland's compositor global");
	debug::ensure(m_wl_shm, "Could not bind to the Wayland's compositor global");

	const auto width = 1080u;
	const auto height = 1920u;
	const auto stride = 4u;
	const auto shm_pool_size = width * stride * height * 2;

	auto file_descriptor = allocate_shm_file(shm_pool_size);
	auto *pool_data = std::bit_cast<std::uint8_t *>(
	    mmap({}, shm_pool_size, PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0)
	);

	m_wl_shm_pool = wl_shm_create_pool(m_wl_shm, file_descriptor, shm_pool_size);
	debug::ensure(
	    m_wl_shm_pool,
	    "Failed to create Wayland shared memory pool of size: {}",
	    shm_pool_size
	);

	log::info("Created Wayland shared memory pool size of: {}", shm_pool_size);

	auto idx = 0;
	auto offset = width * height * stride * idx;
	auto *wl_buffer = wl_shm_pool_create_buffer(
	    m_wl_shm_pool,
	    offset,
	    width,
	    height,
	    width * stride,
	    WL_SHM_FORMAT_XRGB8888,
	);
}

System::~System()
{
	wl_display_disconnect(m_wl_display);
}

void System::on_register()
{
}

void System::on_unregister()
{
}

void System::create_surface_component(ecs::EntityId entity, SurfaceComponent::CreateInfo info)
{
}

void System::tick(app::TickInfo tick)
{
}

#endif

#ifdef LIGHT_PLATFORM_WINDOWS
#endif

} // namespace lt::surface
