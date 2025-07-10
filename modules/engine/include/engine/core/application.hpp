#pragma once

#include <engine/layer/layer_stack.hpp>
#include <engine/time/timer.hpp>
#include <input/input.hpp>
#include <ui/ui.hpp>

namespace lt {

class Renderer;
class Window;
class Event;
class GraphicsContext;

extern Scope<class Application> create_application();

class Application
{
public:
	Application(const Application &) = delete;

	Application(Application &&) = delete;

	auto operator=(const Application &) -> Application & = delete;

	auto operator=(Application &&) -> Application & = delete;

	virtual ~Application() = default;

	[[nodiscard]] auto sanity_check() const -> bool;

	void game_loop();

	[[nodiscard]] auto get_window() -> Window &
	{
		return *m_window;
	}

	[[nodiscard]] auto get_layer_stack() -> LayerStack &
	{
		return *m_layer_stack;
	}

	static void quit();

protected:
	Application();

private:
	void update_layers();

	void render_layers();

	void render_user_interface();

	void poll_events();

	void on_event(const Event &event);

	void log_debug_data() const;

	Timer m_timer;

	Scope<Window> m_window;

	Scope<UserInterface> m_user_interface;

	Scope<GraphicsContext> m_graphics_context;

	Scope<Renderer> m_renderer;

	Scope<LayerStack> m_layer_stack;

	static Application *s_instance;
};


} // namespace lt
