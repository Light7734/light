#include <renderer/components/messenger.hpp>
#include <renderer/frontend/context/device.hpp>
#include <renderer/frontend/context/gpu.hpp>
#include <renderer/frontend/context/instance.hpp>
#include <renderer/frontend/context/surface.hpp>
#include <renderer/frontend/context/swapchain.hpp>
#include <renderer/frontend/messenger.hpp>
#include <renderer/frontend/renderer/pass.hpp>
#include <renderer/frontend/renderer/renderer.hpp>
#include <renderer/system.hpp>
#include <surface/components.hpp>

namespace lt::renderer {

System::System(CreateInfo info)
    : m_surface_entity(info.surface_entity)
    , m_api(info.config.target_api)
    , m_registry(std::move(info.registry))
    , m_instance(IInstance::get(m_api))
    , m_max_frames_in_flight(info.config.max_frames_in_flight)
{
	ensure(m_registry, "Failed to initialize renderer::System: null registry");
	ensure(
	    std::clamp(
	        info.config.max_frames_in_flight,
	        frames_in_flight_lower_limit,
	        frames_in_flight_upper_limit
	    ) == info.config.max_frames_in_flight,
	    "Failed to initialize renderer::System: max_frames_in_flight ({}) not within bounds ({} -> "
	    "{}) ",
	    info.config.max_frames_in_flight,
	    frames_in_flight_lower_limit,
	    frames_in_flight_upper_limit
	);

	if (info.messenger_info.has_value())
	{
		ensure(
		    create_messenger_component(m_registry->create_entity(), info.messenger_info.value()),
		    "Failed to initialize renderer::System: failed to create messenger component"
		);
	}
	else
	{
		log_wrn(
		    "Creating renderer::System without a default messenger component, this is not "
		    "recommended"
		);
	}

	m_surface = ISurface::create(m_api, m_instance, m_surface_entity);
	m_gpu = IGpu::create(m_api, m_instance);
	m_device = IDevice::create(m_api, m_gpu.get(), m_surface.get());
	m_swapchain = ISwapchain::create(m_api, m_surface.get(), m_gpu.get(), m_device.get());
	m_renderer = { IRenderer::create(
		m_api,
		m_device.get(),
		m_swapchain.get(),
		info.config.max_frames_in_flight
	) };
}

System::~System()
{
	auto entities_to_remove = std::vector<ecs::EntityId> {};
	for (auto &[entity, surface] : m_registry->view<MessengerComponent>())
	{
		entities_to_remove.emplace_back(entity);
	}

	for (auto entity : entities_to_remove)
	{
		m_registry->remove<MessengerComponent>(entity);
	}
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
			m_swapchain.reset();
			m_swapchain = ISwapchain::create(m_api, m_surface.get(), m_gpu.get(), m_device.get());
			m_renderer->replace_swapchain(m_swapchain.get());
		}
	}

	if (m_renderer->draw(m_frame_idx) != IRenderer::DrawResult::success)
	{
		m_swapchain.reset();
		m_swapchain = ISwapchain::create(m_api, m_surface.get(), m_gpu.get(), m_device.get());
		m_renderer->replace_swapchain(m_swapchain.get());

		std::ignore = m_renderer->draw(m_frame_idx); // drop the frame if failed twice
	}

	m_frame_idx = (m_frame_idx + 1) % m_max_frames_in_flight;
}

[[nodiscard]] auto System::create_messenger_component(
    ecs::EntityId entity,
    MessengerComponent::CreateInfo info
) -> bool
try
{
	auto &component = m_registry->add<MessengerComponent>(entity, std::move(info));
	component.m_implementation = IMessenger::create(m_api, m_instance, { m_registry, entity });
	// component.m_user_data = info.user_data;
	return true;
}
catch (const std::exception &exp)
{
	log_err("Failed to create renderer::MessengerComponent:");
	log_err("\twhat: {}", exp.what());
	m_registry->remove<MessengerComponent>(entity);
	return false;
}


} // namespace lt::renderer
