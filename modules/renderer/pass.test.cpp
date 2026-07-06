import renderer.vk.pass;
import assets.shader;
import renderer.test_utils;

Suite raii = "pass_raii"_suite = [] {
	Case { "happy paths" } = [] {
		auto fixture = FixtureDeviceSwapchain {};
		ignore = lt::renderer::vkb::Pass(
		    fixture.device(),
		    lt::assets::ShaderAsset { "./data/test_assets/triangle.vert.asset" },
		    lt::assets::ShaderAsset { "./data/test_assets/triangle.frag.asset" }
		);

		expect_false(
		    fixture.has_any_messages_of(lt::renderer::vkb::Debugger ::MessageSeverity::error)
		);
		expect_false(
		    fixture.has_any_messages_of(lt::renderer::vkb::Debugger ::MessageSeverity::warning)
		);
	};

	Case { "unhappy paths" } = [] {
	};
};
