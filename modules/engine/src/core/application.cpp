#include <engine/core/application.hpp>
#include <engine/core/window.hpp>
#include <engine/debug/instrumentor.hpp>
#include <engine/events/event.hpp>
#include <engine/graphics/graphics_context.hpp>
#include <engine/graphics/render_command.hpp>
#include <engine/graphics/renderer.hpp>
#include <engine/layer/layer.hpp>
#include <engine/time/timer.hpp>
#include <engine/user_interface/user_interface.hpp>

namespace Light {

Application *Application::s_context = nullptr;

Application::Application()
    : m_instrumentor(nullptr)
    , m_layer_stack(nullptr)
    , m_input(nullptr)
    , m_window(nullptr)
{
	lt_assert(!s_context, "Repeated singleton construction");
	s_context = this;

	m_logger = logger::create();
	log_debug_data();

	m_instrumentor = Instrumentor::create();
	m_instrumentor->begin_session("Logs/ProfileResults_Startup.json");

	m_layer_stack = LayerStack::create();
	m_input = Input::create();

	m_resource_manager = ResourceManager::create();

	m_window = Window::create(std::bind(&Application::on_event, this, std::placeholders::_1));
}

Application::~Application()
{
	lt_log(trace, "Application::~Application()");
	m_instrumentor->end_session(); // ProfileResults_Termination //
}

void Application::game_loop()
{
	// check
	lt_assert(!m_layer_stack->is_empty(), "layer_stack is empty");

	// log debug data
	m_logger->log_debug_data();
	m_window->get_graphics_context()->log_debug_data();
	m_window->get_graphics_context()->get_user_interface()->log_debug_data();

	// reveal window
	m_window->set_visibility(true);

	m_instrumentor->end_session(); // ProfileResults_GameLoop //
	m_instrumentor->begin_session("Logs/ProfileResults_GameLoop.json");

	/* game loop */
	auto delta_timer = DeltaTimer {};
	while (!m_window->is_closed())
	{
		{
			// update layers
			lt_profile_scope("game_loop::update");

			for (auto it = m_layer_stack->begin(); it != m_layer_stack->end(); it++)
				(*it)->on_update(delta_timer.get_delta_time());
		}

		{
			// render layers
			lt_profile_scope("game_loop::Render");
			m_window->get_graphics_context()->get_renderer()->begin_frame();

			for (auto it = m_layer_stack->begin(); it != m_layer_stack->end(); it++)
				(*it)->on_render();

			m_window->get_graphics_context()->get_renderer()->end_frame();
		}

		{
			// render user interface
			lt_profile_scope("game_loop::UserInterface");
			m_window->get_graphics_context()->get_user_interface()->begin();

			for (auto it = m_layer_stack->begin(); it != m_layer_stack->end(); it++)
				(*it)->on_user_interface_update();

			m_window->get_graphics_context()->get_user_interface()->end();
		}

		{
			// poll events
			lt_profile_scope("game_loop::Events");
			m_window->poll_events();
		}

		/// update delta time
		delta_timer.update();
	}

	m_instrumentor->end_session(); // ProfileResults_GameLoop //
	m_instrumentor->begin_session("Logs/ProfileResults_Termination.json");
}

void Application::quit()
{
	s_context->m_window->close();
}

void Application::on_event(const Event &event)
{
	// window
	if (event.has_category(WindowEventCategory))
	{
		m_window->on_event(event);

		if (event.get_event_type() == EventType::WindowResized)
			m_window->get_graphics_context()->get_renderer()->on_window_resize(
			    (const WindowResizedEvent &)event
			);
	}

	// input
	if (event.has_category(InputEventCategory))
	{
		m_input->on_event(event);

		if (!m_input->is_receiving_game_events()) // return if the event is an input event and
		                                          // 'Input' has disabled the game events
			return;
	}

	/* layers */
	for (auto it = m_layer_stack->rbegin(); it != m_layer_stack->rend(); it++)
		if ((*it)->on_event(event))
			return;
}

void Application::log_debug_data()
{
	// #todo: log more information
	lt_log(info, "________________________________________");
	lt_log(info, "Platform::");
	lt_log(info, "        OS: {}", LT_BUILD_PLATFORM);
	lt_log(info, "       DIR: {}", std::filesystem::current_path().generic_string());
	lt_log(info, "________________________________________");
}

} // namespace Light
