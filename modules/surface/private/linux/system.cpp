#include <ecs/components.hpp>
#include <surface/components.hpp>
#include <surface/events/mouse.hpp>
#include <surface/requests/surface.hpp>
#include <surface/system.hpp>

//
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>

namespace lt::surface {

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

System::System(Ref<ecs::Registry> registry): m_registry(std::move(registry))
{
	ensure(m_registry, "Failed to initialize surface system: null registry");

	ensure(
	    m_registry->view<SurfaceComponent>().size() == 0,
	    "Failed to initialize surface system: registry has surface component(s)"
	);

	m_registry->get_entt_registry()
	    .on_construct<SurfaceComponent>()
	    .connect<&System::on_surface_construct>(this);

	m_registry->get_entt_registry()
	    .on_update<SurfaceComponent>()
	    .connect<&System::on_surface_update>(this);

	m_registry->get_entt_registry()
	    .on_destroy<SurfaceComponent>()
	    .connect<&System::on_surface_destroy>(this);
}

System::~System()
{
	m_registry->view<SurfaceComponent>().each([&](const entt::entity entity, SurfaceComponent &) {
		m_registry->get_entt_registry().remove<SurfaceComponent>(entity);
	});

	m_registry->get_entt_registry()
	    .on_construct<SurfaceComponent>()
	    .disconnect<&System::on_surface_construct>(this);

	m_registry->get_entt_registry()
	    .on_update<SurfaceComponent>()
	    .connect<&System::on_surface_update>(this);

	m_registry->get_entt_registry()
	    .on_destroy<SurfaceComponent>()
	    .disconnect<&System::on_surface_destroy>(this);
}

void System::on_register()
{
}

void System::on_unregister()
{
}

void System::on_surface_construct(entt::registry &registry, entt::entity entity)
{
	try
	{
		auto &surface = registry.get<SurfaceComponent>(entity);
		const auto &resolution = surface.get_resolution();
		const auto &position = surface.get_position();
		ensure_component_sanity(surface);

		// TODO(Light): refactor "environment" into standalone module
		// NOLINTNEXTLINE(concurrency-mt-unsafe)
		auto *display_env = std::getenv("DISPLAY");
		ensure(display_env != nullptr, "DISPLAY env var not found!");

		auto *display = XOpenDisplay(display_env);

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
		long hints[5] = { 2, 0, 0, 0, 0 };
		Atom motif_hints = XInternAtom(display, "_MOTIF_WM_HINTS", False);

		XChangeProperty(
		    display,
		    surface.m_native_data.window,
		    motif_hints,
		    motif_hints,
		    32,
		    PropModeReplace,
		    (unsigned char *)&hints,
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
	catch (...)
	{
		registry.remove<SurfaceComponent>(entity);
		throw;
	}
}

void System::on_surface_update(entt::registry &registry, entt::entity entity)
{
	auto &surface = registry.get<SurfaceComponent>(entity);
}

void System::on_surface_destroy(entt::registry &registry, entt::entity entity)
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

		case Expose: break;
		case GraphicsExpose: break;
		case NoExpose: break;
		case CirculateRequest: break;
		case ConfigureRequest: break;
		case MapRequest: break;
		case ResizeRequest: break;
		case CirculateNotify: break;
		case CreateNotify: break;
		case DestroyNotify: break;
		case GravityNotify: break;
		case MapNotify: break;
		case MappingNotify: break;
		case ReparentNotify: break;
		case UnmapNotify: break;
		case VisibilityNotify: break;
		case ColormapNotify: break;
		case PropertyNotify: break;
		case SelectionClear: break;
		case SelectionNotify: break;
		case SelectionRequest: break;
		default: log_inf("Unknown X Event");
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
	surface.m_resolution = request.resolution;

	const auto &[display, window, _] = surface.get_native_data();
	const auto &[width, height] = request.resolution;
	XResizeWindow(display, window, width, height);
}

void System::modify_position(SurfaceComponent &surface, const ModifyPositionRequest &request)
{
	surface.m_position = request.position;

	const auto &[display, window, _] = surface.get_native_data();
	const auto &[x, y] = request.position;
	XMoveWindow(display, window, static_cast<int>(x), static_cast<int>(y));
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

auto System::tick() -> bool
{
	m_registry->view<SurfaceComponent>().each([this](SurfaceComponent &surface) {
		handle_requests(surface);

		handle_events(surface);
	});

	return false;
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
