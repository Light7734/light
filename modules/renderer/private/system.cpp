#include <renderer/components/messenger.hpp>
#include <renderer/frontend/context/context.hpp>
#include <renderer/frontend/messenger.hpp>
#include <renderer/frontend/renderer/pass.hpp>
#include <renderer/frontend/renderer/renderer.hpp>
#include <renderer/system.hpp>
#include <surface/components.hpp>

namespace lt::renderer {

System::System(CreateInfo info)
    : m_api(info.config.target_api)
    , m_registry(std::move(info.registry))
    , m_context(IContext::create(m_api, info.surface_entity))
    , m_surface_entity(info.surface_entity)
    , m_max_frames_in_flight(info.config.max_frames_in_flight)
{
	// ensure(m_stats, "Failed to initialize system: null stats");
	ensure(m_registry, "Failed to initialize renderer system: null registry");

	m_renderer = IRenderer::create(m_api, *m_context, info.config.max_frames_in_flight);
}

System::~System()
{
}

void System::on_register()
{
}

void System::on_unregister()
{
}

void System::tick(app::TickInfo tick)
{
	std::ignore = tick;

	for (const auto &event : m_surface_entity.get<surface::SurfaceComponent>().peek_events())
	{
		if (std::holds_alternative<surface::ResizedEvent>(event))
		{
			m_context->recreate_swapchain();
			m_renderer->replace_swapchain(m_context->swapchain());
			// m_pass->replace_swapchain(m_context->swapchain());
		}
	}

	if (m_renderer->draw(m_frame_idx) != IRenderer::DrawResult::success)
	{
		m_context->recreate_swapchain();
		m_renderer->replace_swapchain(m_context->swapchain());
		// m_pass->replace_swapchain(m_context->swapchain());
		std::ignore = m_renderer->draw(m_frame_idx); // drop the frame if failed twice
	}

	m_frame_idx = (m_frame_idx + 1) % m_max_frames_in_flight;
}

void System::create_messenger_component(ecs::EntityId entity, MessengerComponent::CreateInfo info)
try
{
	auto &component = m_registry->add<MessengerComponent>(entity, std::move(info));
	component.m_implementation = IMessenger::create(
	    m_api,
	    m_context->instance(),
	    { m_registry, entity }
	);
}
catch (const std::exception &exp)
{
	log_err("Failed to create renderer::MessengerComponent:");
	log_err("\twhat: {}", exp.what());
}


} // namespace lt::renderer
