#include <ecs/entity.hpp>
#include <ecs/registry.hpp>
#include <memory/reference.hpp>
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
		auto entity = registry.create_entity();
		registry.add<surface::SurfaceComponent>(
		    entity,
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
	const auto view = registry.view<SurfaceComponent>();

	if (!view.is_empty())
	{
		registry.remove<SurfaceComponent>(view[0].first);
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

	auto registry = memory::create_ref<ecs::Registry>();
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
			registry->create_entity();

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
			auto view = registry->view<SurfaceComponent>();

			if (!view.is_empty())
			{
				for (auto &[entity, component] : view)
				{
					provider.consume<uint8_t>().value_or(0);
					// @TODO(Light): push some event
				}
			}

			break;
		}
		case FuzzAction::push_request:
		{
			break;
		}
		case FuzzAction::count:
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
