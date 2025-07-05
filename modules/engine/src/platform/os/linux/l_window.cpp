#include <GLFW/glfw3.h>
#include <engine/events/char.hpp>
#include <engine/events/event.hpp>
#include <engine/events/keyboard.hpp>
#include <engine/events/mouse.hpp>
#include <engine/events/window.hpp>
#include <engine/graphics/graphics_context.hpp>
#include <engine/platform/os/linux/l_window.hpp>

namespace Light {

Scope<Window> Window::Create(std::function<void(Event &)> callback)
{
	return CreateScope<lWindow>(callback);
}

lWindow::lWindow(std::function<void(Event &)> callback)
    : m_Handle(nullptr)
    , m_EventCallback(callback)
{
	// init glfw
	ASSERT(glfwInit(), "lWindow::lWindow: failed to initialize 'glfw'");

	// create window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	m_Handle = glfwCreateWindow(1u, 1u, "", nullptr, nullptr);
	ASSERT(m_Handle, "lWindow::lWindow: failed to create 'GLFWwindow'");

	// bind event stuff
	glfwSetWindowUserPointer(m_Handle, &m_EventCallback);
	BindGlfwEvents();

	// create graphics context
	m_GraphicsContext = GraphicsContext::Create(GraphicsAPI::OpenGL, m_Handle);
	ASSERT(m_GraphicsContext, "lWindow::lWindow: failed to create 'GraphicsContext'");
}

lWindow::~lWindow()
{
	glfwDestroyWindow(m_Handle);
}

void lWindow::PollEvents()
{
	glfwPollEvents();
}

void lWindow::OnEvent(const Event &event)
{
	switch (event.GetEventType())
	{
	/* closed */
	case EventType::WindowClosed: b_Closed = true; break;

	/* resized */
	case EventType::WindowResized: OnWindowResize((const WindowResizedEvent &)event); break;
	}
}

void lWindow::OnWindowResize(const WindowResizedEvent &event)
{
	m_Properties.size = event.GetSize();
}

void lWindow::
    SetProperties(const WindowProperties &properties, bool overrideVisibility /* = false */)
{
	// save the visibility status and re-assign if 'overrideVisibility' is false
	bool visible = overrideVisibility ? properties.visible : m_Properties.visible;
	m_Properties = properties;
	m_Properties.visible = visible;

	// set properties
	SetTitle(properties.title);
	SetSize(properties.size);
	SetVSync(properties.vsync);
	SetVisibility(visible);
}

void lWindow::SetTitle(const std::string &title)
{
	m_Properties.title = title;

	glfwSetWindowTitle(m_Handle, title.c_str());
}

void lWindow::SetSize(const glm::uvec2 &size, bool additive /* = false */)
{
	m_Properties.size.x = size.x == 0u ? m_Properties.size.x :
	                      additive     ? m_Properties.size.x + size.x :
	                                     size.x;
	m_Properties.size.y = size.y == 0u ? m_Properties.size.y :
	                      additive     ? m_Properties.size.y + size.y :
	                                     size.y;


	glfwSetWindowSize(m_Handle, size.x, size.y);
}

void lWindow::SetVSync(bool vsync, bool toggle /* = false */)
{
	m_Properties.vsync = toggle ? !m_Properties.vsync : vsync;

	glfwSwapInterval(m_Properties.vsync);
}

void lWindow::SetVisibility(bool visible, bool toggle)
{
	m_Properties.visible = toggle ? !m_Properties.visible : visible;

	if (m_Properties.visible)
		glfwShowWindow(m_Handle);
	else
		glfwHideWindow(m_Handle);
}

void lWindow::BindGlfwEvents()
{
	//============================== MOUSE_EVENTS ==============================//
	/* cursor position */
	glfwSetCursorPosCallback(m_Handle, [](GLFWwindow *window, double xpos, double ypos) {
		std::function<void(Event &)> callback = *(std::function<void(Event &)> *)
		                                            glfwGetWindowUserPointer(window);

		MouseMovedEvent event(xpos, ypos);
		callback(event);
	});

	/* mouse button */
	glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow *window, int button, int action, int mods) {
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
	glfwSetScrollCallback(m_Handle, [](GLFWwindow *window, double xoffset, double yoffset) {
		std::function<void(Event &)> callback = *(std::function<void(Event &)> *)
		                                            glfwGetWindowUserPointer(window);

		WheelScrolledEvent event(yoffset);
		callback(event);
	});
	//============================== MOUSE_EVENTS ==============================//

	//============================== KEYBOARD_EVENTS ==============================//
	/* key */
	glfwSetKeyCallback(
	    m_Handle,
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
	glfwSetCharCallback(m_Handle, [](GLFWwindow *window, unsigned int character) {
		std::function<void(Event &)> callback = *(std::function<void(Event &)> *)
		                                            glfwGetWindowUserPointer(window);

		SetCharEvent event(character);
		callback(event);
	});

	//============================== KEYBOARD_EVENTS ==============================//

	//============================== WINDOW_EVENTS ==============================//
	/* window position */
	glfwSetWindowPosCallback(m_Handle, [](GLFWwindow *window, int xpos, int ypos) {
		std::function<void(Event &)> callback = *(std::function<void(Event &)> *)
		                                            glfwGetWindowUserPointer(window);
		WindowMovedEvent event(xpos, ypos);

		callback(event);
	});

	/* window size */
	glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow *window, int width, int height) {
		std::function<void(Event &)> callback = *(std::function<void(Event &)> *)
		                                            glfwGetWindowUserPointer(window);
		WindowResizedEvent event(width, height);

		callback(event);
	});

	/* window close */
	glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow *window) {
		std::function<void(Event &)> callback = *(std::function<void(Event &)> *)
		                                            glfwGetWindowUserPointer(window);
		WindowClosedEvent event;

		callback(event);
	});

	/* window focus */
	glfwSetWindowFocusCallback(m_Handle, [](GLFWwindow *window, int focus) {
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
