#pragma once

#include <engine/base/base.hpp>
#include <engine/input/input.hpp>
#include <engine/layer/layer_stack.hpp>

namespace Light {

class Window;
class Event;

extern Scope<class Application> create_application();

class Application
{
public:
	Application(const Application &) = delete;

	Application(Application &&) = delete;

	auto operator=(const Application &) -> Application & = delete;

	auto operator=(Application &&) -> Application & = delete;

	virtual ~Application();

	void game_loop();

	[[nodiscard]] auto get_window() -> Window &
	{
		return *m_window;
	}

	static void quit();

protected:
	Application();

private:
	void on_event(const Event &event);

	void log_debug_data();

	Scope<Window> m_window;

	static Application *s_instance;
};


} // namespace Light
