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
    : m_Instrumentor(nullptr)
    , m_LayerStack(nullptr)
    , m_Input(nullptr)
    , m_Window(nullptr)
{
	ASSERT(!s_Context, "Repeated singleton construction");
	s_Context = this;

	m_Logger = Logger::Create();
	LogDebugData();

	m_Instrumentor = Instrumentor::Create();
	m_Instrumentor->BeginSession("Logs/ProfileResults_Startup.json");

	m_LayerStack = LayerStack::Create();
	m_Input = Input::Create();

	m_ResourceManager = ResourceManager::Create();

	m_Window = Window::Create(std::bind(&Application::OnEvent, this, std::placeholders::_1));
}

Application::~Application()
{
	LOG(trace, "Application::~Application()");
	m_Instrumentor->EndSession(); // ProfileResults_Termination //
}

void Application::GameLoop()
{
	// check
	ASSERT(!m_LayerStack->IsEmpty(), "LayerStack is empty");

	// log debug data
	m_Logger->LogDebugData();
	m_Window->GetGfxContext()->LogDebugData();
	m_Window->GetGfxContext()->GetUserInterface()->LogDebugData();

	// reveal window
	m_Window->SetVisibility(true);

	m_Instrumentor->EndSession(); // ProfileResults_GameLoop //
	m_Instrumentor->BeginSession("Logs/ProfileResults_GameLoop.json");

	/* game loop */
	DeltaTimer deltaTimer;
	while (!m_Window->IsClosed())
	{
		{
			// update layers
			LT_PROFILE_SCOPE("GameLoop::Update");

			for (auto it = m_LayerStack->begin(); it != m_LayerStack->end(); it++)
				(*it)->OnUpdate(deltaTimer.GetDeltaTime());
		}

		{
			// render layers
			LT_PROFILE_SCOPE("GameLoop::Render");
			m_Window->GetGfxContext()->GetRenderer()->BeginFrame();

			for (auto it = m_LayerStack->begin(); it != m_LayerStack->end(); it++)
				(*it)->OnRender();

			m_Window->GetGfxContext()->GetRenderer()->EndFrame();
		}

		{
			// render user interface
			LT_PROFILE_SCOPE("GameLoop::UserInterface");
			m_Window->GetGfxContext()->GetUserInterface()->Begin();

			for (auto it = m_LayerStack->begin(); it != m_LayerStack->end(); it++)
				(*it)->OnUserInterfaceUpdate();

			m_Window->GetGfxContext()->GetUserInterface()->End();
		}

		{
			// poll events
			LT_PROFILE_SCOPE("GameLoop::Events");
			m_Window->PollEvents();
		}

		/// update delta time
		deltaTimer.Update();
	}

	m_Instrumentor->EndSession(); // ProfileResults_GameLoop //
	m_Instrumentor->BeginSession("Logs/ProfileResults_Termination.json");
}

void Application::Quit()
{
	s_Context->m_Window->Close();
}

void Application::OnEvent(const Event &event)
{
	// window
	if (event.HasCategory(WindowEventCategory))
	{
		m_Window->OnEvent(event);

		if (event.GetEventType() == EventType::WindowResized)
			m_Window->GetGfxContext()->GetRenderer()->OnWindowResize(
			    (const WindowResizedEvent &)event
			);
	}

	// input
	if (event.HasCategory(InputEventCategory))
	{
		m_Input->OnEvent(event);

		if (!m_Input->IsReceivingGameEvents()) // return if the event is an input event and 'Input'
		                                       // has disabled the game events
			return;
	}

	/* layers */
	for (auto it = m_LayerStack->rbegin(); it != m_LayerStack->rend(); it++)
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
