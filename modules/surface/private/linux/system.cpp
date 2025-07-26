#include <GLFW/glfw3.h>
#include <surface/system.hpp>

namespace lt::surface {

void handle_event(GLFWwindow *window, const System::Event &event)
{
	auto &callbacks = *static_cast<std::vector<System::EventCallback> *>(
	    glfwGetWindowUserPointer(window)
	);

	for (auto &callback : callbacks)
	{
		if (callback(event))
		{
			return;
		}
	}
}

void bind_glfw_events(GLFWwindow *handle)
{
	glfwSetWindowPosCallback(handle, [](GLFWwindow *window, int xpos, int ypos) {
		handle_event(window, MovedEvent { xpos, ypos });
	});

	glfwSetWindowSizeCallback(handle, [](GLFWwindow *window, int width, int height) {
		handle_event(
		    window,
		    ResizedEvent { static_cast<uint32_t>(width), static_cast<uint32_t>(height) }
		);
	});

	glfwSetWindowCloseCallback(handle, [](GLFWwindow *window) {
		handle_event(window, ClosedEvent {});
	});

	glfwSetWindowFocusCallback(handle, [](GLFWwindow *window, int focus) {
		if (focus == GLFW_TRUE)
		{
			handle_event(window, GainFocusEvent {});
		}
		else
		{
			handle_event(window, LostFocusEvent {});
		}
	});

	glfwSetCursorPosCallback(handle, [](GLFWwindow *window, double xpos, double ypos) {
		handle_event(
		    window,
		    MouseMovedEvent { static_cast<float>(xpos), static_cast<float>(ypos) }
		);
	});

	glfwSetMouseButtonCallback(
	    handle,
	    [](GLFWwindow *window, int button, int action, int /*mods*/) {
		    if (action == GLFW_PRESS)
		    {
			    handle_event(window, ButtonPressedEvent { button });
		    }
		    else if (action == GLFW_RELEASE)
		    {
			    handle_event(window, ButtonReleasedEvent { button });
		    }
	    }
	);

	glfwSetScrollCallback(handle, [](GLFWwindow *window, double /*xoffset*/, double yoffset) {
		handle_event(window, WheelScrolledEvent { static_cast<float>(yoffset) });
	});

	glfwSetKeyCallback(
	    handle,
	    [](GLFWwindow *window, int key, int /*scancode*/, int action, int /*mods*/) {
		    if (action == GLFW_PRESS)
		    {
			    handle_event(window, KeyPressedEvent { key });
		    }
		    else if (action == GLFW_RELEASE)
		    {
			    handle_event(window, KeyReleasedEvent { key });
		    }
	    }
	);

	glfwSetCharCallback(handle, [](GLFWwindow *window, unsigned int character) {
		handle_event(window, KeySetCharEvent { character });
	});
}

void System::on_surface_construct(entt::registry &registry, entt::entity entity)
{
	ensure(glfwInit(), "Failed to initialize 'glfw'");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	auto &surface = registry.get<SurfaceComponent>(entity);
	auto [width, height] = surface.get_size();

	surface.m_glfw_handle = glfwCreateWindow(
	    static_cast<int32_t>(width),
	    static_cast<int32_t>(height),
	    surface.get_title().begin(),
	    nullptr,
	    nullptr
	);
	ensure(surface.m_glfw_handle, "Failed to create 'GLFWwindow'");

	glfwSetWindowUserPointer(surface.m_glfw_handle, &m_event_callbacks);
	bind_glfw_events(surface.m_glfw_handle);
}

void System::on_surface_destroy(entt::registry &registry, entt::entity entity)
{
	auto &surface = registry.get<SurfaceComponent>(entity);
	glfwDestroyWindow(surface.m_glfw_handle);
}

void System::set_title(ecs::Entity entity, std::string_view new_title)
{
	auto &surface = entity.get_component<SurfaceComponent>();

	surface.m_title = new_title;
	glfwSetWindowTitle(surface.m_glfw_handle, surface.m_title.begin());
}

auto System::tick() -> bool
{
	glfwPollEvents();
	return false;
}

void System::set_size(ecs::Entity surface_entity, const math::uvec2 &new_size)
{
	auto &surface = surface_entity.get_component<SurfaceComponent>();
	surface.m_size = new_size;

	glfwSetWindowSize(
	    surface.m_glfw_handle,
	    static_cast<int>(new_size.x),
	    static_cast<int>(new_size.y)
	);
}

void System::set_v_sync(ecs::Entity surface_entity, bool vsync)
{
	auto &surface = surface_entity.get_component<SurfaceComponent>();
	surface.m_vsync = vsync;

	glfwSwapInterval(vsync);
}

void System::set_visibility(ecs::Entity surface_entity, bool visible)
{
	auto &surface = surface_entity.get_component<SurfaceComponent>();
	surface.m_visible = visible;

	if (visible)
	{
		glfwShowWindow(surface.m_glfw_handle);
	}
	else
	{
		glfwHideWindow(surface.m_glfw_handle);
	}
}

} // namespace lt::surface

namespace lt {

// void System::on_event(const Event &event)
// {
// 	switch (event.get_event_type())
// 	{
// 	/* closed */
// 	case EventType::WindowClosed: b_Closed = true; break;
//
// 	/* resized */
// 	case EventType::WindowResized:
// 		on_surface_resize(dynamic_cast<const WindowResizedEvent &>(event));
// 		break;
//
// 	default: break;
// 	}
// }
//
// void System::on_surface_resize(const WindowResizedEvent &event)
// {
// 	m_properties.size = event.get_size();
// }

} // namespace lt
