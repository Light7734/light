#include <renderer/vk/renderer/renderer.hpp>
#include <renderer/vk/test_utils.hpp>

using ::lt::assets::ShaderAsset;
using ::lt::renderer::vk::Pass;
using ::lt::renderer::vk::Renderer;

Suite raii = "renderer_raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		auto observer = ValidationObserver {};
		auto [context, _] = create_context();

		auto pass = lt::create_ref<Pass>(
		    context,
		    ShaderAsset { "./data/test_assets/triangle.vert.asset" },
		    ShaderAsset { "./data/test_assets/triangle.frag.asset" }
		);


		auto renderer = Renderer(context, pass);

		for (;;)
		{
			renderer.draw();
		}

		expect_false(observer.had_any_messages());
	};
};
