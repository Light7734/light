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
#include <ranges>

namespace Light {

Application::Application(): m_window(nullptr)
{
	static auto constructed = false;
	lt_assert(!constructed, "Application constructed twice");
	constructed = true;

	log_debug_data();

	Light::Instrumentor::begin_session("Logs/ProfileResults_Startup.json");

	m_window = Window::create([this](auto &&PH1) { on_event(std::forward<decltype(PH1)>(PH1)); });
}

Application::~Application()
{
	log_trc("Application::~Application()");
	Instrumentor::end_session();
}

void Application::game_loop()
{
	// check
	lt_assert(!m_layer_stack->is_empty(), "layer_stack is empty");

	// log debug data
	m_window->get_graphics_context()->log_debug_data();
	m_window->get_graphics_context()->get_user_interface()->log_debug_data();

	// reveal window
	m_window->set_visibility(true);

	Instrumentor::end_session();
	Instrumentor::begin_session("Logs/ProfileResults_GameLoop.json");

	/* game loop */
	auto delta_timer = DeltaTimer {};
	while (!m_window->is_closed())
	{
		{
			// update layers
			lt_profile_scope("game_loop::update");

			for (auto &it : *m_layer_stack)
			{
				it->on_update(delta_timer.get_delta_time());
			}
		}

		{
			// render layers
			lt_profile_scope("game_loop::Render");
			m_window->get_graphics_context()->get_renderer()->begin_frame();

			for (auto &it : *m_layer_stack)
			{
				it->on_render();
			}

			m_window->get_graphics_context()->get_renderer()->end_frame();
		}

		{
			// render user interface
			lt_profile_scope("game_loop::UserInterface");
			m_window->get_graphics_context()->get_user_interface()->begin();

			for (auto &it : *m_layer_stack)
			{
				it->on_user_interface_update();
			}

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

	Instrumentor::end_session();
	Instrumentor::begin_session("Logs/ProfileResults_Termination.json");
}

void Application::quit()
{
	/** TODO: fix quitting procedure */
}

void Application::on_event(const Event &event)
{
	// window
	if (event.has_category(WindowEventCategory))
	{
		m_window->on_event(event);

		if (event.get_event_type() == EventType::WindowResized)
		{
			m_window->get_graphics_context()->get_renderer()->on_window_resize(
			    (const WindowResizedEvent &)event
			);
		}
	}

	// input
	if (event.has_category(InputEventCategory))
	{
		Input::instance().on_event(event);

		if (!Input::instance().is_receiving_game_events())
		{
			return;
		}
	}

	for (auto &it : std::ranges::reverse_view(*m_layer_stack))
	{
		if (it->on_event(event))
		{
			return;
		}
	}
}

void Application::log_debug_data()
{
	log_inf("Platform::");
	log_inf("       Platform name: {}", constants::platform_name);
	log_inf("       Platform identifier: {}", std::to_underlying(constants::platform));
	log_inf("       CWD: {}", std::filesystem::current_path().generic_string());
}

} // namespace Light
