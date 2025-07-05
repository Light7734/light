#pragma once

#include <engine/base/base.hpp>
#include <engine/core/window.hpp>

struct GLFWwindow;

namespace Light {

class Event;
class WindowResizedEvent;

class lWindow: public Window
{
public:
	lWindow(std::function<void(Event &)> callback);

	~lWindow();

	void poll_events() override;

	void on_event(const Event &event) override;

	void set_properties(const WindowProperties &properties, bool overrideVisibility = false)
	    override;

	void set_title(const std::string &title) override;

	void set_size(const glm::uvec2 &size, bool additive = false) override;

	void set_v_sync(bool vsync, bool toggle = false) override;

	void set_visibility(bool visible, bool toggle = false) override;

private:
	GLFWwindow *m_handle;

	std::function<void(Event &)> m_event_callback;

	void on_window_resize(const WindowResizedEvent &event);

	void bind_glfw_events();
};

} // namespace Light
