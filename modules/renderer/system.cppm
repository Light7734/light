#pragma once

#include <app/system.hpp>
#include <ecs/entity.hpp>
#include <ecs/registry.hpp>
#include <memory/reference.hpp>
#include <memory/scope.hpp>
#include <renderer/api.hpp>
#include <renderer/frontend/messenger.hpp>

namespace lt::renderer {

/** The main rendering engine.
 *
 * Responsible for:
 * - Creating a rendering backend context (vk/dx/mt)
 * - Connecting the context to the physical devices (select gpu, create surface, logical device)
 * - Rendering the scene represented in registry via lt::renderer::components.
 *
 * @todo(Light): Add DirectX12 support
 * @todo(Light): Add Metal support
 */
class System: public app::ISystem
{
public:
	/** config.max_frames_in_flight should not be higher than this value. */
	static constexpr auto frames_in_flight_upper_limit = 5u;

	/** config.max_frames_in_flight should not be lower than this value. */
	static constexpr auto frames_in_flight_lower_limit = 1u;

	struct Configuration
	{
		Api target_api;

		uint32_t max_frames_in_flight;
	};

	struct CreateInfo
	{
		Configuration config;

		memory::Ref<ecs::Registry> registry;

		ecs::Entity surface_entity;

		IMessenger::CreateInfo debug_callback_info;
	};

	System(CreateInfo info);

	~System() override;

	System(System &&) = default;

	System(const System &) = delete;

	auto operator=(System &&) -> System & = default;

	auto operator=(const System &) -> System & = delete;

	void on_register() override;

	void on_unregister() override;

	void tick(app::TickInfo tick) override;

	[[nodiscard]] auto get_last_tick_result() const -> const app::TickResult & override
	{
		return m_last_tick_result;
	}

private:
	void handle_surface_resized_events();

	void submit_scene();

	void recreate_swapchain();

	Api m_api;

	memory::Ref<ecs::Registry> m_registry;

	ecs::Entity m_surface_entity;

	memory::Scope<class IMessenger> m_messenger;

	class IInstance *m_instance;

	memory::Scope<class ISurface> m_surface;

	memory::Scope<class IGpu> m_gpu;

	memory::Scope<class IDevice> m_device;

	memory::Scope<class ISwapchain> m_swapchain;

	memory::Scope<class IRenderer> m_renderer;

	app::TickResult m_last_tick_result {};

	uint32_t m_frame_idx {};

	uint32_t m_max_frames_in_flight {};
};

} // namespace lt::renderer

module :private;
using namespace lt::renderer;

#include <camera/components.hpp>
#include <math/algebra.hpp>
#include <math/components/transform.hpp>
#include <renderer/components/messenger.hpp>
#include <renderer/components/sprite.hpp>
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
		m_gpu.get(),
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

	handle_surface_resized_events();
	auto frame_result = m_renderer->frame(m_frame_idx, [this] { submit_scene(); });

	if (frame_result == IRenderer::Result::invalid_swapchain)
	{
		recreate_swapchain();
	}
	m_frame_idx = (m_frame_idx + 1) % m_max_frames_in_flight;
}

void System::handle_surface_resized_events()
{
	for (const auto &event : m_surface_entity.get<surface::SurfaceComponent>().peek_events())
	{
		if (std::holds_alternative<surface::ResizedEvent>(event))
		{
			m_swapchain.reset();
			m_swapchain = ISwapchain::create(m_api, m_surface.get(), m_gpu.get(), m_device.get());
			m_renderer->replace_swapchain(m_swapchain.get());

			// No need to process multiple resize events
			break;
		}
	}
}

void System::submit_scene()
{
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
	for (auto &[id, sprite, transform] :
	     m_registry->view<components::Sprite, math::components::Transform>())
	{
		m_renderer->submit_sprite(sprite, transform);
	}
}

void System::recreate_swapchain()
{
	log::trace("Re-creating swapchaain");
	m_swapchain.reset();
	m_swapchain = ISwapchain::create(m_api, m_surface.get(), m_gpu.get(), m_device.get());
	m_renderer->replace_swapchain(m_swapchain.get());
}
