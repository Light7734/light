import logger;
import renderer.test_utils;

Suite raii = "renderer_raii"_suite = [] {
	Case { "happy paths" } = [] {
		auto fixture = FixtureDeviceSwapchain {};
		ignore = lt::renderer::vkb::Renderer(
		    not_null(fixture.gpu()),
		    not_null(fixture.device()),
		    not_null(fixture.swapchain()),
		    constants::frames_in_flight
		);

		expect_false(
		    fixture.has_any_messages_of(lt::renderer::vkb::Debugger ::MessageSeverity::error)
		);
		expect_false(
		    fixture.has_any_messages_of(lt::renderer::vkb::Debugger ::MessageSeverity::warning)
		);
	};

	Case { "unhappy paths" } = [] {
		auto fixture = FixtureDeviceSwapchain {};

		expect_throw([&] {
			ignore = lt::renderer::vkb::Renderer(
			    not_null { fixture.gpu() },
			    not_null { fixture.device() },
			    not_null { fixture.swapchain() },
			    lt::renderer::vkb::Renderer::frames_in_flight_upper_limit + 1
			);
		});

		expect_throw([&] {
			ignore = lt::renderer::vkb::Renderer(
			    not_null { fixture.gpu() },
			    not_null { fixture.device() },
			    not_null { fixture.swapchain() },
			    lt::renderer::vkb::Renderer::frames_in_flight_lower_limit - 1
			);
		});
	};
};

Suite draw = "renderer_draw"_suite = [] {
	using enum lt::renderer::vkb::Renderer::Result;

	Case { "renderer draw" } = [] {
		auto fixture = FixtureDeviceSwapchain {};
		auto renderer = lt::renderer::vkb::Renderer(
		    not_null { fixture.gpu() },
		    not_null { fixture.device() },
		    not_null { fixture.swapchain() },
		    constants::frames_in_flight
		);

		for (auto frame_idx : std::views::iota(0u, 30u))
		{
			expect_eq(renderer.frame(frame_idx % constants::frames_in_flight, [] {}), success);
		}

		expect_false(
		    fixture.has_any_messages_of(lt::renderer::vkb::Debugger ::MessageSeverity::error)
		);
		expect_false(
		    fixture.has_any_messages_of(lt::renderer::vkb::Debugger ::MessageSeverity::warning)
		);
	};

	Case { "post swapchain replacement renderer draw" } = [] {
		// auto fixture = FixtureDeviceSwapchain {};
		// auto renderer = lt::renderer::vkb::Renderer(
		//     fixture.gpu(),
		//     fixture.device(),
		//     fixture.swapchain(),
		//     constants::frames_in_flight
		// );
		//
		// for (auto frame_idx : std::views::iota(0u, 15u))
		// {
		// 	expect_eq(renderer->frame(frame_idx % constants::frames_in_flight, [] {}), success);
		// }
		//
		// fixture.recreate_swapchain();
		// renderer->replace_swapchain(fixture.swapchain());
		// for (auto frame_idx : std::views::iota(0u, 15u))
		// {
		// 	expect_eq(renderer->frame(frame_idx % constants::frames_in_flight, [] {}), success);
		// }
		//
		//
		// expect_false(fixture.has_any_messages_of(lt::renderer::vkb::Debugger::MessageSeverity::error));
		// expect_false(
		//     fixture.has_any_messages_of(lt::renderer::vkb::Debugger::MessageSeverity::warning)
		// );
	};
};
