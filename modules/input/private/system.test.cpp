#include <ecs/entity.hpp>
#include <input/components.hpp>
#include <input/system.hpp>
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

class Fixture
{
public:
	[[nodiscard]] auto registry() -> Ref<ecs::Registry>
	{
		return m_registry;
	}

	auto add_input_component() -> ecs::Entity
	{
		auto entity = m_registry->create_entity("");
		entity.add_component<InputComponent>();

		return entity;
	}

	auto add_surface_component() -> ecs::Entity
	{
		auto entity = m_registry->create_entity("");
		entity.add_component<surface::SurfaceComponent>(surface::SurfaceComponent::CreateInfo {});

		return entity;
	}

private:
	Ref<ecs::Registry> m_registry = create_ref<ecs::Registry>();
};

Suite raii = [] {
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

Suite system_events = [] {
	Case { "on_register won't throw" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };

		system.on_register();
		expect_eq(fixture.registry()->view<InputComponent>().size(), 0);
	};

	Case { "on_unregister won't throw" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };

		system.on_register();
		system.on_unregister();
		expect_eq(fixture.registry()->view<InputComponent>().size(), 0);
	};
};

Suite registry_events = [] {
	Case { "on_construct<InputComnent>" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };

		const auto &entity = fixture.add_input_component();
		expect_eq(fixture.registry()->view<InputComponent>().size(), 1);
	};

	Case { "on_destrroy<InputComponent>" } = [] {
		auto fixture = Fixture {};
		auto system = create_scope<System>(fixture.registry());

		auto entity_a = fixture.add_input_component();
		auto entity_b = fixture.add_input_component();
		expect_eq(fixture.registry()->view<InputComponent>().size(), 2);

		entity_a.remove_component<InputComponent>();
		expect_eq(fixture.registry()->view<InputComponent>().size(), 1);

		system.reset();
		expect_eq(fixture.registry()->view<InputComponent>().size(), 1);

		entity_b.remove_component<InputComponent>();
		expect_eq(fixture.registry()->view<InputComponent>().size(), 0);
	};
};

Suite tick = [] {
	Case { "Empty tick won't throw" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };

		expect_false(system.tick());
	};

	Case { "Tick triggers input action" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };

		auto &surface = fixture.add_surface_component().get_component<surface::SurfaceComponent>();
		auto &input = fixture.add_input_component().get_component<InputComponent>();

		auto action_key = input.add_action(
		    {
		        .name { "test" },
		        .trigger = { .mapped_keycode = 69 },
		    }
		);

		expect_eq(input.get_action(action_key).state, input::InputAction::State::inactive);
		system.tick();
		expect_eq(input.get_action(action_key).state, input::InputAction::State::inactive);

		surface.push_event(surface::KeyPressedEvent(69));
		system.tick();
		expect_eq(input.get_action(action_key).state, input::InputAction::State::triggered);

		system.tick();
		expect_eq(input.get_action(action_key).state, input::InputAction::State::active);

		system.tick();
		system.tick();
		system.tick();
		expect_eq(input.get_action(action_key).state, input::InputAction::State::active);

		surface.push_event(surface::KeyReleasedEvent(69));
		system.tick();
		expect_eq(input.get_action(action_key).state, input::InputAction::State::inactive);
	};

	Case { "Tick triggers" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };

		auto &surface = fixture.add_surface_component().get_component<surface::SurfaceComponent>();
		auto &input = fixture.add_input_component().get_component<InputComponent>();

		auto action_key = input.add_action(
		    {
		        .name { "test" },
		        .trigger = { .mapped_keycode = 69 },
		    }
		);
	};
};
