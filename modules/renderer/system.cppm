export module renderer.system;
import logger;
import debug.assertions;
import math.mat4;
import renderer.factory;
import app.system;
import surface.events;
import ecs.entity;
import ecs.registry;
import memory.reference;
import memory.scope;
import renderer.frontend;
import camera.components;
import surface.system;
import renderer.components;
import math.components;
import math.algebra;
import math.trig;
import std;

namespace lt::renderer {

/** The main rendering engine.
 *
 * Responsible for:
 * - Creating a rendering backend context (vk/dx/mt)
 * - Connecting the context to the physical devices (select gpu, create surface, logical device)
 * - Rendering the scene represented in registry via lt::renderer::components.
 */
export class System: public app::ISystem
{
public:
	/** config.max_frames_in_flight should not be higher than this value. */
	static constexpr auto frames_in_flight_upper_limit = 5u;

	/** config.max_frames_in_flight should not be lower than this value. */
	static constexpr auto frames_in_flight_lower_limit = 1u;

	struct Configuration
	{
		Api target_api;

		std::uint32_t max_frames_in_flight;
	};

	struct CreateInfo
	{
		Configuration config;

		memory::Ref<ecs::Registry> registry;

		ecs::Entity surface_entity;

		IDebugger::CreateInfo debug_callback_info;
	};

	System(CreateInfo info);

	~System() override = default;

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

	memory::Scope<IDebugger> m_messenger;

	IInstance *m_instance;

	memory::Scope<ISurface> m_surface;

	memory::Scope<IGpu> m_gpu;

	memory::Scope<IDevice> m_device;

	memory::Scope<ISwapchain> m_swapchain;

	memory::Scope<IRenderer> m_renderer;

	app::TickResult m_last_tick_result {};

	std::uint32_t m_frame_idx {};

	std::uint32_t m_max_frames_in_flight {};
};

} // namespace lt::renderer

module :private;
namespace lt::renderer {

System::System(CreateInfo info)
    : m_surface_entity(info.surface_entity)
    , m_api(info.config.target_api)
    , m_registry(std::move(info.registry))
    , m_instance(get_instance(m_api))
    , m_max_frames_in_flight(info.config.max_frames_in_flight)
{
	debug::ensure(m_registry, "Failed to initialize renderer::System: null registry");
	debug::ensure(
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

	m_messenger = create_debugger(m_api, m_instance, info.debug_callback_info);
	m_surface = create_surface(m_api, m_instance, m_surface_entity);
	m_gpu = create_gpu(m_api, m_instance);

	m_device = create_device(m_api, m_gpu.get(), m_surface.get());
	m_swapchain = create_swapchain(m_api, m_surface.get(), m_gpu.get(), m_device.get());
	m_renderer = { create_renderer(
		m_api,
		m_gpu.get(),
		m_device.get(),
		m_swapchain.get(),
		info.config.max_frames_in_flight
	) };
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
			m_swapchain = create_swapchain(m_api, m_surface.get(), m_gpu.get(), m_device.get());
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
	m_swapchain = create_swapchain(m_api, m_surface.get(), m_gpu.get(), m_device.get());
	m_renderer->replace_swapchain(m_swapchain.get());
}

} // namespace lt::renderer
