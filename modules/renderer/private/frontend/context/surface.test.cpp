#include <memory/reference.hpp>
#include <renderer/frontend/context/instance.hpp>
#include <renderer/frontend/context/surface.hpp>
#include <renderer/test/utils.hpp>
#include <surface/components.hpp>
#include <surface/system.hpp>
#include <test/test.hpp>

using ::lt::ecs::EntityId;
using ::lt::ecs::Registry;

Suite raii = "surface"_suite = [] {
	Case { "happy path won't throw" } = [&] {
		auto fixture = Fixture_SurfaceSystem {};

		const auto surface = lt::renderer::ISurface::create(
		    constants::api,
		    lt::renderer::IInstance::get(constants::api),
		    fixture.surface_entity()
		);

		const auto &[x, y] = surface->get_framebuffer_size();
		expect_eq(x, constants::resolution.x);
		expect_eq(y, constants::resolution.y);
	};

	Case { "unhappy path throws" } = [&] {
		auto registry = lt::memory::create_ref<lt::ecs::Registry>();
		auto entity = lt::ecs::Entity { registry, registry->create_entity() };
		auto system = lt::surface::System(registry);

		expect_throw([&] {
			std::ignore = lt::renderer::ISurface::create(
			    constants::api,
			    lt::renderer::IInstance::get(constants::api),
			    entity
			);
		});

		system.create_surface_component(
		    entity.id(),
		    lt::surface::SurfaceComponent::CreateInfo {
		        .title = "",
		        .resolution = constants::resolution,
		    }
		);

		expect_throw([&] {
			std::ignore = lt::renderer::ISurface::create(constants::api, nullptr, entity);
		});

		expect_throw([&] {
			std::ignore = lt::renderer::ISurface::create(
			    lt::renderer::Api::none,
			    lt::renderer::IInstance::get(constants::api),
			    entity
			);
		});

		expect_throw([&] {
			std::ignore = lt::renderer::ISurface::create(
			    lt::renderer::Api::direct_x,
			    lt::renderer::IInstance::get(constants::api),
			    entity
			);
		});

		expect_throw([&] {
			std::ignore = lt::renderer::ISurface::create(
			    lt::renderer::Api::metal,
			    lt::renderer::IInstance::get(constants::api),
			    entity
			);
		});

		// Ensure base creation info is non-throwing
		std::ignore = lt::renderer::ISurface::create(
		    constants::api,
		    lt::renderer::IInstance::get(constants::api),
		    entity
		);
	};

	// TODO(Light): add torture tests
	Case { "torture tests" } = [] {
	};
};
