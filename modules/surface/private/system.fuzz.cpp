#include <ecs/scene.hpp>
#include <surface/system.hpp>
#include <test/fuzz.hpp>
#include <test/test.hpp>

namespace lt::surface {

enum class Action : uint8_t
{
	create_entity,

	create_surface_component,

	destroy_surface_component,

	tick,
};

void create_surface_component(test::FuzzDataProvider &provider, ecs::Registry &registry)
{
	const auto length = std::min(provider.consume<uint32_t>().value_or(16), 255u);
	const auto title = provider.consume_string(length).value_or("");

	const auto resolution = math::uvec2 {
		provider.consume<uint32_t>().value_or({ 32 }),
		provider.consume<uint32_t>().value_or({ 64 }),
	};
	const auto visible = provider.consume<bool>().value_or(false);
	const auto vsync = provider.consume<bool>().value_or(false);

	try
	{
		registry.create_entity("").add_component<surface::SurfaceComponent>(
		    surface::SurfaceComponent::CreateInfo {
		        .title = std::move(title),
		        .resolution = resolution,
		        .vsync = vsync,
		        .visible = visible,
		    }
		);
	}
	catch (const std::exception &exp)
	{
		std::ignore = exp;
	}
}

void remove_surface_component(ecs::Registry &registry)
{
	const auto view = registry.get_entt_registry().view<SurfaceComponent>();

	if (!view->empty())
	{
		registry.get_entt_registry().remove<SurfaceComponent>(*view.begin());
	}
}

void check_invariants()
{
}

test::FuzzHarness harness = [](const uint8_t *data, size_t size) {
	auto provider = test::FuzzDataProvider { data, size };

	auto registry = create_ref<ecs::Registry>();
	auto system = surface::System { registry };

	while (auto action = provider.consume<uint8_t>())
	{
		switch (static_cast<Action>(action.value()))
		{
		case Action::create_entity:
		{
			const auto length = std::min(provider.consume<uint32_t>().value_or(16), 255u);
			const auto tag = provider.consume_string(length).value_or("");
			registry->create_entity(tag);

			break;
		}
		case Action::create_surface_component:
		{
			create_surface_component(provider, *registry);
			break;
		}
		case Action::destroy_surface_component:
		{
			remove_surface_component(*registry);
			break;
		}
		case Action::tick:
		{
			system.tick();
			break;
		}
		}

		check_invariants();
	}

	return 0;
};

} // namespace lt::surface
