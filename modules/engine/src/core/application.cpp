#include <asset_manager/asset_manager.hpp>
#include <debug/assertions.hpp>
#include <engine/core/application.hpp>
#include <engine/core/window.hpp>
#include <engine/debug/instrumentor.hpp>
#include <engine/layer/layer.hpp>
#include <engine/time/timer.hpp>
#include <input/events/event.hpp>
#include <input/events/keyboard.hpp>
#include <input/events/window.hpp>
#include <ranges>
#include <renderer/blender.hpp>
#include <renderer/graphics_context.hpp>
#include <renderer/render_command.hpp>
#include <renderer/renderer.hpp>
#include <ui/ui.hpp>

namespace lt {

Application *Application::s_instance = nullptr;

Application::Application(): m_window(nullptr)
{
	lt_assert(!s_instance, "Application constructed twice");
	s_instance = this;

	log_debug_data();

	lt::Instrumentor::begin_session("data/logs/profile_startup.json");

	m_window = Window::create([this](auto &&PH1) { on_event(std::forward<decltype(PH1)>(PH1)); });

	// create graphics context
	m_graphics_context = GraphicsContext::create(
	    GraphicsAPI::OpenGL,
	    (GLFWwindow *)m_window->get_handle()
	);

	AssetManager::load_shader(
	    "LT_ENGINE_RESOURCES_TEXTURE_SHADER",
	    "data/assets/shaders/texture/vs.asset",
	    "data/assets/shaders/texture/ps.asset"
	);

	AssetManager::load_shader(
	    "LT_ENGINE_RESOURCES_TINTED_TEXTURE_SHADER",
	    "data/assets/shaders/tinted_texture/vs.asset",
	    "data/assets/shaders/tinted_texture/ps.asset"
	);

	AssetManager::load_shader(
	    "LT_ENGINE_RESOURCES_QUAD_SHADER",
	    "data/assets/shaders/quads/vs.asset",
	    "data/assets/shaders/quads/ps.asset"
	);

	m_renderer = Renderer::create(
	    (GLFWwindow *)m_window->get_handle(),
	    m_graphics_context->get_shared_context(),
	    Renderer::CreateInfo {
	        .quad_renderer_shader = AssetManager::get_shader("LT_ENGINE_RESOURCES_QUAD_SHADER"),
	        .texture_renderer_shader = AssetManager::get_shader("LT_ENGINE_RESOURCES_TEXTURE_SHADER"
	        ),
	        .tinted_texture_renderer_shader = AssetManager::get_shader("LT_ENGINE_RESOURCES_TINTED_"
	                                                                   "TEXTURE_SHADER"),
	    }
	);
	lt_assert(m_graphics_context, "lWindow::lWindow: failed to create 'GraphicsContext'");

	m_user_interface = UserInterface::create(
	    (GLFWwindow *)m_window->get_handle(),
	    m_graphics_context->get_shared_context()
	);
}

Application::~Application()
{
	log_trc("Application::~Application()");
	Instrumentor::end_session();
}

void Application::game_loop()
{
	// check
	lt_assert(!LayerStack::instance().is_empty(), "layer_stack is empty");

	// log debug data
	m_graphics_context->log_debug_data();
	m_user_interface->log_debug_data();

	// reveal window
	m_window->set_visibility(true);

	Instrumentor::end_session();
	Instrumentor::begin_session("data/logs/profile_game_loop.json");

	/* game loop */
	auto timer = Timer {};
	while (!m_window->is_closed())
	{
		{
			// update layers
			lt_profile_scope("game_loop::update");

			for (auto &it : LayerStack::instance())
			{
				it->on_update(timer.get_elapsed_time());
			}

			// TODO: each layer should have their own "delta time"
			timer.reset();
		}

		{
			// render layers
			lt_profile_scope("game_loop::Render");
			m_renderer->begin_frame();

			for (auto &it : LayerStack::instance())
			{
				it->on_render();
			}

			m_renderer->end_frame();
		}

		{
			// render user interface
			lt_profile_scope("game_loop::UserInterface");
			m_user_interface->begin();

			for (auto &it : LayerStack::instance())
			{
				it->on_user_interface_update();
			}

			m_user_interface->end();
		}

		{
			// poll events
			lt_profile_scope("game_loop::Events");
			m_window->poll_events();
		}
	}

	Instrumentor::end_session();
	Instrumentor::begin_session("data/logs/profile_cleanup.json");
}

void Application::quit()
{
	s_instance->m_window->close();
}

void Application::on_event(const Event &event)
{
	// window
	if (event.has_category(WindowEventCategory))
	{
		m_window->on_event(event);

		if (event.get_event_type() == EventType::WindowResized)
		{
			m_renderer->on_window_resize(dynamic_cast<const WindowResizedEvent &>(event));
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

	for (auto &it : std::ranges::reverse_view(LayerStack::instance()))
	{
		if (it->on_event(event))
		{
			return;
		}
	}
}

[[nodiscard]] auto Application::sanity_check() const -> bool
{
	// TODO(Light): verify sanity of the application state
	return true;
}

void Application::log_debug_data()
{
	log_inf("Platform::");
	log_inf("       Platform name: {}", constants::platform_name);
	log_inf("       Platform identifier: {}", std::to_underlying(constants::platform));
	log_inf("       CWD: {}", std::filesystem::current_path().generic_string());
}

} // namespace lt
