#pragma once

#include <window/window.hpp>

struct GLFWwindow;

namespace lt {

class Event;
class WindowResizedEvent;

class lWindow: public Window
{
public:
	lWindow(std::function<void(Event &)> callback);

	~lWindow() override;

	lWindow(lWindow &&) = delete;

	lWindow(const lWindow &) = delete;

	auto operator=(lWindow &&) -> lWindow & = delete;

	auto operator=(const lWindow &) -> lWindow & = delete;

	void poll_events() override;

	void on_event(const Event &event) override;

	void set_properties(const Properties &properties, bool overrideVisibility = false) override;

	void set_title(const std::string &title) override;

	void set_size(const glm::uvec2 &size) override;

	void set_v_sync(bool vsync, bool toggle = false) override;

	void set_visibility(bool visible, bool toggle = false) override;

	[[nodiscard]] auto get_handle() -> void * override
	{
		return m_handle;
	}

private:
	void on_window_resize(const WindowResizedEvent &event);

	void bind_glfw_events();

	GLFWwindow *m_handle { nullptr };

	std::function<void(Event &)> m_event_callback;

	Properties m_properties {};

	bool b_Closed {};
};

} // namespace lt
