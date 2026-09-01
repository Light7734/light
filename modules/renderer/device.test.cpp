import renderer.test_utils;

Suite raii = "device_raii"_suite = [] {
	Case { "happy paths" } = [] {
		auto fixture = Fixture_SurfaceGpu {};
		ignore = lt::renderer::vkb::Device(
		    not_null { fixture.gpu() },
		    not_null { fixture.surface() }
		);
	};
};
