#include <ecs/entity.hpp>
#include <input/components.hpp>
#include <input/system.hpp>
#include <memory/reference.hpp>
#include <memory/scope.hpp>
#include <ranges>
#include <test/test.hpp>

// NOLINTBEGIN
using namespace lt;
using input::InputComponent;
using input::System;
using std::ignore;
using test::Case;
using test::expect_eq;
using test::expect_false;
using test::expect_ne;
using test::expect_not_nullptr;
using test::expect_throw;
using test::Suite;
// NOLINTEND

[[nodiscard]] auto tick_info() -> app::TickInfo
{
	return {
		.delta_time = std::chrono::milliseconds { 16 },
		.budget = std::chrono::milliseconds { 10 },
		.start_time = std::chrono::steady_clock::now(),
	};
}

class Fixture
{
public:
	[[nodiscard]] auto registry() -> memory::Ref<ecs::Registry>
	{
		return m_registry;
	}

	auto add_input_component() -> ecs::EntityId
	{
		auto entity = m_registry->create_entity();
		m_registry->add<InputComponent>(entity, {});

		return entity;
	}

	auto add_surface_component() -> ecs::EntityId
	{
		auto entity = m_registry->create_entity();
		m_registry->add<surface::SurfaceComponent>(
		    entity,
		    surface::SurfaceComponent::CreateInfo {}
		);

		return entity;
	}

private:
	memory::Ref<ecs::Registry> m_registry = memory::create_ref<ecs::Registry>();
};

Suite raii = "raii"_suite = "raii"_suite = [] {
	Case { "happy path won't throw" } = [&] {
		System { Fixture {}.registry() };
	};

	Case { "many won't freeze/throw" } = [&] {
		auto fixture = Fixture {};
		for (auto idx : std::views::iota(0, 10'000))
		{
			ignore = System { fixture.registry() };
		}
	};

	Case { "unhappy path throws" } = [] {
		expect_throw([] { ignore = System { {} }; });
	};
};

Suite system_events = "system_events"_suite = [] {
	Case { "on_register won't throw" } = [] {
		auto fixture = Fixture {};
		auto registry = fixture.registry();
		auto system = System { registry };

		system.on_register();
		expect_eq(registry->view<InputComponent>().get_size(), 0);
	};

	Case { "on_unregister won't throw" } = [] {
		auto fixture = Fixture {};
		auto registry = fixture.registry();
		auto system = System { registry };

		system.on_register();
		system.on_unregister();
		expect_eq(registry->view<InputComponent>().get_size(), 0);
	};
};

Suite registry_events = "registry_events"_suite = [] {
	Case { "on_construct<InputComnent>" } = [] {
		auto fixture = Fixture {};
		auto registry = fixture.registry();
		auto system = System { registry };

		const auto &entity = fixture.add_input_component();
		expect_eq(registry->view<InputComponent>().get_size(), 1);
	};

	Case { "on_destrroy<InputComponent>" } = [] {
		auto fixture = Fixture {};
		auto registry = fixture.registry();
		auto system = memory::create_scope<System>(registry);

		auto entity_a = fixture.add_input_component();
		auto entity_b = fixture.add_input_component();
		expect_eq(registry->view<InputComponent>().get_size(), 2);

		registry->remove<InputComponent>(entity_a);
		expect_eq(registry->view<InputComponent>().get_size(), 1);

		system.reset();
		expect_eq(registry->view<InputComponent>().get_size(), 1);

		registry->remove<InputComponent>(entity_b);
		expect_eq(registry->view<InputComponent>().get_size(), 0);
	};
};

Suite tick = "tick"_suite = [] {
	Case { "Empty tick won't throw" } = [] {
		auto fixture = Fixture {};
		auto registry = fixture.registry();
		auto system = System { fixture.registry() };

		system.tick(tick_info());
	};

	Case { "Tick triggers input action" } = [] {
		auto fixture = Fixture {};
		auto registry = fixture.registry();
		auto system = System { fixture.registry() };

		auto surface_entity = fixture.add_surface_component();
		auto &surface = registry->get<surface::SurfaceComponent>(surface_entity);

		auto input_entity = fixture.add_input_component();
		auto &input = registry->get<InputComponent>(input_entity);

		auto action_key = input.add_action(
		    {
		        .name { "test" },
		        .trigger = { .mapped_keycode = 69 },
		    }
		);

		expect_eq(input.get_action(action_key).state, input::InputAction::State::inactive);
		system.tick(tick_info());
		expect_eq(input.get_action(action_key).state, input::InputAction::State::inactive);

		surface.push_event(surface::KeyPressedEvent(69));
		system.tick(tick_info());
		expect_eq(input.get_action(action_key).state, input::InputAction::State::triggered);

		system.tick(tick_info());
		expect_eq(input.get_action(action_key).state, input::InputAction::State::active);

		system.tick(tick_info());
		system.tick(tick_info());
		system.tick(tick_info());
		expect_eq(input.get_action(action_key).state, input::InputAction::State::active);

		surface.push_event(surface::KeyReleasedEvent(69));
		system.tick(tick_info());
		expect_eq(input.get_action(action_key).state, input::InputAction::State::inactive);
	};

	Case { "Tick triggers" } = [] {
		auto fixture = Fixture {};
		auto registry = fixture.registry();
		auto system = System { fixture.registry() };

		auto surface_entity = fixture.add_surface_component();
		auto &surface = registry->get<surface::SurfaceComponent>(surface_entity);

		auto input_entity = fixture.add_input_component();
		auto &input = registry->get<InputComponent>(input_entity);


		auto action_key = input.add_action(
		    {
		        .name { "test" },
		        .trigger = { .mapped_keycode = 69 },
		    }
		);
	};
};
