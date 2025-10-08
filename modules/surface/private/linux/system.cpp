#include <memory/reference.hpp>
#include <surface/components.hpp>
#include <surface/events/mouse.hpp>
#include <surface/requests/surface.hpp>
#include <surface/system.hpp>
#include <time/timer.hpp>

//
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>

namespace lt::surface {

template<int EventType>
int XEventTypeEquals(Display *, XEvent *event, XPointer winptr)
{
	return (
	    event->type == EventType
	    && *(reinterpret_cast<Window *>(winptr)) == reinterpret_cast<XAnyEvent *>(event)->window
	);
}

template<class... Ts>
struct overloads: Ts...
{
	using Ts::operator()...;
};

void ensure_component_sanity(const SurfaceComponent &component);

constexpr auto all_events_mask = KeyPressMask |         //
                                 KeyReleaseMask |       //
                                 ButtonPressMask |      //
                                 ButtonReleaseMask |    //
                                 EnterWindowMask |      //
                                 LeaveWindowMask |      //
                                 PointerMotionMask |    //
                                 KeymapStateMask |      //
                                 ExposureMask |         //
                                 VisibilityChangeMask | //
                                 StructureNotifyMask |  //
                                 FocusChangeMask |      //
                                 ColormapChangeMask |   //
                                 OwnerGrabButtonMask;

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
}

System::~System()
{
	if (!m_registry)
	{
		return;
	}

	try
	{
		// TODO(Light): make registry.remove not validate iterators
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
		log_err("Uncaught exception in surface::~System:");
		log_err("\twhat: {}", exp.what());
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

	// TODO(Light): refactor "environment" into standalone module
	// NOLINTNEXTLINE(concurrency-mt-unsafe)
	auto *display_env = std::getenv("DISPLAY");
	ensure(display_env != nullptr, "DISPLAY env var not found!");

	auto *display = XOpenDisplay(display_env);
	ensure(display, "Failed to open XDisplay with DISPLAY: {}", display_env);

	auto root_window = XDefaultRootWindow(display);

	auto border_width = 0;
	auto depth = int32_t { CopyFromParent };
	auto window_class = CopyFromParent;
	auto *visual = (Visual *)CopyFromParent;

	auto attribute_value_mask = CWBackPixel | CWEventMask;
	auto attributes = XSetWindowAttributes {
		.background_pixel = 0xffafe9af,
		.event_mask = all_events_mask,
	};

	typedef struct Hints
	{
		unsigned long flags;
		unsigned long functions;
		unsigned long decorations;
		long inputMode;
		unsigned long status;
	} Hints;

	auto main_window = XCreateWindow(
	    display,
	    root_window,
	    position.x,
	    position.y,
	    resolution.x,
	    resolution.y,
	    border_width,
	    depth,
	    window_class,
	    visual,
	    attribute_value_mask,
	    &attributes
	);
	surface.m_native_data.display = display;
	surface.m_native_data.window = main_window;

	surface.m_native_data.wm_delete_message = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display, main_window, &surface.m_native_data.wm_delete_message, 1);

	// code to remove decoration
	auto hints = std::array<unsigned char, 5> { 2, 0, 0, 0, 0 };
	const auto motif_hints = XInternAtom(display, "_MOTIF_WM_HINTS", False);

	XChangeProperty(
	    display,
	    surface.m_native_data.window,
	    motif_hints,
	    motif_hints,
	    32,
	    PropModeReplace,
	    hints.data(),
	    5
	);

	XMapWindow(display, main_window);
	XStoreName(display, main_window, surface.m_title.c_str());
	XFlush(display);

	if (!surface.is_visible())
	{
		XUnmapWindow(display, main_window);
	}
}
catch (const std::exception &exp)
{
	log_err("Exception thrown when on_constructing surface component");
	log_err("\tentity: {}", entity);
	log_err("\twhat: {}", exp.what());
	m_registry->remove<SurfaceComponent>(entity);
}

void System::on_surface_destruct(ecs::Registry &registry, ecs::EntityId entity)
{
	const auto &[display, window, _] = registry.get<SurfaceComponent>(entity).get_native_data();
	if (!display)
	{
		log_wrn("Surface component destroyed with null display");
		return;
	}

	XDestroyWindow(display, window);
	XCloseDisplay(display);
}

void System::handle_events(SurfaceComponent &surface)
{
	auto &queue = surface.m_event_queue;
	queue.clear();

	auto event = XEvent {};
	auto &[display, window, wm_delete_message] = surface.m_native_data;

	XFlush(display);
	while (XEventsQueued(display, QueuedAlready) != 0)
	{
		XNextEvent(surface.m_native_data.display, &event);

		switch (event.type)
		{
		case KeyPress:
		{
			queue.emplace_back<KeyPressedEvent>(
			    static_cast<uint32_t>(XLookupKeysym(&event.xkey, 0))
			);
			break;
		}
		case KeyRelease:
		{
			queue.emplace_back<KeyReleasedEvent>(
			    static_cast<uint32_t>(XLookupKeysym(&event.xkey, 0))
			);
			break;
		}
		case ButtonPress:
		{
			queue.emplace_back<ButtonPressedEvent>(static_cast<int>(event.xbutton.button));
			break;
		}
		case ButtonRelease:
		{
			queue.emplace_back<ButtonReleasedEvent>(static_cast<int>(event.xbutton.button));
			break;
		}
		case FocusIn:
		{
			queue.emplace_back<GainFocusEvent>({});
			break;
		}
		case FocusOut:
		{
			queue.emplace_back<LostFocusEvent>({});
			break;
		}
		case ClientMessage:
		{
			if (event.xclient.data.l[0] == wm_delete_message)
			{
				queue.emplace_back<ClosedEvent>({});
			}

			break;
		}
		case MotionNotify:
		{
			queue.emplace_back<MouseMovedEvent>(MouseMovedEvent {
			    static_cast<float>(event.xmotion.x),
			    static_cast<float>(event.xmotion.y),
			});
			break;
		}
		case ConfigureNotify:
		{
			const auto [prev_width, prev_height] = surface.get_resolution();
			const auto new_width = event.xconfigure.width;
			const auto new_height = event.xconfigure.height;
			if (prev_width != new_width || prev_height != new_height)
			{
				surface.m_resolution.x = new_width;
				surface.m_resolution.y = new_height;
				queue.emplace_back<ResizedEvent>(ResizedEvent {
				    static_cast<uint32_t>(new_width),
				    static_cast<uint32_t>(new_height),
				});
			}

			const auto [prev_x, prev_y] = surface.get_position();
			const auto new_x = event.xconfigure.x;
			const auto new_y = event.xconfigure.y;
			if (prev_x != new_x || prev_y != new_y)
			{
				surface.m_position.x = new_x;
				surface.m_position.y = new_y;
				queue.emplace_back<MovedEvent>(MovedEvent {
				    new_x,
				    new_y,
				});
			}
			break;
		}

		default: break; /* pass */
		}
	}
}

void System::handle_requests(SurfaceComponent &surface)
{
	const auto visitor = overloads {
		[&](const ModifyTitleRequest &request) { modify_title(surface, request); },
		[&](const ModifyResolutionRequest &request) { modify_resolution(surface, request); },
		[&](const ModifyPositionRequest &request) { modify_position(surface, request); },
		[&](const ModifyVisibilityRequest &request) { modify_visiblity(surface, request); },
		[&](const auto &) { log_err("Unknown surface request"); },
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

	const auto &[display, window, _] = surface.get_native_data();
	XStoreName(display, window, request.title.c_str());
}

void System::modify_resolution(SurfaceComponent &surface, const ModifyResolutionRequest &request)
{
	// surface.m_resolution = request.resolution;

	auto &[display, window, _] = surface.m_native_data;
	const auto &[width, height] = request.resolution;
	// XResizeWindow(display, window, width, height);

	// get baseline serial number for X requests generated from XResizeWindow
	uint64_t serial = NextRequest(display);

	// request a new window size from the X server
	XResizeWindow(display, window, static_cast<uint32_t>(width), static_cast<uint32_t>(height));

	// flush output queue and wait for X server to processes the request
	XSync(display, False);
	// The documentation for XResizeWindow includes this important note:
	//
	//   If the override-redirect flag of the window is False and some
	//   other client has selected SubstructureRedirectMask on the parent,
	//   the X server generates a ConfigureRequest event, and no further
	//   processing is performed.
	//
	// What this means, essentially, is that if this window is a top-level
	// window, then it's the window manager (the "other client") that is
	// responsible for changing this window's size.  So when we call
	// XResizeWindow() on a top-level window, then instead of resizing
	// the window immediately, the X server informs the window manager,
	// and then the window manager sets our new size (usually it will be
	// the size we asked for).  We receive a ConfigureNotify event when
	// our new size has been set.
	constexpr auto lifespan = std::chrono::milliseconds { 10 };
	auto timer = Timer {};
	auto event = XEvent {};
	while (!XCheckIfEvent(
	           display,
	           &event,
	           XEventTypeEquals<ConfigureNotify>,
	           reinterpret_cast<XPointer>(&window) // NOLINT
	       )
	       || event.xconfigure.serial < serial)
	{
		std::this_thread::sleep_for(std::chrono::microseconds { 100 });
		if (timer.elapsed_time() > lifespan)
		{
			log_err("Timed out waiting for XResizeWindow's event");
			return;
		}
	}
	// We don't need to update the component's state and handle the event in this funcion.
	// Since handle_requests is called before handle_events.
	// So we just put the event back into the queue and move on.
	XPutBackEvent(display, &event);
	XSync(display, False);
	XFlush(display);
}

void System::modify_position(SurfaceComponent &surface, const ModifyPositionRequest &request)
{
	// surface.m_position = request.position;

	auto &[display, window, _] = surface.m_native_data;
	const auto &[x, y] = request.position;

	// get baseline serial number for X requests generated from XResizeWindow
	uint64_t serial = NextRequest(display);
	XMoveWindow(display, window, static_cast<int>(x), static_cast<int>(y));

	// flush output queue and wait for X server to processes the request
	XSync(display, False);
	constexpr auto lifespan = std::chrono::milliseconds { 10 };
	auto timer = Timer {};
	auto event = XEvent {};
	while (!XCheckIfEvent(
	           display,
	           &event,
	           XEventTypeEquals<ConfigureNotify>,
	           reinterpret_cast<XPointer>(&window) // NOLINT
	       )
	       || event.xconfigure.serial < serial)
	{
		std::this_thread::sleep_for(std::chrono::microseconds { 100 });
		if (timer.elapsed_time() > lifespan)
		{
			log_err("Timed out waiting for XMoveWindow's event");
			return;
		}
	}
	// We don't need to update the component's state and handle the event in this funcion.
	// Since handle_requests is called before handle_events.
	// So we just put the event back into the queue and move on.
	XPutBackEvent(display, &event);
	XSync(display, False);
	XFlush(display);
}

void System::modify_visiblity(SurfaceComponent &surface, const ModifyVisibilityRequest &request)
{
	const auto &[display, window, _] = surface.get_native_data();
	surface.m_visible = request.visible;

	if (request.visible)
	{
		XMapWindow(display, window);
	}
	else
	{
		XUnmapWindow(display, window);
	}
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

namespace lt {

} // namespace lt
