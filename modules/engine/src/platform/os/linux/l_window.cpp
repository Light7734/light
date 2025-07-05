#include <GLFW/glfw3.h>
#include <engine/events/char.hpp>
#include <engine/events/event.hpp>
#include <engine/events/keyboard.hpp>
#include <engine/events/mouse.hpp>
#include <engine/events/window.hpp>
#include <engine/graphics/graphics_context.hpp>
#include <engine/platform/os/linux/l_window.hpp>

namespace Light {

Scope<Window> Window::create(std::function<void(Event &)> callback)
{
	return create_scope<lWindow>(callback);
}

lWindow::lWindow(std::function<void(Event &)> callback)
    : m_handle(nullptr)
    , m_event_callback(callback)
{
	// init glfw
	lt_assert(glfwInit(), "lWindow::lWindow: failed to initialize 'glfw'");

	// create window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	m_handle = glfwCreateWindow(1u, 1u, "", nullptr, nullptr);
	lt_assert(m_handle, "lWindow::lWindow: failed to create 'GLFWwindow'");

	// bind event stuff
	glfwSetWindowUserPointer(m_handle, &m_event_callback);
	bind_glfw_events();

	// create graphics context
	m_graphics_context = GraphicsContext::create(GraphicsAPI::OpenGL, m_handle);
	lt_assert(m_graphics_context, "lWindow::lWindow: failed to create 'GraphicsContext'");
}

lWindow::~lWindow()
{
	glfwDestroyWindow(m_handle);
}

void lWindow::poll_events()
{
	glfwPollEvents();
}

void lWindow::on_event(const Event &event)
{
	switch (event.get_event_type())
	{
	/* closed */
	case EventType::WindowClosed: b_Closed = true; break;

	/* resized */
	case EventType::WindowResized: on_window_resize((const WindowResizedEvent &)event); break;
	}
}

void lWindow::on_window_resize(const WindowResizedEvent &event)
{
	m_properties.size = event.get_size();
}

void lWindow::
    set_properties(const WindowProperties &properties, bool overrideVisibility /* = false */)
{
	// save the visibility status and re-assign if 'overrideVisibility' is false
	bool visible = overrideVisibility ? properties.visible : m_properties.visible;
	m_properties = properties;
	m_properties.visible = visible;

	// set properties
	set_title(properties.title);
	set_size(properties.size);
	set_v_sync(properties.vsync);
	set_visibility(visible);
}

void lWindow::set_title(const std::string &title)
{
	m_properties.title = title;

	glfwSetWindowTitle(m_handle, title.c_str());
}

void lWindow::set_size(const glm::uvec2 &size, bool additive /* = false */)
{
	m_properties.size.x = size.x == 0u ? m_properties.size.x :
	                      additive     ? m_properties.size.x + size.x :
	                                     size.x;
	m_properties.size.y = size.y == 0u ? m_properties.size.y :
	                      additive     ? m_properties.size.y + size.y :
	                                     size.y;


	glfwSetWindowSize(m_handle, size.x, size.y);
}

void lWindow::set_v_sync(bool vsync, bool toggle /* = false */)
{
	m_properties.vsync = toggle ? !m_properties.vsync : vsync;

	glfwSwapInterval(m_properties.vsync);
}

void lWindow::set_visibility(bool visible, bool toggle)
{
	m_properties.visible = toggle ? !m_properties.visible : visible;

	if (m_properties.visible)
		glfwShowWindow(m_handle);
	else
		glfwHideWindow(m_handle);
}

void lWindow::bind_glfw_events()
{
	//============================== MOUSE_EVENTS ==============================//
	/* cursor position */
	glfwSetCursorPosCallback(m_handle, [](GLFWwindow *window, double xpos, double ypos) {
		std::function<void(Event &)> callback = *(std::function<void(Event &)> *)
		                                            glfwGetWindowUserPointer(window);

		MouseMovedEvent event(xpos, ypos);
		callback(event);
	});

	/* mouse button */
	glfwSetMouseButtonCallback(m_handle, [](GLFWwindow *window, int button, int action, int mods) {
		std::function<void(Event &)> callback = *(std::function<void(Event &)> *)
		                                            glfwGetWindowUserPointer(window);

		if (action == GLFW_PRESS)
		{
			ButtonPressedEvent event(button);
			callback(event);
		}
		else if (action == GLFW_RELEASE)
		{
			ButtonReleasedEvent event(button);
			callback(event);
		}
	});

	/* scroll */
	glfwSetScrollCallback(m_handle, [](GLFWwindow *window, double xoffset, double yoffset) {
		std::function<void(Event &)> callback = *(std::function<void(Event &)> *)
		                                            glfwGetWindowUserPointer(window);

		WheelScrolledEvent event(yoffset);
		callback(event);
	});
	//============================== MOUSE_EVENTS ==============================//

	//============================== KEYBOARD_EVENTS ==============================//
	/* key */
	glfwSetKeyCallback(
	    m_handle,
	    [](GLFWwindow *window, int key, int scancode, int action, int mods) {
		    std::function<void(Event &)> callback = *(std::function<void(Event &)> *)
		                                                glfwGetWindowUserPointer(window);

		    if (action == GLFW_PRESS)
		    {
			    KeyPressedEvent event(key);
			    callback(event);
		    }
		    else if (action == GLFW_RELEASE)
		    {
			    KeyReleasedEvent event(key);
			    callback(event);
		    }
	    }
	);
	/* char */
	glfwSetCharCallback(m_handle, [](GLFWwindow *window, unsigned int character) {
		std::function<void(Event &)> callback = *(std::function<void(Event &)> *)
		                                            glfwGetWindowUserPointer(window);

		SetCharEvent event(character);
		callback(event);
	});

	//============================== KEYBOARD_EVENTS ==============================//

	//============================== WINDOW_EVENTS ==============================//
	/* window position */
	glfwSetWindowPosCallback(m_handle, [](GLFWwindow *window, int xpos, int ypos) {
		std::function<void(Event &)> callback = *(std::function<void(Event &)> *)
		                                            glfwGetWindowUserPointer(window);
		WindowMovedEvent event(xpos, ypos);

		callback(event);
	});

	/* window size */
	glfwSetWindowSizeCallback(m_handle, [](GLFWwindow *window, int width, int height) {
		std::function<void(Event &)> callback = *(std::function<void(Event &)> *)
		                                            glfwGetWindowUserPointer(window);
		WindowResizedEvent event(width, height);

		callback(event);
	});

	/* window close */
	glfwSetWindowCloseCallback(m_handle, [](GLFWwindow *window) {
		std::function<void(Event &)> callback = *(std::function<void(Event &)> *)
		                                            glfwGetWindowUserPointer(window);
		WindowClosedEvent event;

		callback(event);
	});

	/* window focus */
	glfwSetWindowFocusCallback(m_handle, [](GLFWwindow *window, int focus) {
		std::function<void(Event &)> callback = *(std::function<void(Event &)> *)
		                                            glfwGetWindowUserPointer(window);

		if (focus == GLFW_TRUE)
		{
			WindowGainFocusEvent event;
			callback(event);
		}
		else
		{
			WindowLostFocusEvent event;
			callback(event);
		}
	});
	//============================== WINDOW_EVENTS ==============================//
}

} // namespace Light
