import renderer.frontend;
import renderer.test_utils;

Suite raii = "surface"_suite = [] {
	Case { "happy path won't throw" } = [&] {
		auto fixture = Fixture_SurfaceSystem {};

		const auto surface = lt::renderer::create_surface(
		    constants::api,
		    lt::renderer::get_instance(constants::api),
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
			std::ignore = lt::renderer::create_surface(
			    constants::api,
			    lt::renderer::get_instance(constants::api),
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
			std::ignore = lt::renderer::create_surface(constants::api, nullptr, entity);
		});

		expect_throw([&] {
			std::ignore = lt::renderer::create_surface(
			    lt::renderer::Api::none,
			    lt::renderer::get_instance(constants::api),
			    entity
			);
		});

		expect_throw([&] {
			std::ignore = lt::renderer::create_surface(
			    lt::renderer::Api::direct_x,
			    lt::renderer::get_instance(constants::api),
			    entity
			);
		});

		expect_throw([&] {
			std::ignore = lt::renderer::create_surface(
			    lt::renderer::Api::metal,
			    lt::renderer::get_instance(constants::api),
			    entity
			);
		});

		// Ensure base creation info is non-throwing
		std::ignore = lt::renderer::create_surface(
		    constants::api,
		    lt::renderer::get_instance(constants::api),
		    entity
		);
	};
};
