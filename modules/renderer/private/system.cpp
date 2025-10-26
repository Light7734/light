#include <camera/components.hpp>
#include <math/algebra.hpp>
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

	m_messenger = IMessenger::create(m_api, m_instance, info.debug_callback_info);
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

System::~System() = default;

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

	auto perspective = math::mat4::identity();
	for (auto [id, camera] : m_registry->view<lt::camera::components::PerspectiveCamera>())
	{
		if (camera.is_primary)
		{
			perspective = math::perspective(
			    camera.vertical_fov,
			    camera.aspect_ratio,
			    camera.near_plane,
			    camera.far_plane
			);

			break;
		}
	}

	m_renderer->set_frame_constants({ .view_projection = perspective });
	if (m_renderer->draw(m_frame_idx) != IRenderer::DrawResult::success)
	{
		m_swapchain.reset();
		m_swapchain = ISwapchain::create(m_api, m_surface.get(), m_gpu.get(), m_device.get());
		m_renderer->replace_swapchain(m_swapchain.get());

		std::ignore = m_renderer->draw(m_frame_idx); // drop the frame if failed twice
	}

	m_frame_idx = (m_frame_idx + 1) % m_max_frames_in_flight;
}

} // namespace lt::renderer
