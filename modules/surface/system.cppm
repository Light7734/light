module;
#if defined(LIGHT_PLATFORM_LINUX)
	#include <wayland-client.h>
	#include <xdg-shell.h>
#elif defined(LIGHT_PLATFORM_WINDOWS)
	#include <Windows.h>
#else
	#error "Unsupported platform"
#endif

export module surface.system;
export import :components;
import debug.assertions;
import app.system;
import ecs.registry;
import math.vec2;
import surface.requests;
import memory.reference;
import memory.null_on_move;
import logger;
import std;
import surface.constants;
import debug.assertions;
import memory.reference;
import surface.requests;
import surface.events;
import logger;
import ecs.registry;
import ecs.entity;
import time;
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
	static void wayland_registry_listener(
	    void *data,
	    wl_registry *registry,
	    std::uint32_t name,
	    const char *interface,
	    std::uint32_t version
	);

	static void wayland_seat_capabilities_listener(
	    void *data,
	    wl_seat *seat,
	    std::uint32_t capabilities
	);

	static void wayland_pointer_leave_listener(
	    void *data,
	    wl_pointer *pointer,
	    std::uint32_t serial,
	    wl_surface *surface
	);

	static void wayland_pointer_enter_listener(
	    void *data,
	    wl_pointer *pointer,
	    std::uint32_t serial,
	    wl_surface *surface,
	    wl_fixed_t surface_x,
	    wl_fixed_t surface_y
	);

	static void wayland_pointer_motion_listener(
	    void *data,
	    wl_pointer *listener,
	    std::uint32_t time,
	    wl_fixed_t surface_x,
	    wl_fixed_t surface_y
	);

	static void wayland_pointer_button_listener(
	    void *data,
	    wl_pointer *pointer,
	    std::uint32_t serial,
	    std::uint32_t time,
	    std::uint32_t button,
	    std::uint32_t state
	);

	static void wayland_pointer_axis_listener(
	    void *data,
	    wl_pointer *pointer,
	    std::uint32_t time,
	    std::uint32_t axis,
	    wl_fixed_t value
	);

	static void wayland_pointer_axis_source_listener(
	    void *data,
	    wl_pointer *pointer,
	    std::uint32_t axis_source
	);

	static void wayland_pointer_axis_stop_listener(
	    void *data,
	    wl_pointer *pointer,
	    std::uint32_t time,
	    std::uint32_t axis_source
	);

	static void wayland_pointer_axis_discrete_listener(
	    void *data,
	    wl_pointer *pointer,
	    std::uint32_t axis,
	    std::int32_t discrete
	);

	static void wayland_pointer_frame_listener(void *data, wl_pointer *pointer);
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

	app::TickResult m_last_tick_result {};

#if defined(LIGHT_PLATFORM_LINUX)
	memory::NullOnMove<wl_display *> m_wl_display {};

	wl_registry *m_wl_registry {};

	wl_registry_listener m_wl_registry_listener {};

	wl_seat_listener m_wl_seat_listener {};

	wl_pointer_listener m_wl_pointer_listener {};

	wl_compositor *m_wl_compositor {};

	xdg_wm_base *m_shell = {};

	wl_seat *m_wl_seat {};

	wl_keyboard *m_wl_keyboard {};

	wl_pointer *m_wl_pointer {};

	wl_touch *m_wl_touch {}; // TODO(Light): Add touch support


#endif
};

} // namespace lt::surface

module :private;
namespace lt::surface {

#if defined(LIGHT_PLATFORM_LINUX)

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

void wayland_pointer_leave_listener(
    void *data,
    wl_pointer *pointer,
    std::uint32_t serial,
    wl_surface *surface
)
{
	void *system = std::bit_cast<System *>(data);
}

/* static */ void System::wayland_seat_capabilities_listener(
    void *data,
    wl_seat *seat,
    std::uint32_t capabilities
)
{
	std::ignore = seat;

	auto *system = std::bit_cast<System *>(data);
	const auto have_pointer = capabilities & WL_SEAT_CAPABILITY_POINTER;

	if (have_pointer && !system->m_wl_pointer)
	{
		system->m_wl_pointer = wl_seat_get_pointer(system->m_wl_seat);
		wl_pointer_add_listener(system->m_wl_pointer, &system->m_wl_pointer_listener, system);
		log::info(
		    "Added Wayland pointer (0x{:x})",
		    std::bit_cast<std::size_t>(system->m_wl_pointer)
		);
	}
	else if (!have_pointer && system->m_wl_pointer)
	{
		wl_pointer_release(system->m_wl_pointer);
		system->m_wl_pointer = nullptr;

		log::info(
		    "Released Wayland pointer (0x{:x})",
		    std::bit_cast<std::size_t>(system->m_wl_pointer)
		);
	}
}

/* static */ void System::wayland_pointer_leave_listener(
    void *data,
    wl_pointer *pointer,
    std::uint32_t serial,
    wl_surface *surface
)
{
	log::debug("Pointer leave...");
}

/* static */ void System::wayland_pointer_enter_listener(
    void *data,
    wl_pointer *pointer,
    std::uint32_t serial,
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
    std::uint32_t time,
    wl_fixed_t surface_x,
    wl_fixed_t surface_y
)
{
	log::debug("Pointer motion: [{} - {}]", surface_x, surface_y);
}

/* static */ void System::wayland_pointer_button_listener(
    void *data,
    wl_pointer *pointer,
    std::uint32_t serial,
    std::uint32_t time,
    std::uint32_t button,
    std::uint32_t state
)
{
}

/* static */ void System::wayland_pointer_axis_listener(
    void *data,
    wl_pointer *pointer,
    std::uint32_t time,
    std::uint32_t axis,
    wl_fixed_t value
)
{
}

/* static */ void System::wayland_pointer_axis_source_listener(
    void *data,
    wl_pointer *pointer,
    std::uint32_t axis_source
)
{
}

/* static */ void System::wayland_pointer_axis_stop_listener(
    void *data,
    wl_pointer *pointer,
    std::uint32_t time,
    std::uint32_t axis_source
)
{
}

/* static */ void System::wayland_pointer_axis_discrete_listener(
    void *data,
    wl_pointer *pointer,
    std::uint32_t axis,
    std::int32_t discrete
)
{
}

/* static */ void System::wayland_pointer_frame_listener(void *data, wl_pointer *pointer)
{
	log::debug("Pointer frame...");
}

void seat_name_listener(void *data, wl_seat *seat, const char *name)
{
	std::ignore = data;

	log::info("Wayland seat:");
	log::info("\tname: {}", name);
	log::info("\taddr: 0x{:x}", std::bit_cast<std::size_t>(seat));
}

void System::wayland_registry_listener(
    void *data,
    wl_registry *registry,
    std::uint32_t name,
    const char *interface,
    std::uint32_t version
)

{
	std::ignore = version;

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

void registry_handle_global_remove(void *data, wl_registry *registry, std::uint32_t name)
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
	// NOLINTNEXTLINE
	m_wl_display = wl_display_connect({});
	debug::ensure(m_wl_display, "Failed to connect to Wayland display");

	// NOLINTNEXTLINE
	m_wl_registry = wl_display_get_registry(m_wl_display);
	debug::ensure(m_wl_registry, "Failed to get Wayland display's registry");

	// TODO(Light): "this" could be moved around... replace with a pointer to some heap allocation
	wl_registry_add_listener(m_wl_registry, &m_wl_registry_listener, this);
	wl_display_roundtrip(m_wl_display);

	// Wayland seat gets named after the second roundtrip....
	// For reasons beyond my fragile comprehension :(
	wl_display_roundtrip(m_wl_display);

	debug::ensure(m_wl_compositor, "Failed to bind to the Wayland's compositor global");
	debug::ensure(m_shell, "Failed to bind to the Wayland's  XDG-shell global");
}

System::~System()
{
	if (!m_wl_display)
	{
		return;
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
	wl_display_roundtrip(m_wl_display);
}

#endif

#ifdef LIGHT_PLATFORM_WINDOWS

template<class... Ts>
struct overloads: Ts...
{
	using Ts::operator()...;
};

void ensure_component_sanity(const SurfaceComponent &component);

auto CALLBACK native_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT;

System::System(memory::Ref<ecs::Registry> registry): m_registry(std::move(registry))
{
	debug::ensure(m_registry, "Failed to initialize surface system: null registry");

	debug::ensure(
	    m_registry->view<SurfaceComponent>().get_size() == 0,
	    "Failed to initialize surface system: registry has surface component(s)"
	);

	m_registry->connect_on_destruct<SurfaceComponent>(
	    [this](ecs::Registry &registry, ecs::EntityId entity) {
		    on_surface_destruct(registry, entity);
	    }
	);

	auto window_class = WNDCLASS {
		.lpfnWndProc = native_window_proc,
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
		// TODO(Light): make registry.remove not invalidate iterators
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

void System::create_surface_component(ecs::EntityId entity, SurfaceComponent::CreateInfo info)
try
{
	auto &component = m_registry->add<SurfaceComponent>(entity, info);
	auto &surface = m_registry->get<SurfaceComponent>(entity);
	const auto &resolution = surface.get_resolution();
	const auto &position = surface.get_position();
	ensure_component_sanity(surface);

	surface.m_native_data.window = CreateWindowEx(
	    0,
	    constants::class_name,
	    info.title.data(),
	    WS_OVERLAPPEDWINDOW,
	    CW_USEDEFAULT,
	    CW_USEDEFAULT,
	    CW_USEDEFAULT,
	    CW_USEDEFAULT,
	    nullptr,
	    nullptr,
	    GetModuleHandle(nullptr),
	    nullptr
	);
	debug::ensure(surface.m_native_data.window, "Failed to create Windows surface component");

	ShowWindow(surface.m_native_data.window, SW_NORMAL);

	// TODO(Light): refactor "environment" into standalone module
	// NOLINTNEXTLINE(concurrency-mt-unsafe)
	// auto *display_env = std::getenv("DISPLAY");
	// debug::ensure(display_env != nullptr, "DISPLAY env var not found!");
	//
	// auto *display = XOpenDisplay(display_env);
	// debug::ensure(display, "Failed to open XDisplay with DISPLAY: {}", display_env);
	//
	// auto root_window = XDefaultRootWindow(display);
	//
	// auto border_width = 0;
	// auto depth = std::int32_t { CopyFromParent };
	// auto window_class = CopyFromParent;
	// auto *visual = (Visual *)CopyFromParent;
	//
	// auto attribute_value_mask = CWBackPixel | CWEventMask;
	// auto attributes = XSetWindowAttributes {
	// 	.background_pixel = 0xffafe9af,
	// 	.event_mask = all_events_mask,
	// };
	//
	// typedef struct Hints
	// {
	// 	unsigned long flags;
	// 	unsigned long functions;
	// 	unsigned long decorations;
	// 	long inputMode;
	// 	unsigned long status;
	// } Hints;
	//
	// auto main_window = XCreateWindow(
	//     display,
	//     root_window,
	//     position.x,
	//     position.y,
	//     resolution.x,
	//     resolution.y,
	//     border_width,
	//     depth,
	//     window_class,
	//     visual,
	//     attribute_value_mask,
	//     &attributes
	// );
	// surface.m_native_data.display = display;
	// surface.m_native_data.window = main_window;
	//
	// surface.m_native_data.wm_delete_message = XInternAtom(display, "WM_DELETE_WINDOW", False);
	// XSetWMProtocols(display, main_window, &surface.m_native_data.wm_delete_message, 1);
	//
	// // code to remove decoration
	// auto hints = std::array<const unsigned char, 5> { 2, 0, 0, 0, 0 };
	// const auto motif_hints = XInternAtom(display, "_MOTIF_WM_HINTS", False);
	//
	// XChangeProperty(
	//     display,
	//     surface.m_native_data.window,
	//     motif_hints,
	//     motif_hints,
	//     32,
	//     PropModeReplace,
	//     hints.data(),
	//     5
	// );
	//
	// XMapWindow(display, main_window);
	// XStoreName(display, main_window, surface.m_title.c_str());
	// XFlush(display);
	//
	// if (!surface.is_visible())
	// {
	// 	XUnmapWindow(display, main_window);
	// }
}
catch (const std::exception &exp)
{
	log::error("Exception thrown when on_constructing surface component");
	log::error("\tentity: {}", std::uint32_t { entity });
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
	while (PeekMessage(&message, 0, {}, {}, PM_REMOVE))
	{
		switch (message.message) {}

		log::debug("Window message type: {}", std::uint32_t { message.message });
	}

	// auto event = XEvent {};
	// auto &[display, window, wm_delete_message] = surface.m_native_data;
	//
	// XFlush(display);
	// while (XEventsQueued(display, QueuedAlready) != 0)
	// {
	// 	XNextEvent(surface.m_native_data.display, &event);
	//
	// 	switch (event.type)
	// 	{
	// 	case KeyPress:
	// 	{
	// 		queue.emplace_back<KeyPressedEvent>(
	// 		    static_cast<std::uint32_t>(XLookupKeysym(&event.xkey, 0))
	// 		);
	// 		break;
	// 	}
	// 	case KeyRelease:
	// 	{
	// 		queue.emplace_back<KeyReleasedEvent>(
	// 		    static_cast<std::uint32_t>(XLookupKeysym(&event.xkey, 0))
	// 		);
	// 		break;
	// 	}
	// 	case ButtonPress:
	// 	{
	// 		queue.emplace_back<ButtonPressedEvent>(static_cast<int>(event.xbutton.button));
	// 		break;
	// 	}
	// 	case ButtonRelease:
	// 	{
	// 		queue.emplace_back<ButtonReleasedEvent>(static_cast<int>(event.xbutton.button));
	// 		break;
	// 	}
	// 	case FocusIn:
	// 	{
	// 		queue.emplace_back<GainFocusEvent>({});
	// 		break;
	// 	}
	// 	case FocusOut:
	// 	{
	// 		queue.emplace_back<LostFocusEvent>({});
	// 		break;
	// 	}
	// 	case ClientMessage:
	// 	{
	// 		if (event.xclient.data.l[0] == wm_delete_message)
	// 		{
	// 			queue.emplace_back<ClosedEvent>({});
	// 		}
	//
	// 		break;
	// 	}
	// 	case MotionNotify:
	// 	{
	// 		queue.emplace_back<MouseMovedEvent>(MouseMovedEvent {
	// 		    static_cast<float>(event.xmotion.x),
	// 		    static_cast<float>(event.xmotion.y),
	// 		});
	// 		break;
	// 	}
	// 	case ConfigureNotify:
	// 	{
	// 		const auto [prev_width, prev_height] = surface.get_resolution();
	// 		const auto new_width = event.xconfigure.width;
	// 		const auto new_height = event.xconfigure.height;
	// 		if (prev_width != new_width || prev_height != new_height)
	// 		{
	// 			surface.m_resolution.x = new_width;
	// 			surface.m_resolution.y = new_height;
	// 			queue.emplace_back<ResizedEvent>(ResizedEvent {
	// 			    static_cast<std::uint32_t>(new_width),
	// 			    static_cast<std::uint32_t>(new_height),
	// 			});
	// 		}
	//
	// 		const auto [prev_x, prev_y] = surface.get_position();
	// 		const auto new_x = event.xconfigure.x;
	// 		const auto new_y = event.xconfigure.y;
	// 		if (prev_x != new_x || prev_y != new_y)
	// 		{
	// 			surface.m_position.x = new_x;
	// 			surface.m_position.y = new_y;
	// 			queue.emplace_back<MovedEvent>(MovedEvent {
	// 			    new_x,
	// 			    new_y,
	// 			});
	// 		}
	// 		break;
	// 	}
	//
	// 	default: break; /* pass */
	// 	}
	// }
}

void System::handle_requests(SurfaceComponent &surface)
{
	const auto visitor = overloads {
		[&](const ModifyTitleRequest &request) { modify_title(surface, request); },
		[&](const ModifyResolutionRequest &request) { modify_resolution(surface, request); },
		[&](const ModifyPositionRequest &request) { modify_position(surface, request); },
		[&](const ModifyVisibilityRequest &request) { modify_visiblity(surface, request); },
		[&](const auto &) { log::error("Unknown surface request"); },
	};

	for (const auto &request : surface.peek_requests())
	{
		std::visit(visitor, request);
	}

	surface.m_requests.clear();
}

void System::modify_title(SurfaceComponent &surface, const ModifyTitleRequest &request)
{
	surface.m_title = request.title;

	// const auto &[display, window, _] = surface.get_native_data();
	// XStoreName(display, window, request.title.c_str());
}

void System::modify_resolution(SurfaceComponent &surface, const ModifyResolutionRequest &request)
{
	// surface.m_resolution = request.resolution;

	// auto &[display, window, _] = surface.m_native_data;
	// const auto &[width, height] = request.resolution;
	// // XResizeWindow(display, window, width, height);
	//
	// // get baseline serial number for X requests generated from XResizeWindow
	// auto serial = NextRequest(display);
	//
	// // request a new window size from the X server
	// XResizeWindow(
	//     display,
	//     window,
	//     static_cast<std::uint32_t>(width),
	//     static_cast<std::uint32_t>(height)
	// );
	//
	// // flush output queue and wait for X server to processes the request
	// XSync(display, False);
	// // The documentation for XResizeWindow includes this important note:
	// //
	// //   If the override-redirect flag of the window is False and some
	// //   other client has selected SubstructureRedirectMask on the parent,
	// //   the X server generates a ConfigureRequest event, and no further
	// //   processing is performed.
	// //
	// // What this means, essentially, is that if this window is a top-level
	// // window, then it's the window manager (the "other client") that is
	// // responsible for changing this window's size.  So when we call
	// // XResizeWindow() on a top-level window, then instead of resizing
	// // the window immediately, the X server informs the window manager,
	// // and then the window manager sets our new size (usually it will be
	// // the size we asked for).  We receive a ConfigureNotify event when
	// // our new size has been set.
	// constexpr auto lifespan = std::chrono::milliseconds { 10 };
	// auto timer = time::Timer {};
	// auto event = XEvent {};
	// while (!XCheckIfEvent(
	//            display,
	//            &event,
	//            XEventTypeEquals<ConfigureNotify>,
	//            reinterpret_cast<XPointer>(&window) // NOLINT
	//        )
	//        || event.xconfigure.serial < serial)
	// {
	// 	std::this_thread::sleep_for(std::chrono::microseconds { 100 });
	// 	if (timer.elapsed_time() > lifespan)
	// 	{
	// 		log::error("Timed out waiting for XResizeWindow's event");
	// 		return;
	// 	}
	// }
	// // We don't need to update the component's state and handle the event in this funcion.
	// // Since handle_requests is called before handle_events.
	// // So we just put the event back into the queue and move on.
	// XPutBackEvent(display, &event);
	// XSync(display, False);
	// XFlush(display);
}

void System::modify_position(SurfaceComponent &surface, const ModifyPositionRequest &request)
{
	// surface.m_position = request.position;

	// auto &[display, window, _] = surface.m_native_data;
	// const auto &[x, y] = request.position;
	//
	// // get baseline serial number for X requests generated from XResizeWindow
	// auto serial = NextRequest(display);
	// XMoveWindow(display, window, static_cast<int>(x), static_cast<int>(y));
	//
	// // flush output queue and wait for X server to processes the request
	// XSync(display, False);
	// constexpr auto lifespan = std::chrono::milliseconds { 10 };
	// auto timer = time::Timer {};
	// auto event = XEvent {};
	// while (!XCheckIfEvent(
	//            display,
	//            &event,
	//            XEventTypeEquals<ConfigureNotify>,
	//            reinterpret_cast<XPointer>(&window) // NOLINT
	//        )
	//        || event.xconfigure.serial < serial)
	// {
	// 	std::this_thread::sleep_for(std::chrono::microseconds { 100 });
	// 	if (timer.elapsed_time() > lifespan)
	// 	{
	// 		log::error("Timed out waiting for XMoveWindow's event");
	// 		return;
	// 	}
	// }
	// // We don't need to update the component's state and handle the event in this funcion.
	// // Since handle_requests is called before handle_events.
	// // So we just put the event back into the queue and move on.
	// XPutBackEvent(display, &event);
	// XSync(display, False);
	// XFlush(display);
}

void System::modify_visiblity(SurfaceComponent &surface, const ModifyVisibilityRequest &request)
{
	// const auto &[display, window, _] = surface.get_native_data();
	// surface.m_visible = request.visible;

	// if (request.visible)
	// {
	// 	XMapWindow(display, window);
	// }
	// else
	// {
	// 	XUnmapWindow(display, window);
	// }
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

void ensure_component_sanity(const SurfaceComponent &component)
{
	auto [width, height] = component.get_resolution();

	debug::ensure(width != 0u, "Received bad values for surface component: width({}) == 0", width);

	debug::ensure(
	    height != 0u,
	    "Received bad values for surface component: height({}) == 0",
	    height
	);

	debug::ensure(
	    width < SurfaceComponent::max_dimension,
	    "Received bad values for surface component: width({}) > max_dimension({})",
	    width,
	    SurfaceComponent::max_dimension
	);

	debug::ensure(
	    height < SurfaceComponent::max_dimension,
	    "Received bad values for surface component: height({}) > max_dimension({})",
	    height,
	    SurfaceComponent::max_dimension
	);

	debug::ensure(
	    component.get_title().size() < SurfaceComponent::max_title_length,
	    "Received bad values for surface component: title.size({}) > max_title_length({})",
	    component.get_title().size(),
	    SurfaceComponent::max_title_length
	);
}

auto CALLBACK native_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	}

	return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

#endif

} // namespace lt::surface
