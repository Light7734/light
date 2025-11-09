#include <memory/reference.hpp>
#include <ranges>
#include <renderer/frontend/context/device.hpp>
#include <renderer/frontend/context/surface.hpp>
#include <renderer/test/utils.hpp>
#include <surface/components.hpp>
#include <surface/system.hpp>
#include <test/test.hpp>

Suite raii = "device_raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		auto fixture = Fixture_SurfaceGpu {};
		std::ignore = lt::renderer::IDevice::create(
		    constants::api,
		    fixture.gpu(),
		    fixture.surface()
		);
	};

	Case { "unhappy path throws" } = [] {
		auto fixture = Fixture_SurfaceGpu {};

		expect_throw([&] {
			ignore = lt::renderer::IDevice::create(constants::api, nullptr, fixture.surface());
		});

		expect_throw([&] {
			ignore = lt::renderer::IDevice::create(constants::api, fixture.gpu(), nullptr);
		});

		expect_throw([&] {
			ignore = lt::renderer::IDevice::create(
			    lt::renderer::Api::none,
			    fixture.gpu(),
			    fixture.surface()
			);
		});

		expect_throw([&] {
			ignore = lt::renderer::IDevice::create(
			    lt::renderer::Api::direct_x,
			    fixture.gpu(),
			    fixture.surface()
			);
		});

		expect_throw([&] {
			ignore = lt::renderer::IDevice::create(
			    lt::renderer::Api::metal,
			    fixture.gpu(),
			    fixture.surface()
			);
		});
	};
};
