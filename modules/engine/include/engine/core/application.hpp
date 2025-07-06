#pragma once

#include <engine/base/base.hpp>
#include <engine/input/input.hpp>
#include <engine/layer/layer_stack.hpp>

namespace Light {

class Window;
class Event;

class Application
{
public:
	Application(const Application &) = delete;

	Application &operator=(const Application &) = delete;

	virtual ~Application();

	void game_loop();

	static void quit();

protected:
	Application();

	Scope<Window> m_window;

private:
	void on_event(const Event &event);

	void log_debug_data();

	Scope<LayerStack> m_layer_stack;
};

extern Light::Scope<Application> create_application();

} // namespace Light
