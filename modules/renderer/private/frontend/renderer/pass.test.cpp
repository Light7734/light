#include <assets/shader.hpp>
#include <renderer/frontend/messenger.hpp>
#include <renderer/frontend/renderer/pass.hpp>
#include <renderer/test/utils.hpp>

using ::lt::renderer::IMessenger;

Suite raii = "pass_raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		auto fixture = Fixture_RendererSystem {};
		auto &system = fixture.renderer_system();

		std::ignore = lt::renderer::IPass::create(
		    constants::api,
		    system.get_device(),
		    system.get_swapchain(),
		    lt::assets::ShaderAsset { "./data/test_assets/triangle.vert.asset" },
		    lt::assets::ShaderAsset { "./data/test_assets/triangle.frag.asset" }
		);

		expect_false(fixture.has_any_messages_of(IMessenger ::MessageSeverity::error));
		expect_false(fixture.has_any_messages_of(IMessenger ::MessageSeverity::warning));
	};

	Case { "unhappy path throws" } = [] {
		auto fixture = Fixture_RendererSystem {};
		auto &system = fixture.renderer_system();

		expect_throw([&] {
			std::ignore = lt::renderer::IPass::create(
			    constants::api,
			    nullptr,
			    system.get_swapchain(),
			    lt::assets::ShaderAsset { "./data/test_assets/triangle.vert.asset" },
			    lt::assets::ShaderAsset { "./data/test_assets/triangle.frag.asset" }
			);
		});


		expect_throw([&] {
			std::ignore = lt::renderer::IPass::create(
			    constants::api,
			    system.get_device(),
			    nullptr,
			    lt::assets::ShaderAsset { "./data/test_assets/triangle.vert.asset" },
			    lt::assets::ShaderAsset { "./data/test_assets/triangle.frag.asset" }
			);
		});

		expect_throw([&] {
			std::ignore = lt::renderer::IPass::create(
			    lt::renderer::Api::none,
			    system.get_device(),
			    system.get_swapchain(),
			    lt::assets::ShaderAsset { "./data/test_assets/triangle.vert.asset" },
			    lt::assets::ShaderAsset { "./data/test_assets/triangle.frag.asset" }
			);
		});

		expect_throw([&] {
			std::ignore = lt::renderer::IPass::create(
			    lt::renderer::Api::direct_x,
			    system.get_device(),
			    system.get_swapchain(),
			    lt::assets::ShaderAsset { "./data/test_assets/triangle.vert.asset" },
			    lt::assets::ShaderAsset { "./data/test_assets/triangle.frag.asset" }
			);
		});

		expect_throw([&] {
			std::ignore = lt::renderer::IPass::create(
			    lt::renderer::Api::metal,
			    system.get_device(),
			    system.get_swapchain(),
			    lt::assets::ShaderAsset { "./data/test_assets/triangle.vert.asset" },
			    lt::assets::ShaderAsset { "./data/test_assets/triangle.frag.asset" }
			);
		});
	};
};
