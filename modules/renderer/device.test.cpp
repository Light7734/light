import renderer.test_utils;

Suite raii = "device_raii"_suite = [] {
	Case { "happy paths" } = [] {
		auto fixture = Fixture_SurfaceGpu {};
		ignore = lt::renderer::vkb::Device(fixture.gpu(), fixture.surface());
	};

	Case { "unhappy paths" } = [] {
		auto fixture = Fixture_SurfaceGpu {};

		expect_throw([&] { ignore = lt::renderer::vkb::Device(nullptr, fixture.surface()); });
		expect_throw([&] { ignore = lt::renderer::vkb::Device(fixture.gpu(), nullptr); });
	};
};
