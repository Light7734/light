#pragma once

#include <memory/reference.hpp>
#include <renderer/components/messenger.hpp>
#include <renderer/frontend/context/device.hpp>
#include <renderer/frontend/context/gpu.hpp>
#include <renderer/frontend/context/instance.hpp>
#include <renderer/frontend/context/surface.hpp>
#include <renderer/frontend/context/swapchain.hpp>
#include <renderer/frontend/messenger.hpp>
#include <renderer/system.hpp>
#include <surface/components.hpp>
#include <surface/system.hpp>
#include <test/test.hpp>

using ::lt::test::Case;
using ::lt::test::expect_eq;
using ::lt::test::expect_false;
using ::lt::test::expect_not_nullptr;
using ::lt::test::expect_throw;
using ::lt::test::expect_true;
using ::lt::test::Suite;
using ::std::ignore;

namespace constants {

constexpr auto api = lt::renderer::Api::vulkan;
constexpr auto resolution = lt::math::uvec2 { 800u, 600u };
constexpr auto frames_in_flight = uint32_t { 3u };

} // namespace constants


inline void noop_messenger_callback(
    lt::renderer::IMessenger::MessageSeverity severity,
    lt::renderer::IMessenger::MessageType type,
    const lt::renderer::IMessenger::MessageData &data,
    std::any &user_data
)
{
}

class Fixture_SurfaceSystem
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
                    .severities = lt::renderer::IMessenger::MessageSeverity::all,
                    .types= lt::renderer::IMessenger::MessageType::all,
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

class Fixture_SurfaceGpu: public Fixture_SurfaceSystem
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
	lt::memory::Scope<lt::renderer::ISurface> m_surface { lt::renderer::ISurface::create(
		constants::api,
		lt::renderer::IInstance::get(constants::api),
		surface_entity()
	) };

	lt::memory::Scope<lt::renderer::IGpu> m_gpu {
		lt::renderer::IGpu::create(constants::api, lt::renderer::IInstance::get(constants::api))
	};
};

class FixtureDeviceSwapchain: public Fixture_SurfaceGpu
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
		m_swapchain = lt::renderer::ISwapchain::create(
		    constants::api,
		    surface(),
		    gpu(),
		    m_device.get()
		);
	}

private:
	lt::memory::Scope<lt::renderer::IDevice> m_device {
		lt::renderer::IDevice::create(constants::api, gpu(), surface())
	};

	lt::memory::Scope<lt::renderer::ISwapchain> m_swapchain {
		lt::renderer::ISwapchain::create(constants::api, surface(), gpu(), m_device.get())
	};
};

class Fixture_RendererSystem: public Fixture_SurfaceSystem
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
	    lt::renderer::IMessenger ::MessageSeverity severity
	) const -> uint32_t
	{
		return m_user_data->m_severity_counter.contains(severity);
	}

private:
	static void messenger_callback(
	    lt::renderer::IMessenger::MessageSeverity severity,
	    lt::renderer::IMessenger::MessageType type,
	    const lt::renderer::IMessenger::MessageData &data,
	    std::any &user_data
	)
	{
		std::ignore = data;
		std::ignore = type;

		auto *fixture = std::any_cast<UserData *>(user_data);
		fixture->m_has_any_messages = true;
		++fixture->m_severity_counter[severity];
	}

	struct UserData
	{
		std::unordered_map<lt::renderer::IMessenger::MessageSeverity, uint32_t> m_severity_counter;

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
        .debug_callback_info = lt::renderer::IMessenger ::CreateInfo {
		        .severities = lt::renderer::IMessenger ::MessageSeverity::all,
		        .types = lt::renderer::IMessenger ::MessageType::all,
		        .callback = &messenger_callback,
		        .user_data = m_user_data.get(),
        }
	};
};
