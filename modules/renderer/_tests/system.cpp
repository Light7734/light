import time;
import renderer.frontend;
import renderer.test_utils;

struct SurfaceContext
{
	lt::surface::System system;

	lt::ecs::Entity entity;
};

struct RendererContext
{
	lt::memory::Ref<lt::ecs::Registry> registry;

	lt::renderer::System system;
};

Suite raii = "system_raii"_suite = [] {
	Case { "sandbox" } = [] {
		auto fixture = Fixture_RendererSystem {};
		auto &surface_system = fixture.surface_system();
		auto &renderer_system = fixture.renderer_system();

		auto timer = lt::time::Timer {};
		lt::log::trace("Ticking for 3 seconds...");

		while (timer.elapsed_time() < std::chrono::seconds { 3 })
		{
			surface_system.tick({});
			renderer_system.tick({});
		}

		lt::log::trace("Three seconds passed, quitting...");
	};

	// Case { "happy path won't throw" } = [] {
	// 	ignore = Fixture_RendererSystem {};
	//
	//
	// 	auto timer = lt::time::Timer {};
	// 	lt::log::trace("Ticking for 3 seconds...");
	// 	while (timer.elapsed_time() < std::chrono::seconds { 3 })
	// 	{
	// 		system.tick({});
	// 	}
	//
	// 	lt::log::trace("Three seconds passed, quitting...");
	// };
	//
	// Case { "happy path has no errors" } = [] {
	// 	auto fixture = Fixture_RendererSystem {};
	// 	expect_false(fixture.has_any_messages_of(lt::renderer::IDebugger::MessageSeverity::error));
	// 	expect_false(
	// 	    fixture.has_any_messages_of(lt::renderer::IDebugger::MessageSeverity::warning)
	// 	);
	// };
	//
	// Case { "unhappy path throws" } = [] {
	// 	auto fixture = Fixture_SurfaceSystem {};
	// 	auto empty_entity = lt::ecs::Entity { fixture.registry(),
	// 		                                  fixture.registry()->create_entity() };
	// 	auto info = fixture.renderer_system_create_info();
	//
	// 	expect_throw([=] mutable {
	// 		info.registry = nullptr;
	// 		ignore = lt::renderer::System { info };
	// 	});
	//
	// 	expect_throw([=] mutable {
	// 		info.surface_entity = lt::ecs::Entity({}, {});
	// 		ignore = lt::renderer::System { info };
	// 	});
	//
	// 	expect_throw([=] mutable {
	// 		info.config.target_api = lt::renderer::Api::none;
	// 		ignore = lt::renderer::System { info };
	// 	});
	//
	// 	// unsupported Apis
	// 	expect_throw([=] mutable {
	// 		info.config.target_api = lt::renderer::Api::direct_x;
	// 		ignore = lt::renderer::System { info };
	// 	});
	//
	// 	expect_throw([=] mutable {
	// 		info.config.target_api = lt::renderer::Api::metal;
	// 		ignore = lt::renderer::System { info };
	// 	});
	//
	// 	expect_throw([=] mutable {
	// 		constexpr auto limit = lt::renderer::System::frames_in_flight_upper_limit;
	// 		info.config.max_frames_in_flight = limit + 1u;
	// 		ignore = lt::renderer::System { info };
	// 	});
	//
	// 	expect_throw([=] mutable {
	// 		constexpr auto limit = lt::renderer::System::frames_in_flight_lower_limit;
	// 		info.config.max_frames_in_flight = limit - 1u;
	// 		ignore = lt::renderer::System { info };
	// 	});
	//
	// 	expect_throw([=] mutable {
	// 		info.debug_callback_info = lt::renderer::IDebugger::CreateInfo {};
	// 		ignore = lt::renderer::System { info };
	// 	});
	//
	// 	// Make sure the base info is not at fault for unhappiness.
	// 	ignore = lt::renderer::System { info };
	// };
};
