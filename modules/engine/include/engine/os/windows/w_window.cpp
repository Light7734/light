#include <GLFW/glfw3.h>
#include <engine/events/char.hpp>
#include <engine/events/event.hpp>
#include <engine/events/keyboard.hpp>
#include <engine/events/mouse.hpp>
#include <engine/events/window.hpp>
#include <renderer/graphics_context.hpp>
#include <engine/platform/os/windows/w_window.hpp>

extern "C"
{
	// Force Machine to use Dedicated Graphics
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001; // NVidia
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;   // AMD
}

namespace Light {

Scope<Window> Window::create(std::function<void(Event &)> callback)
{
	return create_scope<wWindow>(callback);
}

wWindow::wWindow(std::function<void(Event &)> callback)
    : m_handle(nullptr)
    , m_event_callback(callback)
{
	// init glfw
	lt_assert(glfwInit(), "wWindow::wWindow: failed to initialize 'glfw'");

	// create window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	m_handle = glfwCreateWindow(1u, 1u, "", nullptr, nullptr);
	lt_assert(m_handle, "wWindow::wWindow: glfwCreateWindow: failed to create 'GLFWwindow'");

	// bind event stuff
	glfwSetWindowUserPointer(m_handle, &m_event_callback);
	bind_glfw_events();

	// create graphics context
	m_graphics_context = GraphicsContext::create(GraphicsAPI::DirectX, m_handle);
	lt_assert(m_graphics_context, "wWindow::wWindow: failed to create 'GraphicsContext'");
}

wWindow::~wWindow()
{
	glfwDestroyWindow(m_handle);
}

void wWindow::poll_events()
{
	glfwPollEvents();
}

void wWindow::on_event(const Event &event)
{
	switch (event.get_event_type())
	{
	/* closed */
	case EventType::WindowClosed: b_Closed = true; break;

	/* resized */
	case EventType::WindowResized: on_window_resize((const WindowResizedEvent &)event); break;
	}
}

void wWindow::on_window_resize(const WindowResizedEvent &event)
{
	m_properties.size = event.get_size();
}

void wWindow::
    set_properties(const WindowProperties &properties, bool overrideVisiblity /* = false */)
{
	// save the visibility status and re-assign if 'overrideVisibility' is false
	bool visible = overrideVisiblity ? properties.visible : m_properties.visible;
	m_properties = properties;
	m_properties.visible = visible;

	// set properties
	set_title(properties.title);
	set_size(properties.size);
	set_v_sync(properties.vsync);
	set_visibility(visible);
}

void wWindow::set_title(const std::string &title)
{
	m_properties.title = title;

	glfwSetWindowTitle(m_handle, m_properties.title.c_str());
}

void wWindow::set_size(const glm::uvec2 &size, bool additive /* = false */)
{
	m_properties.size.x = size.x == 0u ? m_properties.size.x :
	                      additive     ? m_properties.size.x + size.x :
	                                     size.x;
	m_properties.size.y = size.y == 0u ? m_properties.size.y :
	                      additive     ? m_properties.size.y + size.y :
	                                     size.y;


	glfwSetWindowSize(m_handle, size.x, size.y);
}

void wWindow::set_v_sync(bool vsync, bool toggle /* = false */)
{
	m_properties.vsync = toggle ? !m_properties.vsync : vsync;

	glfwSwapInterval(m_properties.vsync);
}

void wWindow::set_visibility(bool visible, bool toggle)
{
	m_properties.visible = toggle ? !m_properties.visible : visible;

	if (m_properties.visible)
		glfwShowWindow(m_handle);
	else
		glfwHideWindow(m_handle);
}

void wWindow::bind_glfw_events()
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
	//============================== WINDOW_EVENTS ==============================//	}
}
} // namespace Light
