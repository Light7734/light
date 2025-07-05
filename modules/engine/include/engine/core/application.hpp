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

class Application /* singleton */
{
private:
	static Application *s_Context;

private:
	Scope<logger> m_logger;
	Scope<Instrumentor> m_instrumentor;
	Scope<LayerStack> m_layer_stack;
	Scope<Input> m_input;
	Scope<ResourceManager> m_resource_manager;

protected:
	Scope<Window> m_window;

public:
	Application(const Application &) = delete;
	Application &operator=(const Application &) = delete;

	virtual ~Application();

	void game_loop();

	// To be defined in client project

	static void quit();

protected:
	Application();

private:
	void on_event(const Event &event);

	void log_debug_data();
};

extern Application *CreateApplication();

} // namespace Light
