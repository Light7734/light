import renderer.frontend;
import renderer.test_utils;

Suite raii = "pass_raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		auto fixture = FixtureDeviceSwapchain {};
		std::ignore = lt::renderer::create_pass(
		    constants::api,
		    fixture.device(),
		    lt::assets::ShaderAsset { "./data/test_assets/triangle.vert.asset" },
		    lt::assets::ShaderAsset { "./data/test_assets/triangle.frag.asset" }
		);

		expect_false(fixture.has_any_messages_of(lt::renderer::IDebugger ::MessageSeverity::error));
		expect_false(
		    fixture.has_any_messages_of(lt::renderer::IDebugger ::MessageSeverity::warning)
		);
	};

	Case { "unhappy path throws" } = [] {
		auto fixture = FixtureDeviceSwapchain {};
		expect_throw([&] {
			std::ignore = lt::renderer::create_pass(
			    constants::api,
			    nullptr,
			    lt::assets::ShaderAsset { "./data/test_assets/triangle.vert.asset" },
			    lt::assets::ShaderAsset { "./data/test_assets/triangle.frag.asset" }
			);
		});

		expect_throw([&] {
			std::ignore = lt::renderer::create_pass(
			    lt::renderer::Api::none,
			    fixture.device(),
			    lt::assets::ShaderAsset { "./data/test_assets/triangle.vert.asset" },
			    lt::assets::ShaderAsset { "./data/test_assets/triangle.frag.asset" }
			);
		});

		expect_throw([&] {
			std::ignore = lt::renderer::create_pass(
			    lt::renderer::Api::direct_x,
			    fixture.device(),
			    lt::assets::ShaderAsset { "./data/test_assets/triangle.vert.asset" },
			    lt::assets::ShaderAsset { "./data/test_assets/triangle.frag.asset" }
			);
		});

		expect_throw([&] {
			std::ignore = lt::renderer::create_pass(
			    lt::renderer::Api::metal,
			    fixture.device(),
			    lt::assets::ShaderAsset { "./data/test_assets/triangle.vert.asset" },
			    lt::assets::ShaderAsset { "./data/test_assets/triangle.frag.asset" }
			);
		});
	};
};
