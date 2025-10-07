#include <memory/reference.hpp>
#include <renderer/frontend/renderer/renderer.hpp>
#include <renderer/test/utils.hpp>

Suite raii = "renderer_raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		auto fixture = FixtureDeviceSwapchain {};
		ignore = lt::renderer::IRenderer::create(
		    constants::api,
		    fixture.device(),
		    fixture.swapchain(),
		    constants::frames_in_flight
		);
	};

	Case { "unhappy path throws" } = [] {
		auto fixture = FixtureDeviceSwapchain {};

		expect_throw([&] {
			ignore = lt::renderer::IRenderer::create(
			    constants::api,
			    nullptr,
			    fixture.swapchain(),
			    constants::frames_in_flight
			);
		});

		expect_throw([&] {
			ignore = lt::renderer::IRenderer::create(
			    constants::api,
			    fixture.device(),
			    nullptr,
			    constants::frames_in_flight
			);
		});

		expect_throw([&] {
			ignore = lt::renderer::IRenderer::create(
			    constants::api,
			    fixture.device(),
			    nullptr,
			    lt::renderer::IRenderer::frames_in_flight_upper_limit + 1
			);
		});

		expect_throw([&] {
			ignore = lt::renderer::IRenderer::create(
			    constants::api,
			    fixture.device(),
			    nullptr,
			    lt::renderer::IRenderer::frames_in_flight_lower_limit - 1
			);
		});
	};
};

Suite draw = "renderer_draw"_suite = [] {
	using enum lt::renderer::IRenderer::DrawResult;

	Case { "renderer draw" } = [] {
		auto fixture = FixtureDeviceSwapchain {};
		auto renderer = lt::renderer::IRenderer::create(
		    constants::api,
		    fixture.device(),
		    fixture.swapchain(),
		    constants::frames_in_flight
		);

		for (auto frame_idx : std::views::iota(0u, 30u))
		{
			expect_eq(renderer->draw(frame_idx % constants::frames_in_flight), success);
		}
	};

	Case { "post swapchain replacement renderer draw" } = [] {
		auto fixture = FixtureDeviceSwapchain {};
		auto renderer = lt::renderer::IRenderer::create(
		    constants::api,
		    fixture.device(),
		    fixture.swapchain(),
		    constants::frames_in_flight
		);

		for (auto frame_idx : std::views::iota(0u, 15u))
		{
			expect_eq(renderer->draw(frame_idx % constants::frames_in_flight), success);
		}

		fixture.recreate_swapchain();
		renderer->replace_swapchain(fixture.swapchain());
		for (auto frame_idx : std::views::iota(0u, 15u))
		{
			expect_eq(renderer->draw(frame_idx % constants::frames_in_flight), success);
		}
	};
};
