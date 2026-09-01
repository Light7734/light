export module renderer.system;


import renderer.vk.device;
import renderer.vk.pass;
import renderer.vk.instance;
import renderer.vk.swapchain;
import renderer.vk.renderer;
import renderer.vk.buffer;
import renderer.vk.gpu;
import renderer.vk.debugger;
import renderer.vk.surface;
import preliminary;
import math.formatter;
import logger;
import math.mat4;
import app.system;
import surface.events;
import ecs.entity;
import ecs.registry;
import camera.components;
import surface.system;
import renderer.components;
import math.components;
import math.algebra;
import math.trig;

export namespace lt::renderer {

/** The main rendering engine.
 *
 * Responsible for:
 * - Creating a rendering backend context (currently only Vulkan is supported)
 * - Connecting the context to the physical devices (select gpu, creating surface (a window on a
 * display/monitor), logical device (a driver))
 * - Rendering the scene represented in registry via lt::renderer::components.
 */
class System: public app::ISystem
{
public:
	// TODO(Light): this is some horrible design... fix it :(

	/** config.max_frames_in_flight should not be higher than this value. */
	static constexpr auto frames_in_flight_upper_limit = 5u;

	/** config.max_frames_in_flight should not be lower than this value. */
	static constexpr auto frames_in_flight_lower_limit = 1u;

	struct Configuration
	{
		u32 max_frames_in_flight;
	};

	struct CreateInfo
	{
		Configuration config;

		not_null<ref<ecs::Registry>> registry;

		ecs::Entity surface_entity;

		vkb::Debugger::CreateInfo debug_callback_info;
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

	ref<ecs::Registry> m_registry;

	ecs::Entity m_surface_entity;

	scope<vkb::Debugger> m_messenger;

	vkb::Instance *m_instance;

	scope<vkb::Surface> m_surface;

	scope<vkb::Gpu> m_gpu;

	scope<vkb::Device> m_device;

	scope<vkb::Swapchain> m_swapchain;

	scope<vkb::Renderer> m_renderer;

	app::TickResult m_last_tick_result {};

	u32 m_frame_idx {};

	u32 m_max_frames_in_flight {};
};

} // namespace lt::renderer

namespace lt::renderer {

System::System(CreateInfo info)
    : m_surface_entity(info.surface_entity)
    , m_registry(info.registry)
    , m_instance(vkb::Instance::get())
    , m_max_frames_in_flight(info.config.max_frames_in_flight)
{
	m_messenger = create_scope<vkb::Debugger>(
	    not_null { m_instance },
	    std::move(info.debug_callback_info)
	);
	m_surface = create_scope<vkb::Surface>(
	    not_null<vkb::Instance *>(m_instance),
	    info.surface_entity
	);
	m_gpu = create_scope<vkb::Gpu>(not_null { m_instance });

	m_device = create_scope<vkb::Device>(not_null { m_gpu.get() }, not_null { m_surface.get() });
	m_swapchain = create_scope<vkb::Swapchain>(
	    not_null { m_surface.get() },
	    not_null { m_gpu.get() },
	    not_null { m_device.get() }
	);
	m_renderer = { create_scope<vkb::Renderer>(
		not_null<vkb::Gpu *>(m_gpu.get()),
		not_null<vkb::Device *>(m_device.get()),
		not_null<vkb::Swapchain *>(m_swapchain.get()),
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
	ignore = tick;

	handle_surface_resized_events();
	auto frame_result = m_renderer->frame(m_frame_idx, [this] { submit_scene(); });

	if (frame_result == vkb::Renderer::Result::invalid_swapchain)
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
			const auto res = std::get<surface::ResizedEvent>(event).get_size();
			log::debug("Resize event received from the renderer: {}", res);

			m_renderer.reset();
			m_swapchain.reset();
			m_device.reset();
			m_gpu.reset();
			m_surface.reset();

			m_surface = create_scope<vkb::Surface>(
			    not_null<vkb::Instance *>(m_instance),
			    m_surface_entity
			);
			m_gpu = create_scope<vkb::Gpu>(not_null { m_instance });
			m_device = create_scope<vkb::Device>(
			    not_null { m_gpu.get() },
			    not_null { m_surface.get() }
			);

			m_swapchain = create_scope<vkb::Swapchain>(
			    not_null { m_surface.get() },
			    not_null { m_gpu.get() },
			    not_null { m_device.get() }
			);

			m_renderer = { create_scope<vkb::Renderer>(
				not_null<vkb::Gpu *>(m_gpu.get()),
				not_null<vkb::Device *>(m_device.get()),
				not_null<vkb::Swapchain *>(m_swapchain.get()),
				m_max_frames_in_flight
			) };

			// No need to process multiple resize events
			// TODO(Light): what am I reading here? can't there be other event types?
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
	m_swapchain = create_scope<vkb::Swapchain>(
	    not_null { m_surface.get() },
	    not_null { m_gpu.get() },
	    not_null { m_device.get() }
	);
	m_renderer->replace_swapchain(m_swapchain.get());
}

} // namespace lt::renderer
