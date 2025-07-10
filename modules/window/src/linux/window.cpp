#include <GLFW/glfw3.h>
#include <input/events/char.hpp>
#include <input/events/event.hpp>
#include <input/events/keyboard.hpp>
#include <input/events/mouse.hpp>
#include <input/events/window.hpp>
#include <window/linux/window.hpp>

namespace lt {

Window::~Window()
{
}

auto Window::create(const std::function<void(Event &)> &callback) -> Scope<Window>
{
	return create_scope<lWindow>(callback);
}

lWindow::lWindow(std::function<void(Event &)> callback)
    : m_event_callback(std::move(std::move(callback)))
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

	glfwSetWindowUserPointer(m_handle, &m_event_callback);
	bind_glfw_events();
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
	case EventType::WindowResized:
		on_window_resize(dynamic_cast<const WindowResizedEvent &>(event));
		break;
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
	auto visible = overrideVisibility ? properties.visible : m_properties.visible;
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
	{
		glfwShowWindow(m_handle);
	}
	else
	{
		glfwHideWindow(m_handle);
	}
}

void lWindow::bind_glfw_events()
{
	glfwSetCursorPosCallback(m_handle, [](GLFWwindow *window, double xpos, double ypos) {
		auto callback = *(std::function<void(Event &)> *)glfwGetWindowUserPointer(window);

		auto event = MouseMovedEvent {
			static_cast<float>(xpos),
			static_cast<float>(ypos),
		};
		callback(event);
	});

	glfwSetMouseButtonCallback(
	    m_handle,
	    [](GLFWwindow *window, int button, int action, int /*mods*/) {
		    std::function<void(Event &)> const callback = *(std::function<void(Event &)> *)
		                                                      glfwGetWindowUserPointer(window);

		    if (action == GLFW_PRESS)
		    {
			    auto event = ButtonPressedEvent { button };
			    callback(event);
		    }
		    else if (action == GLFW_RELEASE)
		    {
			    auto event = ButtonReleasedEvent { button };
			    callback(event);
		    }
	    }
	);

	glfwSetScrollCallback(m_handle, [](GLFWwindow *window, double /*xoffset*/, double yoffset) {
		auto callback = *(std::function<void(Event &)> *)glfwGetWindowUserPointer(window);

		auto event = WheelScrolledEvent { static_cast<float>(yoffset) };
		callback(event);
	});

	glfwSetKeyCallback(
	    m_handle,
	    [](GLFWwindow *window, int key, int /*scancode*/, int action, int /*mods*/) {
		    auto callback = *(std::function<void(Event &)> *)glfwGetWindowUserPointer(window);

		    if (action == GLFW_PRESS)
		    {
			    auto event = KeyPressedEvent { key };
			    callback(event);
		    }
		    else if (action == GLFW_RELEASE)
		    {
			    auto event = KeyReleasedEvent { key };
			    callback(event);
		    }
	    }
	);

	glfwSetCharCallback(m_handle, [](GLFWwindow *window, unsigned int character) {
		auto callback = *(std::function<void(Event &)> *)glfwGetWindowUserPointer(window);

		auto event = SetCharEvent { character };
		callback(event);
	});

	glfwSetWindowPosCallback(m_handle, [](GLFWwindow *window, int xpos, int ypos) {
		auto callback = *(std::function<void(Event &)> *)glfwGetWindowUserPointer(window);
		auto event = WindowMovedEvent { xpos, ypos };

		callback(event);
	});

	glfwSetWindowSizeCallback(m_handle, [](GLFWwindow *window, int width, int height) {
		auto callback = *(std::function<void(Event &)> *)glfwGetWindowUserPointer(window);
		auto event = WindowResizedEvent {
			static_cast<unsigned int>(width),
			static_cast<unsigned int>(height),
		};

		callback(event);
	});

	glfwSetWindowCloseCallback(m_handle, [](GLFWwindow *window) {
		auto callback = *(std::function<void(Event &)> *)glfwGetWindowUserPointer(window);
		auto event = WindowClosedEvent {};

		callback(event);
	});

	glfwSetWindowFocusCallback(m_handle, [](GLFWwindow *window, int focus) {
		auto callback = *(std::function<void(Event &)> *)glfwGetWindowUserPointer(window);

		if (focus == GLFW_TRUE)
		{
			auto event = WindowGainFocusEvent {};
			callback(event);
		}
		else
		{
			auto event = WindowLostFocusEvent {};
			callback(event);
		}
	});
}

} // namespace lt
