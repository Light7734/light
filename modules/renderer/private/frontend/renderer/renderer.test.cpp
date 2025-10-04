#include <renderer/vk/renderer/renderer.hpp>
#include <renderer/vk/test_utils.hpp>

using ::lt::assets::ShaderAsset;
using ::lt::renderer::vk::Pass;
using ::lt::renderer::vk::Renderer;

Suite raii = "renderer_raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		auto observer = ValidationObserver {};
		auto [context, _] = create_context();

		std::ignore = Renderer(
		    context,
		    lt::create_ref<Pass>(
		        context,
		        ShaderAsset { "./data/test_assets/triangle.vert.asset" },
		        ShaderAsset { "./data/test_assets/triangle.frag.asset" }
		    )
		);

		expect_false(observer.had_any_messages());
	};
};

Suite draw = "renderer_draw"_suite = [] {
	Case { "renderer draw" } = [] {
		auto observer = ValidationObserver {};
		auto [context, _] = create_context();

		auto renderer = Renderer(
		    context,
		    lt::create_ref<Pass>(
		        context,
		        ShaderAsset { "./data/test_assets/triangle.vert.asset" },
		        ShaderAsset { "./data/test_assets/triangle.frag.asset" }
		    )
		);

		for (auto frame_idx : std::views::iota(0u, 30u))
		{
			expect_true(renderer.draw(frame_idx % Renderer::max_frames_in_flight));
		}
		expect_false(observer.had_any_messages());
	};

	Case { "post swapchain replacement renderer draw" } = [] {
		auto observer = ValidationObserver {};
		auto [context, _] = create_context();
		auto pass = lt::create_ref<Pass>(
		    context,
		    ShaderAsset { "./data/test_assets/triangle.vert.asset" },
		    ShaderAsset { "./data/test_assets/triangle.frag.asset" }
		);

		auto renderer = Renderer { context, pass };

		for (auto frame_idx : std::views::iota(0u, 15u))
		{
			expect_true(renderer.draw(frame_idx % Renderer::max_frames_in_flight));
		}

		context.recreate_swapchain();
		renderer.replace_swapchain(context.swapchain());
		pass->replace_swapchain(context.swapchain());
		for (auto frame_idx : std::views::iota(0u, 15u))
		{
			expect_true(renderer.draw(frame_idx % Renderer::max_frames_in_flight));
		}

		expect_false(observer.had_any_messages());
	};
};
