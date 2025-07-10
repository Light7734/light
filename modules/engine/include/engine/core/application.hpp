#pragma once


#include <engine/layer/layer_stack.hpp>
#include <input/input.hpp>

namespace lt {

class Renderer;
class Window;
class Event;
class UserInterface;
class GraphicsContext;

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

	Scope<UserInterface> m_user_interface;

	Scope<GraphicsContext> m_graphics_context;

	Scope<Renderer> m_renderer;

	static Application *s_instance;
};


} // namespace lt
