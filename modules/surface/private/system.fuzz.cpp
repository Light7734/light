#include <ecs/entity.hpp>
#include <ecs/registry.hpp>
#include <surface/components.hpp>
#include <surface/system.hpp>
#include <test/fuzz.hpp>
#include <test/test.hpp>

namespace lt::surface {

enum class FuzzAction : uint8_t
{
	create_entity,

	create_surface_component,

	destroy_surface_component,

	push_request,

	push_event,

	tick_system,

	count,
};

enum class EventType : uint8_t
{
	Closed,
	Moved,
	Resized,
	LostFocus,
	GainFocus,
};

void create_surface_component(test::FuzzDataProvider &provider, ecs::Registry &registry)
{
	const auto length = std::min(provider.consume<uint32_t>().value_or(16), 255u);
	const auto title = provider.consume_string(length).value_or("");

	const auto resolution = math::uvec2 {
		provider.consume<uint32_t>().value_or(32u),
		provider.consume<uint32_t>().value_or(64u),
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

void push_request(ecs::Registry &registry)
{
}

void push_event(ecs::Registry &registry)
{
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
		if (*action > std::to_underlying(FuzzAction::count))
		{
			*action = *action % std::to_underlying(FuzzAction::count);
		}

		switch (static_cast<FuzzAction>(action.value()))
		{
		case FuzzAction::create_entity:
		{
			const auto length = std::min(provider.consume<uint32_t>().value_or(16), 255u);
			const auto tag = provider.consume_string(length).value_or("");
			registry->create_entity(tag);

			break;
		}
		case FuzzAction::create_surface_component:
		{
			create_surface_component(provider, *registry);
			break;
		}
		case FuzzAction::destroy_surface_component:
		{
			remove_surface_component(*registry);
			break;
		}
		case FuzzAction::push_event:
		{
			const auto view = registry->get_entt_registry().view<SurfaceComponent>();

			if (!view->empty())
			{
				view.each([&](auto entity, SurfaceComponent &surface) {
					provider.consume<uint8_t>().value_or(0);
				});

				registry->get_entt_registry().remove<SurfaceComponent>(*view.begin());
			}

			break;
		}
		case FuzzAction::push_request:
		{
			break;
		}
		case FuzzAction::tick_system:
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
