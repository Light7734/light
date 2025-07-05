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

Application *Application::s_Context = nullptr;

Application::Application()
    : m_instrumentor(nullptr)
    , m_layer_stack(nullptr)
    , m_input(nullptr)
    , m_window(nullptr)
{
	ASSERT(!s_Context, "Repeated singleton construction");
	s_Context = this;

	m_logger = Logger::Create();
	LogDebugData();

	m_instrumentor = Instrumentor::Create();
	m_instrumentor->BeginSession("Logs/ProfileResults_Startup.json");

	m_layer_stack = LayerStack::Create();
	m_input = Input::Create();

	m_resource_manager = ResourceManager::Create();

	m_window = Window::Create(std::bind(&Application::OnEvent, this, std::placeholders::_1));
}

Application::~Application()
{
	LOG(trace, "Application::~Application()");
	m_instrumentor->EndSession(); // ProfileResults_Termination //
}

void Application::GameLoop()
{
	// check
	ASSERT(!m_layer_stack->IsEmpty(), "LayerStack is empty");

	// log debug data
	m_logger->LogDebugData();
	m_window->GetGfxContext()->LogDebugData();
	m_window->GetGfxContext()->GetUserInterface()->LogDebugData();

	// reveal window
	m_window->SetVisibility(true);

	m_instrumentor->EndSession(); // ProfileResults_GameLoop //
	m_instrumentor->BeginSession("Logs/ProfileResults_GameLoop.json");

	/* game loop */
	DeltaTimer deltaTimer;
	while (!m_window->IsClosed())
	{
		{
			// update layers
			LT_PROFILE_SCOPE("GameLoop::Update");

			for (auto it = m_layer_stack->begin(); it != m_layer_stack->end(); it++)
				(*it)->OnUpdate(deltaTimer.GetDeltaTime());
		}

		{
			// render layers
			LT_PROFILE_SCOPE("GameLoop::Render");
			m_window->GetGfxContext()->GetRenderer()->BeginFrame();

			for (auto it = m_layer_stack->begin(); it != m_layer_stack->end(); it++)
				(*it)->OnRender();

			m_window->GetGfxContext()->GetRenderer()->EndFrame();
		}

		{
			// render user interface
			LT_PROFILE_SCOPE("GameLoop::UserInterface");
			m_window->GetGfxContext()->GetUserInterface()->Begin();

			for (auto it = m_layer_stack->begin(); it != m_layer_stack->end(); it++)
				(*it)->OnUserInterfaceUpdate();

			m_window->GetGfxContext()->GetUserInterface()->End();
		}

		{
			// poll events
			LT_PROFILE_SCOPE("GameLoop::Events");
			m_window->PollEvents();
		}

		/// update delta time
		deltaTimer.Update();
	}

	m_instrumentor->EndSession(); // ProfileResults_GameLoop //
	m_instrumentor->BeginSession("Logs/ProfileResults_Termination.json");
}

void Application::Quit()
{
	s_Context->m_window->Close();
}

void Application::OnEvent(const Event &event)
{
	// window
	if (event.HasCategory(WindowEventCategory))
	{
		m_window->OnEvent(event);

		if (event.GetEventType() == EventType::WindowResized)
			m_window->GetGfxContext()->GetRenderer()->OnWindowResize(
			    (const WindowResizedEvent &)event
			);
	}

	// input
	if (event.HasCategory(InputEventCategory))
	{
		m_input->OnEvent(event);

		if (!m_input->IsReceivingGameEvents()) // return if the event is an input event and 'Input'
		                                       // has disabled the game events
			return;
	}

	/* layers */
	for (auto it = m_layer_stack->rbegin(); it != m_layer_stack->rend(); it++)
		if ((*it)->OnEvent(event))
			return;
}

void Application::LogDebugData()
{
	// #todo: log more information
	LOG(info, "________________________________________");
	LOG(info, "Platform::");
	LOG(info, "        OS: {}", LT_BUILD_PLATFORM);
	LOG(info, "       DIR: {}", std::filesystem::current_path().generic_string());
	LOG(info, "________________________________________");
}

} // namespace Light
