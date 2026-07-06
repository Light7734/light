import preliminary;
import time;
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
	Case { "happy paths" } = [] {
		auto fixture = Fixture_RendererSystem {};
		expect_false(
		    fixture.has_any_messages_of(lt::renderer::vkb::Debugger::MessageSeverity::error)
		);
		expect_false(
		    fixture.has_any_messages_of(lt::renderer::vkb::Debugger::MessageSeverity::warning)
		);
	};

	Case { "unhappy paths" } = [] {
		auto fixture = Fixture_SurfaceSystem {};
		auto empty_entity = lt::ecs::Entity { fixture.registry(),
			                                  fixture.registry()->create_entity() };
		auto info = fixture.renderer_system_create_info();

		expect_throw([=] mutable {
			info.registry = nullptr;
			ignore = lt::renderer::System { info };
		});

		expect_throw([=] mutable {
			info.surface_entity = lt::ecs::Entity({}, {});
			ignore = lt::renderer::System { info };
		});

		expect_throw([=] mutable {
			constexpr auto limit = lt::renderer::System::frames_in_flight_upper_limit;
			info.config.max_frames_in_flight = limit + 1u;
			ignore = lt::renderer::System { info };
		});

		expect_throw([=] mutable {
			constexpr auto limit = lt::renderer::System::frames_in_flight_lower_limit;
			info.config.max_frames_in_flight = limit - 1u;
			ignore = lt::renderer::System { info };
		});

		expect_throw([=] mutable {
			info.debug_callback_info = lt::renderer::vkb::Debugger::CreateInfo {};
			ignore = lt::renderer::System { info };
		});

		// Make sure the base info is not at fault for unhappiness.
		ignore = lt::renderer::System { info };
	};
};
