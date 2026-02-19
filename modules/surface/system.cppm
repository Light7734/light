module;
#if defined(LIGHT_PLATFORM_LINUX)
	#include <wayland-client.h>
	#include <xdg-shell.h>
#elif defined(LIGHT_PLATFORM_WINDOWS)
	#include <ShellScalingApi.h>
	#include <Windows.h>
	#include <comdef.h>
	#include <dwmapi.h> // For DWM functions
	#include <windowsx.h>

	#if defined(UNICODE) || defined(_UNICODE)
		#error "Unicode is not turned off"
	#endif
#else
	#error "Unsupported platform"
#endif

export module surface.system;
export import :components;

import preliminary;
import app.system;
import ecs.registry;
import math.vec2;
import input.codes;
import surface.requests;
import memory.reference;
import memory.null_on_move;
import logger;
import preliminary;
import surface.constants;
import memory.reference;
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

#if defined(LIGHT_PLATFORM_WINDOWS)
	static auto to_native_key(Key code) noexcept -> i64;

	static auto to_engine_key(int code) noexcept -> Key;

#endif

private:
#if defined(LIGHT_PLATFORM_LINUX)
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
#endif

#if defined(LIGHT_PLATFORM_WINDOWS)
	static auto CALLBACK window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT;
#endif

	void on_surface_destruct(ecs::Registry &registry, ecs::EntityId entity);

	void handle_requests(SurfaceComponent &surface);

	void handle_events(SurfaceComponent &surface);

	void modify_title(SurfaceComponent &surface, const ModifyTitleRequest &request);

	void modify_resolution(SurfaceComponent &surface, const ModifyResolutionRequest &request);

	void modify_position(SurfaceComponent &surface, const ModifyPositionRequest &request);

	void modify_visibility(SurfaceComponent &surface, const ModifyVisibilityRequest &request);

	memory::Ref<ecs::Registry> m_registry;

	app::TickResult m_last_tick_result {};

#if defined(LIGHT_PLATFORM_LINUX)
	memory::NullOnMove<wl_display *> m_wl_display {};

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


#endif
};

} // namespace lt::surface

/** @todo(Light): unimplemented in gcc -- is it even right to use a private fragment? */
// module :private;
namespace lt::surface {


#if defined(LIGHT_PLATFORM_LINUX)

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

	log::test("Surface  configure: {}", (i32)serial);
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
	// TODO(Light): handle resizing
	log::test("Toplevel configure: {}x{}", (i32)width, (i32)height);
}

void handle_toplevel_close(void *data, xdg_toplevel *toplevel)
{
	// TODO(Light): handle quitting
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
	void *system = std::bit_cast<System *>(data);
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
	log::debug("Pointer axis listener");
}

/* static */ void System::wayland_pointer_axis_source_listener(
    void *data,
    wl_pointer *pointer,
    u32 axis_source
)
{
	log::debug("Pointer axis source listener");
}

/* static */ void System::wayland_pointer_axis_stop_listener(
    void *data,
    wl_pointer *pointer,
    u32 time,
    u32 axis_source
)
{
	log::debug("Pointer axis stop listener");
}

/* static */ void System::wayland_pointer_axis_discrete_listener(
    void *data,
    wl_pointer *pointer,
    u32 axis,
    i32 discrete
)
{
	log::debug("Pointer axis discrete listener");
}

/* static */ void System::wayland_pointer_frame_listener(void *data, wl_pointer *pointer)
{
	log::debug("Pointer frame...");
}

void seat_name_listener(void *data, wl_seat *seat, const char *name)
{
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
	log::trace("Registry global remove:");
	log::trace("\tname: {}", name);
}

System::System(memory::Ref<ecs::Registry> registry)
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

void System::create_surface_component(ecs::EntityId entity, SurfaceComponent::CreateInfo info)
try
{
	auto &component = m_registry->add<SurfaceComponent>(entity, info);
	ensure_component_sanity(component);

	auto &surface = m_registry->get<SurfaceComponent>(entity);
	const auto &resolution = surface.get_resolution();
	const auto &position = surface.get_position();

	auto *wayland_surface = (wl_surface *)nullptr;
	auto *shell_toplevel = (xdg_toplevel *)nullptr;
	auto *shell_surface = (xdg_surface *)nullptr;

	wayland_surface = wl_compositor_create_surface(m_wl_compositor);
	ensure(wayland_surface, "Failed to create Wayland surface");

	shell_surface = xdg_wm_base_get_xdg_surface(m_shell, wayland_surface);
	ensure(shell_surface, "Failed to get XDG-shell surface");
	xdg_surface_add_listener(shell_surface, &shell_surface_listener, {});

	shell_toplevel = xdg_surface_get_toplevel(shell_surface);
	ensure(shell_toplevel, "Failed to get XDG-shell toplevel");
	xdg_toplevel_add_listener(shell_toplevel, &toplevel_listener, {});

	xdg_toplevel_set_title(shell_toplevel, info.title.c_str());
	xdg_toplevel_set_app_id(shell_toplevel, "Wayland Vulkan Example");

	wl_surface_commit(wayland_surface);
	wl_display_roundtrip(m_wl_display);
	wl_surface_commit(wayland_surface);

	surface.m_native_data.surface = wayland_surface;
	surface.m_native_data.display = m_wl_display;
	surface.m_native_data.shell_surface = shell_surface;
	surface.m_native_data.shell_toplevel = shell_toplevel;
}
catch (const std::exception &exp)
{
	log::error("Exception thrown when on_constructing surface component");
	log::error("\tentity: {}", u32 { entity });
	log::error("\twhat: {}", exp.what());

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
	// WIP(Light)
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
	auto *toplevel = surface.m_native_data.shell_toplevel;
	ensure(toplevel, "Failed to modify surface title: null shell toplevel");
	ensure(!request.title.empty(), "Failed to modify surface title: null titlle");

	xdg_toplevel_set_title(toplevel, request.title.c_str());
	wl_surface_commit(surface.m_native_data.surface);
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

#endif

#ifdef LIGHT_PLATFORM_WINDOWS

template<class... Ts>
struct overloads: Ts...
{
	using Ts::operator()...;
};

void ensure_component_sanity(const SurfaceComponent &component);

[[nodiscard]] auto get_error_message() -> std::string;

void check_hresult(HRESULT result);

System::System(memory::Ref<ecs::Registry> registry): m_registry(std::move(registry))
{
	ensure(m_registry, "Failed to initialize surface system: null registry");

	ensure(
	    m_registry->view<SurfaceComponent>().get_size() == 0,
	    "Failed to initialize surface system: registry has surface component(s)"
	);

	m_registry->connect_on_destruct<SurfaceComponent>(
	    [this](ecs::Registry &registry, ecs::EntityId entity) {
		    on_surface_destruct(registry, entity);
	    }
	);

	auto window_class = WNDCLASS {
		.lpfnWndProc = System::window_proc,
		.hInstance = GetModuleHandle(nullptr),
		.lpszClassName = constants::class_name,
	};
	RegisterClass(&window_class);
}

System::~System()
{
	if (!m_registry)
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
	}
	catch (const std::exception &exp)
	{
		log::error("Uncaught exception in surface::~System:");
		log::error("\twhat: {}", exp.what());
	}
}

void System::on_register()
{
}

void System::on_unregister()
{
}

/** Selects a monitor from a point and returns the dpi of that monitor. */
auto get_dpi_from_point(math::vec2_i32 point) -> ::UINT
{
	auto target_monitor = MonitorFromPoint(
	    ::POINT { .x = point.x, .y = point.y },
	    MONITOR_DEFAULTTONEAREST
	);
	ensure(target_monitor, "Failed to get target monitor from MonitorFromPoint (point: {})", point);

	auto dpi_x = ::UINT {};
	auto dpi_y = ::UINT {};
	check_hresult(::GetDpiForMonitor(target_monitor, MDT_EFFECTIVE_DPI, &dpi_x, &dpi_y));

	ensure(
	    dpi_x == dpi_y,
	    "Assumption that dpi_x == dpi_y does not hold true ({} == {})",
	    dpi_x,
	    dpi_y
	);

	return dpi_x;
}

void System::create_surface_component(ecs::EntityId entity, SurfaceComponent::CreateInfo info)
try
{
	auto &surface = m_registry->add<SurfaceComponent>(entity, info);
	ensure_component_sanity(surface);

	// auto style = WS_THICKFRAME    // Required for a standard resizeable window
	//              | WS_SYSMENU     // Support snapping via Win + ← / Win + →
	//              | WS_MAXIMIZEBOX // Support maximizing via mouse dragging to the top of the
	//              screen | WS_MINIMIZEBOX // Support minimizing by clicking on the taskbar icon
	//     ;

	// if (info.visible)
	// {
	// 	style |= WS_VISIBLE;
	// }

	auto hwnd = ::CreateWindowEx(
	    0,
	    constants::class_name,
	    info.title.data(),
	    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
	    info.position.x,
	    info.position.y,
	    info.resolution.x,
	    info.resolution.y,
	    nullptr,
	    nullptr,
	    ::GetModuleHandle(nullptr),
	    /** @todo(Light): Component's address may change as the underlying ECS storage provides no
	     * pointer-stability guarantees; Figure out a way to make this safe. */
	    std::bit_cast<LPVOID>(&surface)
	);
	ensure(hwnd, "Failed ::CreateWindowEx: {}", get_error_message());
	surface.m_native_data.window = hwnd;

	auto margins = MARGINS { 0, 0, 1, 0 }; // Extend 1px on right for shadow rendering
	DwmExtendFrameIntoClientArea(hwnd, &margins);

	BOOL useDarkMode = TRUE;
	DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &useDarkMode, sizeof(useDarkMode));

	ShowWindow(hwnd, SW_SHOW);
	SetWindowPos(
	    hwnd,
	    NULL,
	    0,
	    0,
	    0,
	    0,
	    SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE
	);
	UpdateWindow(hwnd);
	surface.m_visible = info.visible;

	if (info.visible)
	{
		ShowWindow(hwnd, SW_SHOW);
	}
	else
	{
		ShowWindow(hwnd, SW_HIDE);
	}
}
catch (const std::exception &exp)
{
	log::error("Exception thrown when on_constructing surface component");
	log::error("\tentity: {}", u32 { entity });
	log::error("\twhat: {}", exp.what());
	m_registry->remove<SurfaceComponent>(entity);
}

void System::on_surface_destruct(ecs::Registry &registry, ecs::EntityId entity)
{
	auto *window = registry.get<SurfaceComponent>(entity).get_native_data().window;
	if (!window)
	{
		log::warn("Surface component destroyed with null window handle");
		return;
	}

	DestroyWindow(window);
}

void System::handle_events(SurfaceComponent &surface)
{
	auto &queue = surface.m_event_queue;
	queue.clear();

	auto message = MSG {};
	while (PeekMessage(&message, {}, {}, {}, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
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

	surface.m_requests.clear();
}

void System::modify_title(SurfaceComponent &surface, const ModifyTitleRequest &request)
{
	auto hwnd = surface.m_native_data.window;
	surface.m_title = request.title;

	::SetWindowTextA(hwnd, request.title.c_str());
}

void System::modify_resolution(SurfaceComponent &surface, const ModifyResolutionRequest &request)
{
	::SetWindowPos(
	    surface.m_native_data.window,
	    {},
	    surface.get_position().x,
	    surface.get_position().y,
	    request.resolution.x,
	    request.resolution.y,
	    SWP_NOZORDER | SWP_NOACTIVATE
	);
}

void System::modify_position(SurfaceComponent &surface, const ModifyPositionRequest &request)
{
	::SetWindowPos(
	    surface.m_native_data.window,
	    {},
	    request.position.x,
	    request.position.y,
	    surface.get_resolution().x,
	    surface.get_resolution().y,
	    SWP_NOZORDER | SWP_NOACTIVATE
	);
}

void System::modify_visibility(SurfaceComponent &surface, const ModifyVisibilityRequest &request)
{
	::ShowWindow(surface.m_native_data.window, request.visible ? SW_SHOW : SW_HIDE);
}

void System::tick(app::TickInfo tick)
{
	for (auto &[id, surface] : m_registry->view<SurfaceComponent>())
	{
		handle_requests(surface);
		handle_events(surface);
	}

	const auto now = std::chrono::steady_clock::now();
	m_last_tick_result = app::TickResult {
		.info = tick,
		.duration = now - tick.start_time,
		.end_time = now,
	};
}

/* static */ auto System::to_native_key(Key code) noexcept -> i64
{
	using enum Key;

	switch (code)
	{
	case left_button: return VK_LBUTTON;
	case right_button: return VK_RBUTTON;
	case middle_button: return VK_MBUTTON;

	case escape: return VK_ESCAPE;
	case backspace: return VK_BACK;
	case tab: return VK_TAB;
	case capslock: return VK_CAPITAL;
	case enter: return VK_RETURN;
	case space: return VK_SPACE;
	case delete_: return VK_DELETE;

	case shift: return VK_SHIFT;
	case right_shift: return VK_RSHIFT;

	case control: return VK_CONTROL;
	case right_control: return VK_RCONTROL;

	case alt: return VK_MENU;
	case right_alt: return VK_RMENU;

	case pageup: return VK_PRIOR;
	case pagedown: return VK_NEXT;
	case end: return VK_END;
	case home: return VK_HOME;

	case left_arrow: return VK_LEFT;
	case right_arrow: return VK_RIGHT;
	case down_arrow: return VK_DOWN;
	case up_arrow: return VK_UP;

	case cancel: return VK_CANCEL;
	case pause: return VK_PAUSE;
	case select: return VK_SELECT;
	case print: return VK_PRINT;
	case snapshot: return VK_SNAPSHOT;
	case insert: return VK_INSERT;
	case help: return VK_HELP;
	case sleep: return VK_SLEEP;

	case digit_0: return '0';
	case digit_1: return '1';
	case digit_2: return '2';
	case digit_3: return '3';
	case digit_4: return '4';
	case digit_5: return '5';
	case digit_6: return '6';
	case digit_7: return '7';
	case digit_8: return '8';
	case digit_9: return '9';

	case a: return 'A';
	case b: return 'B';
	case c: return 'C';
	case d: return 'D';
	case e: return 'E';
	case f: return 'F';
	case g: return 'G';
	case h: return 'H';
	case i: return 'I';
	case j: return 'J';
	case k: return 'K';
	case l: return 'L';
	case m: return 'M';
	case n: return 'N';
	case o: return 'O';
	case p: return 'P';
	case q: return 'Q';
	case r: return 'R';
	case s: return 'S';
	case t: return 'T';
	case u: return 'U';
	case v: return 'V';
	case w: return 'W';
	case x: return 'X';
	case y: return 'Y';
	case z: return 'Z';

	case super: return VK_LWIN;
	case right_super: return VK_RWIN;

	case kp_0: return VK_NUMPAD0;
	case kp_1: return VK_NUMPAD1;
	case kp_2: return VK_NUMPAD2;
	case kp_3: return VK_NUMPAD3;
	case kp_4: return VK_NUMPAD4;
	case kp_5: return VK_NUMPAD5;
	case kp_6: return VK_NUMPAD6;
	case kp_7: return VK_NUMPAD7;
	case kp_8: return VK_NUMPAD8;
	case kp_9: return VK_NUMPAD9;

	case kp_multiply: return VK_MULTIPLY;
	case kp_add: return VK_ADD;
	case kp_subtract: return VK_SUBTRACT;
	case kp_decimal: return VK_DECIMAL;

	case f1: return VK_F1;
	case f2: return VK_F2;
	case f3: return VK_F3;
	case f4: return VK_F4;
	case f5: return VK_F5;
	case f6: return VK_F6;
	case f7: return VK_F7;
	case f8: return VK_F8;
	case f9: return VK_F9;
	case f10: return VK_F10;
	case f11: return VK_F11;
	case f12: return VK_F12;
	}

	return {};
};

/* static */ auto System::to_engine_key(int code) noexcept -> Key
{
	using enum Key;

	switch (code)
	{
	case VK_LBUTTON: return left_button;
	case VK_RBUTTON: return right_button;
	case VK_MBUTTON: return middle_button;

	case VK_ESCAPE: return escape;
	case VK_BACK: return backspace;
	case VK_TAB: return tab;
	case VK_CAPITAL: return capslock;
	case VK_RETURN: return enter;
	case VK_SPACE: return space;
	case VK_DELETE: return delete_;

	case VK_SHIFT: return shift;
	case VK_RSHIFT: return right_shift;

	case VK_CONTROL: return control;
	case VK_RCONTROL: return right_control;

	case VK_MENU: return alt;
	case VK_RMENU: return right_alt;

	case VK_PRIOR: return pageup;
	case VK_NEXT: return pagedown;
	case VK_END: return end;
	case VK_HOME: return home;

	case VK_LEFT: return left_arrow;
	case VK_RIGHT: return right_arrow;
	case VK_DOWN: return down_arrow;
	case VK_UP: return up_arrow;

	case VK_CANCEL: return cancel;
	case VK_PAUSE: return pause;
	case VK_SELECT: return Key::select;
	case VK_PRINT: return print;
	case VK_SNAPSHOT: return snapshot;
	case VK_INSERT: return insert;
	case VK_HELP: return help;
	case VK_SLEEP: return sleep;

	case '0': return digit_0;
	case '1': return digit_1;
	case '2': return digit_2;
	case '3': return digit_3;
	case '4': return digit_4;
	case '5': return digit_5;
	case '6': return digit_6;
	case '7': return digit_7;
	case '8': return digit_8;
	case '9': return digit_9;

	case 'A': return a;
	case 'B': return b;
	case 'C': return c;
	case 'D': return d;
	case 'E': return e;
	case 'F': return f;
	case 'G': return g;
	case 'H': return h;
	case 'I': return i;
	case 'J': return j;
	case 'K': return k;
	case 'L': return l;
	case 'M': return m;
	case 'N': return n;
	case 'O': return o;
	case 'P': return p;
	case 'Q': return q;
	case 'R': return r;
	case 'S': return s;
	case 'T': return t;
	case 'U': return u;
	case 'V': return v;
	case 'W': return w;
	case 'X': return x;
	case 'Y': return y;
	case 'Z': return z;

	case VK_LWIN: return super;
	case VK_RWIN: return right_super;

	case VK_NUMPAD0: return kp_0;
	case VK_NUMPAD1: return kp_1;
	case VK_NUMPAD2: return kp_2;
	case VK_NUMPAD3: return kp_3;
	case VK_NUMPAD4: return kp_4;
	case VK_NUMPAD5: return kp_5;
	case VK_NUMPAD6: return kp_6;
	case VK_NUMPAD7: return kp_7;
	case VK_NUMPAD8: return kp_8;
	case VK_NUMPAD9: return kp_9;

	case VK_MULTIPLY: return kp_multiply;
	case VK_ADD: return kp_add;
	case VK_SUBTRACT: return kp_subtract;
	case VK_DECIMAL: return kp_decimal;

	case VK_F1: return f1;
	case VK_F2: return f2;
	case VK_F3: return f3;
	case VK_F4: return f4;
	case VK_F5: return f5;
	case VK_F6: return f6;
	case VK_F7: return f7;
	case VK_F8: return f8;
	case VK_F9: return f9;
	case VK_F10: return f10;
	case VK_F11: return f11;
	case VK_F12: return f12;
	}

	return Key::unknown;
};

/* static */ auto CALLBACK System::window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    -> LRESULT
{
	const auto get_userdata = [hwnd]() -> SurfaceComponent & {
		auto *long_ptr = std::bit_cast<SurfaceComponent *>(GetWindowLongPtrA(hwnd, GWLP_USERDATA));

		/** @todo(Light): Throwing here causes a crash, handle errors more gracefully. */
		ensure(long_ptr != nullptr, "Null window longptr!");

		return *long_ptr;
	};

	switch (uMsg)
	{
	case WM_NCCALCSIZE:
	{
		if (wParam == TRUE)
		{
			// Get border thicknesses
			// int borderPadding = GetSystemMetrics(SM_CXPADDEDBORDER);
			// int borderLR = GetSystemMetrics(SM_CXFRAME) + borderPadding;
			// int borderTB = GetSystemMetrics(SM_CYFRAME) + borderPadding;
			//
			// NCCALCSIZE_PARAMS *params = (NCCALCSIZE_PARAMS *)lParam;
			// RECT *rect = &params->rgrc[0];

			// Adjust client rect: Subtract borders from left/right/bottom
			// rect->left += borderLR;
			// rect->right -= borderLR;
			// rect->bottom -= borderTB;

			// For maximized windows, also subtract top border
			// if (IsZoomed(hwnd))
			// {
			// 	rect->top += borderTB;
			// }

			// Return 0 to indicate we handled it (prevents default title bar)
			return 0;
		}
		break;
	}

	case WM_NCHITTEST:
	{
		// Get mouse position in client coordinates
		POINT pt;
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		ScreenToClient(hwnd, &pt);

		RECT clientRect;
		GetClientRect(hwnd, &clientRect);

		// Define a drag area (e.g., top 30px of client area acts as "caption" for moving)
		const int dragHeight = 30; // Adjust as needed; set to 0 if no dragging desired
		if (pt.y < dragHeight && pt.y >= 0)
		{
			// Check corners for diagonal resize
			const int resizeBorder = 8; // Pixels for corner hit detection
			if (pt.x < resizeBorder)
				return HTTOPLEFT;
			if (pt.x > clientRect.right - resizeBorder)
				return HTTOPRIGHT;
			// Middle top: vertical resize
			return HTTOP;
		}

		// Fallback to default handling for side/bottom borders and other areas
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		RECT rect;
		GetClientRect(hwnd, &rect);
		FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 5));
		EndPaint(hwnd, &ps);
		return 0;
	}
	case WM_NCCREATE:
		[[unlikely]]
		{
			const auto *create_struct = std::bit_cast<::CREATESTRUCT *>(lParam);
			auto *surface_ptr = std::bit_cast<SurfaceComponent *>(create_struct->lpCreateParams);
			::SetWindowLongPtrA(hwnd, GWLP_USERDATA, std::bit_cast<LONG_PTR>(surface_ptr));

			return !!surface_ptr;
		}

	case WM_SETTEXT:
		[[unlikely]]
		{
			get_userdata().m_title = std::string { std::bit_cast<char *>(lParam) };
			break;
		}

	case WM_SHOWWINDOW: get_userdata().m_visible = static_cast<bool>(wParam); return 0;

	case WM_SETFOCUS: get_userdata().m_event_queue.emplace_back(GainFocusEvent {}); return 0;

	case WM_KILLFOCUS: get_userdata().m_event_queue.emplace_back(LostFocusEvent {}); return 0;

	case WM_SIZE:
	{
		auto &surface = get_userdata();


		surface.m_resolution = math::vec2_u32 { LOWORD(lParam), HIWORD(lParam) };
		surface.m_event_queue.emplace_back(surface.m_resolution);

		return 0;
	}

	case WM_MOVE:
	{
		auto &surface = get_userdata();

		surface.m_position = math::vec2_i32 { LOWORD(lParam), HIWORD(lParam) };
		surface.m_event_queue.emplace_back(MovedEvent { surface.m_position });

		return 0;
	}

	case WM_MOUSEWHEEL:
	{
		const auto delta = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;

		if (delta > 0)
		{
			get_userdata().m_event_queue.emplace_back(KeyPressedEvent { Key::wheel_up });
			get_userdata().m_event_queue.emplace_back(KeyReleasedEvent { Key::wheel_up });
		}
		else if (delta < 0)
		{
			get_userdata().m_event_queue.emplace_back(KeyPressedEvent { Key::wheel_down });
			get_userdata().m_event_queue.emplace_back(KeyReleasedEvent { Key::wheel_down });
		}

		break;
	}
	case WM_LBUTTONDOWN:
	{
		get_userdata().m_event_queue.emplace_back<KeyPressedEvent>(Key::left_button);
		break;
	}
	case WM_LBUTTONUP:
	{
		get_userdata().m_event_queue.emplace_back<KeyReleasedEvent>(Key::left_button);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		get_userdata().m_event_queue.emplace_back<KeyPressedEvent>(Key::right_button);
		break;
	}
	case WM_RBUTTONUP:
	{
		get_userdata().m_event_queue.emplace_back<KeyReleasedEvent>(Key::right_button);
		break;
	}
	case WM_MBUTTONDOWN:
	{
		get_userdata().m_event_queue.emplace_back<KeyPressedEvent>(Key::middle_button);
		break;
	}
	case WM_MBUTTONUP:
	{
		get_userdata().m_event_queue.emplace_back<KeyReleasedEvent>(Key::middle_button);
		break;
	}
	case WM_XBUTTONDOWN:
	{
		const auto key = static_cast<Key>(
		    std::to_underlying(Key::x_button_1) + GET_XBUTTON_WPARAM(wParam) - 1
		);
		get_userdata().m_event_queue.emplace_back<KeyPressedEvent>(key);
		break;
	}
	case WM_XBUTTONUP:
	{
		const auto key = static_cast<Key>(
		    std::to_underlying(Key::x_button_1) + GET_XBUTTON_WPARAM(wParam) - 1
		);
		get_userdata().m_event_queue.emplace_back<KeyReleasedEvent>(key);
		break;
	}
	case WM_KEYDOWN:
	{
		get_userdata().m_event_queue.emplace_back<KeyPressedEvent>(
		    to_engine_key(static_cast<int>(wParam))
		);
		break;
	}
	case WM_KEYUP:

	{
		get_userdata().m_event_queue.emplace_back<KeyReleasedEvent>(
		    to_engine_key(static_cast<int>(wParam))
		);
		break;
	}

	case WM_CLOSE:
	{
		get_userdata().m_event_queue.emplace_back<ClosedEvent>({});
		return 0;
	}

		// case WM_DESTROY:
		// {
		// 	PostQuitMessage(0);
		// 	return 0;
		// }
	}

	return DefWindowProcA(hwnd, uMsg, wParam, lParam);
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

[[nodiscard]] auto get_error_message() -> std::string
{
	const auto error = GetLastError();

	auto msg = LPSTR { nullptr };
	::FormatMessageA(
	    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
	    nullptr,
	    error,
	    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	    std::bit_cast<::LPSTR>(&msg),
	    0,
	    nullptr
	);

	if (!msg)
	{
		return "Unknown error (" + std::to_string(error) + ")";
	}

	auto result = std::string { msg };
	::LocalFree(msg);
	return result;
}

void check_hresult(HRESULT result)
{
	if (!result)
	{
		return;
	}

	auto error = ::_com_error { result };
	auto message = std::string { ::LPCTSTR { error.ErrorMessage() } };

	throw std::runtime_error { std::format("HResult failed: {}", message) };
}

#endif

} // namespace lt::surface
