#include <renderer/vk/renderer/pass.hpp>
#include <renderer/vk/test_utils.hpp>

using ::lt::assets::ShaderAsset;
using ::lt::renderer::vk::Pass;

Suite raii = "pass_raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		auto observer = ValidationObserver {};
		auto [context, _] = create_context();

		std::ignore = Pass {
			context,
			ShaderAsset { "./data/test_assets/triangle.vert.asset" },
			ShaderAsset { "./data/test_assets/triangle.frag.asset" },
		};

		expect_false(observer.had_any_messages());
	};
};
