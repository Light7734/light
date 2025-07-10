#include <asset_manager/asset_manager.hpp>
#include <debug/assertions.hpp>
#include <engine/core/application.hpp>
#include <engine/layer/layer.hpp>
#include <engine/layer/layer_stack.hpp>
#include <engine/time/timer.hpp>
#include <input/events/event.hpp>
#include <input/events/keyboard.hpp>
#include <input/events/window.hpp>
#include <input/input.hpp>
#include <ranges>
#include <renderer/blender.hpp>
#include <renderer/graphics_context.hpp>
#include <renderer/render_command.hpp>
#include <renderer/renderer.hpp>
#include <ui/ui.hpp>
#include <window/linux/window.hpp>

namespace lt {

Application *Application::s_instance = nullptr;

Application::Application(): m_window(nullptr)
{
	ensure(!s_instance, "Application constructed twice");
	s_instance = this;

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
	ensure(m_graphics_context, "lWindow::lWindow: failed to create 'GraphicsContext'");

	m_user_interface = UserInterface::create(
	    (GLFWwindow *)m_window->get_handle(),
	    m_graphics_context->get_shared_context()
	);

	m_layer_stack = create_scope<LayerStack>();
}

Application::~Application()
{
	/** This is required to make forward-declarations possible:
	 * https://stackoverflow.com/questions/34072862/why-is-error-invalid-application-of-sizeof-to-an-incomplete-type-using-uniqu
	 */
}

void Application::game_loop()
{
	m_window->set_visibility(true);

	while (!m_window->is_closed())
	{
		update_layers();
		render_layers();
		render_user_interface();
		poll_events();
	}
}

void Application::quit()
{
	s_instance->m_window->close();
}

void Application::update_layers()
{
	for (auto &it : *m_layer_stack)
	{
		it->on_update(m_timer.get_elapsed_time());
	}

	// TODO(Light): each layer should have their own "delta time"
	m_timer.reset();
}

void Application::render_layers()
{
	m_renderer->begin_frame();

	for (auto &it : *m_layer_stack)
	{
		it->on_render();
	}

	m_renderer->end_frame();
}

void Application::render_user_interface()
{
	m_user_interface->begin();

	for (auto &it : *m_layer_stack)
	{
		it->on_user_interface_update();
	}

	m_user_interface->end();
}

void Application::poll_events()
{
	m_window->poll_events();
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

	for (auto &it : std::ranges::reverse_view(*m_layer_stack))
	{
		if (it->on_event(event))
		{
			return;
		}
	}
}

[[nodiscard]] auto Application::sanity_check() const -> bool
{
	log_inf("Checking application sanity...");
	ensure(s_instance, "Application not constructed!?");
	ensure(m_window, "Window is not initialized");
	ensure(m_user_interface, "User interface is not initialized");
	ensure(m_graphics_context, "Graphics context is not initialized");
	ensure(m_renderer, "Renderer is not initialized");
	ensure(m_layer_stack, "Layer_stack is not initialized");
	ensure(!m_layer_stack->is_empty(), "Layer_stack is empty");

	log_inf("Logging application state...");
	this->log_debug_data();
	m_graphics_context->log_debug_data();
	m_user_interface->log_debug_data();

	return true;
}

void Application::log_debug_data() const
{
	log_inf("Platform::");
	log_inf("       Platform name: {}", constants::platform_name);
	log_inf("       Platform identifier: {}", std::to_underlying(constants::platform));
	log_inf("       CWD: {}", std::filesystem::current_path().generic_string());
}

} // namespace lt
