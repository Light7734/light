#include <logger/logger.hpp>
#include <memory/reference.hpp>
#include <memory/scope.hpp>
#include <renderer/frontend/renderer/renderer.hpp>
#include <renderer/system.hpp>
#include <renderer/test/utils.hpp>
#include <surface/components.hpp>
#include <surface/system.hpp>
#include <test/test.hpp>

using namespace lt;
using std::ignore;
using test::Case;
using test::expect_throw;
using test::Suite;

using renderer::System;

struct SurfaceContext
{
	surface::System system;
	ecs::Entity entity;
};

struct RendererContext
{
	memory::Ref<ecs::Registry> registry;
	System system;
};


Suite raii = "system_raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		ignore = Fixture_RendererSystem {};
	};

	Case { "happy path has no errors" } = [] {
		auto fixture = Fixture_RendererSystem {};
		expect_false(fixture.has_any_messages_of(renderer::IMessenger::MessageSeverity::error));
		expect_false(fixture.has_any_messages_of(renderer::IMessenger::MessageSeverity::warning));
	};

	Case { "unhappy path throws" } = [] {
		auto fixture = Fixture_SurfaceSystem {};
		auto empty_entity = ecs::Entity { fixture.registry(), fixture.registry()->create_entity() };
		auto info = fixture.renderer_system_create_info();

		expect_throw([=] mutable {
			info.registry = nullptr;
			ignore = System { info };
		});

		expect_throw([=] mutable {
			info.surface_entity = ecs::Entity({}, {});
			ignore = System { info };
		});

		expect_throw([=] mutable {
			info.config.target_api = lt::renderer::Api::none;
			ignore = System { info };
		});

		// unsupported Apis
		expect_throw([=] mutable {
			info.config.target_api = lt::renderer::Api::direct_x;
			ignore = System { info };
		});

		expect_throw([=] mutable {
			info.config.target_api = lt::renderer::Api::metal;
			ignore = System { info };
		});

		expect_throw([=] mutable {
			constexpr auto limit = lt::renderer::System::frames_in_flight_upper_limit;
			info.config.max_frames_in_flight = limit + 1u;
			ignore = System { info };
		});

		expect_throw([=] mutable {
			constexpr auto limit = lt::renderer::System::frames_in_flight_lower_limit;
			info.config.max_frames_in_flight = limit - 1u;
			ignore = System { info };
		});

		expect_throw([=] mutable {
			info.debug_callback_info = lt::renderer::IMessenger::CreateInfo {};
			ignore = System { info };
		});

		// Make sure the base info is not at fault for unhappiness.
		ignore = System { info };
	};
};
