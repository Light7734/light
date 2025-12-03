export module renderer.test_utils;

export import logger;
export import surface.system;
export import ecs.registry;
export import renderer.factory;
export import test.test;
export import test.expects;
export import memory.reference;
export import renderer.frontend;
export import renderer.system;
export import math.vec2;
export import math.vec3;
export import math.vec4;
export import math.mat4;
export import std;

export using ::lt::test::Case;
export using ::lt::test::expect_eq;
export using ::lt::test::expect_false;
export using ::lt::test::expect_not_nullptr;
export using ::lt::test::expect_throw;
export using ::lt::test::operator""_suite;
export using ::lt::test::expect_true;
export using ::lt::test::Suite;
export using ::std::ignore;

export namespace constants {

constexpr auto api = lt::renderer::Api::vulkan;
constexpr auto resolution = lt::math::uvec2 { 800u, 600u };
constexpr auto frames_in_flight = std::uint32_t { 3u };

} // namespace constants


void noop_messenger_callback(
    lt::renderer::IDebugger::MessageSeverity severity,
    lt::renderer::IDebugger::MessageType type,
    const lt::renderer::IDebugger::MessageData &data,
    std::any &user_data
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
                    .target_api = constants::api,
                    .max_frames_in_flight = constants::frames_in_flight,
                },
                .registry = registry(),
		        .surface_entity = surface_entity(),
                .debug_callback_info = {
                    .severities = lt::renderer::IDebugger::MessageSeverity::all,
                    .types= lt::renderer::IDebugger::MessageType::all,
                    .callback = noop_messenger_callback,
                    .user_data = {},
                }
		    } ;
	}

	[[nodiscard]] auto registry() -> lt::memory::Ref<lt::ecs::Registry> &
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
	lt::memory::Ref<lt::ecs::Registry> m_registry = lt::memory::create_ref<lt::ecs::Registry>();

	lt::ecs::Entity m_entity { m_registry, m_registry->create_entity() };

	lt::surface::System m_system = lt::surface::System(m_registry);
};

export class Fixture_SurfaceGpu: public Fixture_SurfaceSystem
{
public:
	Fixture_SurfaceGpu() = default;

	[[nodiscard]] auto surface() -> lt::renderer::ISurface *
	{
		return m_surface.get();
	}

	[[nodiscard]] auto gpu() -> lt::renderer::IGpu *
	{
		return m_gpu.get();
	}

private:
	lt::memory::Scope<lt::renderer::ISurface> m_surface { lt::renderer::create_surface(
		constants::api,
		lt::renderer::get_instance(constants::api),
		surface_entity()
	) };

	lt::memory::Scope<lt::renderer::IGpu> m_gpu {
		lt::renderer::create_gpu(constants::api, lt::renderer::get_instance(constants::api))
	};
};

export class FixtureDeviceSwapchain: public Fixture_SurfaceGpu
{
public:
	FixtureDeviceSwapchain() = default;

	[[nodiscard]] auto device() -> lt::renderer::IDevice *
	{
		return m_device.get();
	}

	[[nodiscard]] auto swapchain() -> lt::renderer::ISwapchain *
	{
		return m_swapchain.get();
	}

	void recreate_swapchain()
	{
		m_swapchain.reset();
		m_swapchain = lt::renderer::create_swapchain(
		    constants::api,
		    surface(),
		    gpu(),
		    m_device.get()
		);
	}

	[[nodiscard]] auto has_any_messages() const -> bool
	{
		return m_user_data->m_has_any_messages;
	}

	[[nodiscard]] auto has_any_messages_of(lt::renderer::IDebugger ::MessageSeverity severity) const
	    -> std::uint32_t
	{
		return m_user_data->m_severity_counter.contains(severity);
	}

private:
	static void messenger_callback(
	    lt::renderer::IDebugger::MessageSeverity severity,
	    lt::renderer::IDebugger::MessageType type,
	    const lt::renderer::IDebugger::MessageData &data,
	    std::any &user_data
	)
	{
		// I know this makes the tests too verbose...
		// but makes it easier to figure out what the problem is when things fail on ci
		lt::log::error("vulkan: {}", data.message);
		std::ignore = data;
		std::ignore = type;

		auto *fixture = std::any_cast<UserData *>(user_data);
		fixture->m_has_any_messages = true;
		++fixture->m_severity_counter[severity];
	}

	struct UserData
	{
		std::unordered_map<lt::renderer::IDebugger::MessageSeverity, std::uint32_t>
		    m_severity_counter;

		bool m_has_any_messages {};
	};

	lt::memory::Scope<UserData> m_user_data = lt::memory::create_scope<UserData>();

	lt::memory::Scope<lt::renderer::IDebugger> m_messenger = lt::renderer::create_debugger(
	    constants::api,
	    lt::renderer::get_instance(constants::api),
	    lt::renderer::IDebugger ::CreateInfo {
	        .severities = lt::renderer::IDebugger::MessageSeverity::all,
	        .types = lt::renderer::IDebugger::MessageType::all,
	        .callback = &messenger_callback,
	        .user_data = m_user_data.get(),
	    }
	);

	lt::memory::Scope<lt::renderer::IDevice> m_device {
		lt::renderer::create_device(constants::api, gpu(), surface())
	};

	lt::memory::Scope<lt::renderer::ISwapchain> m_swapchain {
		lt::renderer::create_swapchain(constants::api, surface(), gpu(), m_device.get())
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

	[[nodiscard]] auto has_any_messages_of(lt::renderer::IDebugger ::MessageSeverity severity) const
	    -> std::uint32_t
	{
		return m_user_data->m_severity_counter.contains(severity);
	}

private:
	static void messenger_callback(
	    lt::renderer::IDebugger::MessageSeverity severity,
	    lt::renderer::IDebugger::MessageType type,
	    const lt::renderer::IDebugger::MessageData &data,
	    std::any &user_data
	)
	{
		// I know this makes the tests too verbose...
		// but makes it easier to figure out what the problem is when things fail on ci
		lt::log::trace("vulkan: {}", data.message);

		std::ignore = data;
		std::ignore = type;

		auto *fixture = std::any_cast<UserData *>(user_data);
		fixture->m_has_any_messages = true;
		++fixture->m_severity_counter[severity];
	}

	struct UserData
	{
		std::unordered_map<lt::renderer::IDebugger::MessageSeverity, std::uint32_t>
		    m_severity_counter;

		bool m_has_any_messages {};
	};

	lt::memory::Scope<UserData> m_user_data = lt::memory::create_scope<UserData>();

	lt::renderer::System m_system = lt::renderer::System::CreateInfo {
		.config = { 
            .target_api = constants::api,
            .max_frames_in_flight = constants::frames_in_flight,
        },
		.registry = registry(),
		.surface_entity = surface_entity(),
        .debug_callback_info = lt::renderer::IDebugger ::CreateInfo {
		        .severities = lt::renderer::IDebugger ::MessageSeverity::all,
		        .types = lt::renderer::IDebugger ::MessageType::all,
		        .callback = &messenger_callback,
		        .user_data = m_user_data.get(),
        }
	};
};
