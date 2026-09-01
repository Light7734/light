import renderer.test_utils;

Suite raii = "surface"_suite = [] {
	Case { "happy paths" } = [&] {
		auto fixture = Fixture_SurfaceSystem {};

		const auto surface = lt::renderer::vkb::Surface(
		    not_null<lt::renderer::vkb::Instance *>(lt::renderer::vkb::Instance::get()),
		    fixture.surface_entity()
		);

		const auto &[x, y] = surface.get_framebuffer_size();
		expect_eq(x, constants::resolution.x);
		expect_eq(y, constants::resolution.y);
	};

	Case { "unhappy paths" } = [&] {
		auto registry = create_ref<lt::ecs::Registry>();
		auto entity = lt::ecs::Entity {
			not_null<ref<lt::ecs::Registry>>(registry),
			registry->create_entity(),
		};
		auto system = lt::surface::System(not_null { registry });

		expect_throw([&] {
			ignore = lt::renderer::vkb::Surface(
			    not_null<lt::renderer::vkb::Instance *>(lt::renderer::vkb::Instance::get()),
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

		// Ensure base creation info is non-throwing
		ignore = lt::renderer::vkb::Surface(
		    not_null<lt::renderer::vkb::Instance *>(lt::renderer::vkb::Instance::get()),
		    entity
		);
	};
};
