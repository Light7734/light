import renderer.frontend;
import renderer.test_utils;

Suite raii = "device_raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		auto fixture = Fixture_SurfaceGpu {};
		std::ignore = lt::renderer::create_device(constants::api, fixture.gpu(), fixture.surface());
	};

	Case { "unhappy path throws" } = [] {
		auto fixture = Fixture_SurfaceGpu {};

		expect_throw([&] {
			ignore = lt::renderer::create_device(constants::api, nullptr, fixture.surface());
		});

		expect_throw([&] {
			ignore = lt::renderer::create_device(constants::api, fixture.gpu(), nullptr);
		});

		expect_throw([&] {
			ignore = lt::renderer::create_device(
			    lt::renderer::Api::none,
			    fixture.gpu(),
			    fixture.surface()
			);
		});

		expect_throw([&] {
			ignore = lt::renderer::create_device(
			    lt::renderer::Api::direct_x,
			    fixture.gpu(),
			    fixture.surface()
			);
		});

		expect_throw([&] {
			ignore = lt::renderer::create_device(
			    lt::renderer::Api::metal,
			    fixture.gpu(),
			    fixture.surface()
			);
		});
	};
};
