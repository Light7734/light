import test;
import input.system;
import input.codes;
import surface.events;
import app.system;
import ecs.entity;
import ecs.registry;
import surface.system;

using ::lt::input::InputComponent;
using ::lt::input::System;

[[nodiscard]] auto tick_info() -> lt::app::TickInfo
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
	[[nodiscard]] auto registry() -> ref<lt::ecs::Registry>
	{
		return m_registry;
	}

	auto add_input_component() -> lt::ecs::EntityId
	{
		auto entity = m_registry->create_entity();
		m_registry->add<InputComponent>(entity, {});

		return entity;
	}

	auto add_surface_component() -> lt::ecs::EntityId
	{
		auto entity = m_registry->create_entity();
		m_surface_system.create_surface_component(
		    entity,
		    { .title = "", .resolution = { 20u, 20u } }
		);

		return entity;
	}

private:
	ref<lt::ecs::Registry> m_registry = create_ref<lt::ecs::Registry>();

	lt::surface::System m_surface_system = lt::surface::System { not_null { m_registry } };
};

Suite raii = "raii"_suite = "raii"_suite = [] {
	Case { "happy paths" } = [&] {
		System { not_null { Fixture {}.registry() } };
	};

	Case { "many" } = [&] {
		auto fixture = Fixture {};
		for (auto idx : std::views::iota(0, 10'000))
		{
			ignore = idx;
			ignore = System { not_null { fixture.registry() } };
		}
	};
};

Suite system_events = "system_events"_suite = [] {
	Case { "on_register won't throw" } = [] {
		auto fixture = Fixture {};
		auto registry = fixture.registry();
		auto system = System { not_null { registry } };

		system.on_register();
		expect_eq(registry->view<InputComponent>().get_size(), 0);
	};

	Case { "on_unregister won't throw" } = [] {
		auto fixture = Fixture {};
		auto registry = fixture.registry();
		auto system = System { not_null { registry } };

		system.on_register();
		system.on_unregister();
		expect_eq(registry->view<InputComponent>().get_size(), 0);
	};
};

Suite registry_events = "registry_events"_suite = [] {
	Case { "on_construct<InputComnent>" } = [] {
		auto fixture = Fixture {};
		auto registry = fixture.registry();
		auto system = System { not_null { registry } };

		fixture.add_input_component();
		expect_eq(registry->view<InputComponent>().get_size(), 1);
	};

	Case { "on_destrroy<InputComponent>" } = [] {
		auto fixture = Fixture {};
		auto registry = fixture.registry();
		auto system = create_scope<System>(not_null { registry });

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
		auto system = System { not_null { fixture.registry() } };

		system.tick(tick_info());
	};

	Case { "Tick triggers input action" } = [] {
		auto fixture = Fixture {};
		auto registry = fixture.registry();
		auto system = System { not_null { fixture.registry() } };

		auto surface_entity = fixture.add_surface_component();
		auto &surface = registry->get<lt::surface::SurfaceComponent>(surface_entity);

		auto input_entity = fixture.add_input_component();
		auto &input = registry->get<InputComponent>(input_entity);

		auto action_key = input.add_action(
		    {
		        .name { "test" },
		        .trigger = { .mapped_keycode = lt::Key::a },
		    }
		);

		using enum ::lt::input::InputAction::State;
		expect_eq(input.get_action(action_key).state, inactive);
		system.tick(tick_info());
		expect_eq(input.get_action(action_key).state, inactive);

		surface.push_event(lt::surface::KeyPressedEvent(lt::Key::a));
		system.tick(tick_info());
		expect_eq(input.get_action(action_key).state, triggered);

		system.tick(tick_info());
		expect_eq(input.get_action(action_key).state, active);

		system.tick(tick_info());
		system.tick(tick_info());
		system.tick(tick_info());
		expect_eq(input.get_action(action_key).state, active);

		surface.push_event(lt::surface::KeyReleasedEvent(lt::Key::a));
		system.tick(tick_info());
		expect_eq(input.get_action(action_key).state, inactive);
	};
};
