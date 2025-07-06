#pragma once

#include <engine/base/base.hpp>
#include <engine/debug/instrumentor.hpp>
#include <engine/input/input.hpp>
#include <engine/layer/layer_stack.hpp>
#include <engine/utils/resource_manager.hpp>

namespace Light {

class Window;
class Event;
class Instrumentor;

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
	static Application *s_context;

	Scope<logger> m_logger;

	Scope<Instrumentor> m_instrumentor;

	Scope<LayerStack> m_layer_stack;

	Scope<Input> m_input;

	Scope<ResourceManager> m_resource_manager;

	void on_event(const Event &event);

	void log_debug_data();
};

extern Application *create_application();

} // namespace Light
