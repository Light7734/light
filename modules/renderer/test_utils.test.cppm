export module renderer.test_utils;

export import test;
export import surface.system;
export import ecs.registry;
export import renderer.system;
export import math.vec2;
export import math.vec3;
export import math.vec4;
export import math.mat4;
export import renderer.vk.device;
export import renderer.vk.pass;
export import renderer.vk.instance;
export import renderer.vk.swapchain;
export import renderer.vk.renderer;
export import renderer.vk.buffer;
export import renderer.vk.gpu;
export import renderer.vk.debugger;
export import renderer.vk.surface;
export import ecs.entity;

export namespace constants {

constexpr auto resolution = lt::math::vec2_u32 { 800u, 600u };
constexpr auto frames_in_flight = u32 { 3u };

} // namespace constants


export void noop_callback(
    lt::renderer::vkb::Debugger::MessageSeverity /* unused */,
    lt::renderer::vkb::Debugger::MessageType /* unused */,
    const lt::renderer::vkb::Debugger::MessageData & /* unused */,
    std::any & /* unused */
)
{
}

export class Fixture_SurfaceSystem
{
public:
	Fixture_SurfaceSystem()
	{
		m_system.create_surface_component(
		    m_entity.id(),
		    lt::surface::SurfaceComponent::CreateInfo {
		        .title = "",
		        .resolution = constants::resolution,
		    }
		);
	}

	[[nodiscard]] auto renderer_system_create_info() -> lt::renderer::System::CreateInfo
	{
		return lt::renderer::System::CreateInfo{
		        .config = lt::renderer::System::Configuration{
                    .max_frames_in_flight = constants::frames_in_flight,
                },
                .registry = registry(),
		        .surface_entity = surface_entity(),
                .debug_callback_info = {
                    .severities = lt::renderer::vkb::Debugger::MessageSeverity::all,
                    .types= lt::renderer::vkb::Debugger::MessageType::all,
                    .callback = noop_callback,
                    .user_data = {},
                }
		    } ;
	}

	[[nodiscard]] auto registry() -> ref<lt::ecs::Registry> &
	{
		return m_registry;
	}

	[[nodiscard]] auto surface_entity() -> lt::ecs::Entity &
	{
		return m_entity;
	}

	[[nodiscard]] auto surface_system() -> lt::surface::System &
	{
		return m_system;
	}

private:
	ref<lt::ecs::Registry> m_registry = create_ref<lt::ecs::Registry>();


	lt::ecs::Entity m_entity { not_null<ref<lt::ecs::Registry>>(m_registry),
		                       m_registry->create_entity() };

	lt::surface::System m_system = lt::surface::System(m_registry);
};

export class Fixture_SurfaceGpu: public Fixture_SurfaceSystem
{
public:
	Fixture_SurfaceGpu() = default;

	[[nodiscard]] auto surface() -> lt::renderer::vkb::Surface *
	{
		return m_surface.get();
	}

	[[nodiscard]] auto gpu() -> lt::renderer::vkb::Gpu *
	{
		return m_gpu.get();
	}

private:
	scope<lt::renderer::vkb::Surface> m_surface { create_scope<lt::renderer::vkb::Surface>(
		not_null<lt::renderer::vkb::Instance *>(lt::renderer::vkb::Instance::get()),
		surface_entity()
	) };

	scope<lt::renderer::vkb::Gpu> m_gpu {
		create_scope<lt::renderer::vkb::Gpu>(lt::renderer::vkb::Instance::get())
	};
};

export class FixtureDeviceSwapchain: public Fixture_SurfaceGpu
{
public:
	FixtureDeviceSwapchain() = default;

	[[nodiscard]] auto device() -> lt::renderer::vkb::Device *
	{
		return m_device.get();
	}

	[[nodiscard]] auto swapchain() -> lt::renderer::vkb::Swapchain *
	{
		return m_swapchain.get();
	}

	void recreate_swapchain()
	{
		m_device->wait_idle();
		m_swapchain.reset();
		m_swapchain = create_scope<lt::renderer::vkb::Swapchain>(surface(), gpu(), m_device.get());
	}

	[[nodiscard]] auto has_any_messages() const -> bool
	{
		return m_user_data->m_has_any_messages;
	}

	[[nodiscard]] auto has_any_messages_of(
	    lt::renderer::vkb::Debugger ::MessageSeverity severity
	) const -> u32
	{
		return m_user_data->m_severity_counter.contains(severity);
	}

private:
	static void messenger_callback(
	    lt::renderer::vkb::Debugger::MessageSeverity severity,
	    lt::renderer::vkb::Debugger::MessageType type,
	    const lt::renderer::vkb::Debugger::MessageData &data,
	    std::any &user_data
	)
	{
		// I know this makes the tests too verbose...
		// but makes it easier to figure out what the problem is when things fail on ci
		lt::log::trace("vulkan: {}", std::string { data.message });
		ignore = data;
		ignore = type;

		auto *fixture = std::any_cast<UserData *>(user_data);
		fixture->m_has_any_messages = true;
		++fixture->m_severity_counter[severity];
	}

	struct UserData
	{
		std::unordered_map<lt::renderer::vkb::Debugger::MessageSeverity, u32> m_severity_counter;

		bool m_has_any_messages {};
	};

	scope<UserData> m_user_data = create_scope<UserData>();

	scope<lt::renderer::vkb::Debugger> m_messenger { create_scope<lt::renderer::vkb::Debugger>(
		lt::renderer::vkb::Instance::get(),
		lt::renderer::vkb::Debugger ::CreateInfo {
		    .severities = lt::renderer::vkb::Debugger::MessageSeverity::all,
		    .types = lt::renderer::vkb::Debugger::MessageType::all,
		    .callback = &messenger_callback,
		    .user_data = m_user_data.get(),
		}
	) };

	scope<lt::renderer::vkb::Device> m_device {
		create_scope<lt::renderer::vkb::Device>(gpu(), surface())
	};

	scope<lt::renderer::vkb::Swapchain> m_swapchain {
		create_scope<lt::renderer::vkb::Swapchain>(surface(), gpu(), m_device.get())
	};
};

export class Fixture_RendererSystem: public Fixture_SurfaceSystem
{
public:
	Fixture_RendererSystem() = default;

	[[nodiscard]] auto renderer_system() -> lt::renderer::System &
	{
		return m_system;
	}

	[[nodiscard]] auto has_any_messages() const -> bool
	{
		return m_user_data->m_has_any_messages;
	}

	[[nodiscard]] auto has_any_messages_of(
	    lt::renderer::vkb::Debugger ::MessageSeverity severity
	) const -> u32
	{
		return m_user_data->m_severity_counter.contains(severity);
	}

private:
	static void messenger_callback(
	    lt::renderer::vkb::Debugger::MessageSeverity severity,
	    lt::renderer::vkb::Debugger::MessageType type,
	    const lt::renderer::vkb::Debugger::MessageData &data,
	    std::any &user_data
	)
	{
		// I know this makes the tests too verbose...
		// but makes it easier to figure out what the problem is when things fail on ci
		lt::log::trace("vulkan: {}", std::string { data.message });

		ignore = data;
		ignore = type;

		auto *fixture = std::any_cast<UserData *>(user_data);
		fixture->m_has_any_messages = true;
		++fixture->m_severity_counter[severity];
	}

	struct UserData
	{
		std::unordered_map<lt::renderer::vkb::Debugger::MessageSeverity, u32> m_severity_counter;

		bool m_has_any_messages {};
	};

	scope<UserData> m_user_data = create_scope<UserData>();

	lt::renderer::System m_system = lt::renderer::System::CreateInfo {
		.config = { 
            .max_frames_in_flight = constants::frames_in_flight,
        },
		.registry = registry(),
		.surface_entity = surface_entity(),
        .debug_callback_info = lt::renderer::vkb::Debugger ::CreateInfo {
		        .severities = lt::renderer::vkb::Debugger ::MessageSeverity::all,
		        .types = lt::renderer::vkb::Debugger ::MessageType::all,
		        .callback = &messenger_callback,
		        .user_data = m_user_data.get(),
        }
	};
};
