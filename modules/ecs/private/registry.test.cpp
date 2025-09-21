#include <ecs/registry.hpp>
#include <ranges>
#include <test/expects.hpp>
#include <test/test.hpp>

using lt::test::Case;
using lt::test::expect_unreachable;
using lt::test::Suite;

using lt::test::expect_eq;

using lt::test::expect_false;
using lt::test::expect_true;

using lt::ecs::Entity;
using lt::ecs::Registry;

struct Component
{
	int m_int {};
	std::string m_string;

	[[nodiscard]] friend auto operator==(const Component &lhs, const Component &rhs) -> bool
	{
		return lhs.m_int == rhs.m_int && lhs.m_string == rhs.m_string;
	}
};
template<>
struct std::formatter<Component>
{
	constexpr auto parse(std::format_parse_context &context)
	{
		return context.begin();
	}

	auto format(const Component &val, std::format_context &context) const
	{
		return std::format_to(context.out(), "{}, {}", val.m_int, val.m_string);
	}
};

struct Component_B
{
	float m_float {};

	[[nodiscard]] friend auto operator==(const Component_B lhs, const Component_B &rhs) -> bool
	{
		return lhs.m_float == rhs.m_float;
	}
};
template<>
struct std::formatter<Component_B>
{
	constexpr auto parse(std::format_parse_context &context)
	{
		return context.begin();
	}

	auto format(const Component_B &val, std::format_context &context) const
	{
		return std::format_to(context.out(), "{}", val.m_float);
	}
};

Suite raii = [] {
	Case { "happy path won't throw" } = [] {
		std::ignore = Registry {};
	};

	Case { "many won't throw" } = [] {
		for (auto idx : std::views::iota(0, 100'000))
		{
			std::ignore = Registry {};
		}
	};

	Case { "unhappy path throws" } = [] {
	};

	Case { "post construct has correct state" } = [] {
		auto registry = Registry {};
		expect_eq(registry.get_entity_count(), 0);
	};
};

Suite entity_raii = [] {
	Case { "create_entity returns unique values" } = [] {
		auto registry = Registry {};
		auto set = std::unordered_set<Entity> {};

		for (auto idx : std::views::iota(0, 10'000))
		{
			auto entity = registry.create_entity();
			expect_false(set.contains(entity));

			set.insert(entity);
			expect_eq(set.size(), idx + 1);
		}
	};

	Case { "post create/destroy_entity has correct state" } = [] {
		auto registry = Registry {};

		auto entities = std::vector<Entity> {};
		for (auto idx : std::views::iota(0, 10'000))
		{
			entities.emplace_back(registry.create_entity());
			expect_eq(registry.get_entity_count(), idx + 1);
		}

		for (auto idx : std::views::iota(0, 10'000))
		{
			auto entity = entities.back();
			registry.destroy_entity(entity);

			entities.pop_back();
			expect_eq(registry.get_entity_count(), 10'000 - (idx + 1));
		}
	};
};

Suite component_raii = [] {
	Case { "add has correct state" } = [] {
		auto registry = Registry {};
		for (auto idx : std::views::iota(0, 100'000))
		{
			auto entity = registry.create_entity();
			auto &component = registry.add<Component>(
			    entity,
			    { .m_int = idx, .m_string = std::to_string(idx) }
			);

			expect_eq(component.m_int, idx);
			expect_eq(component.m_string, std::to_string(idx));
		}
	};

	Case { "remove has correct state" } = [] {
		auto registry = Registry {};
		for (auto idx : std::views::iota(0, 100'000))
		{
			auto entity = registry.create_entity();
			auto &component = registry.add<Component>(
			    entity,
			    { .m_int = idx, .m_string = std::to_string(idx) }
			);

			expect_eq(component.m_int, idx);
			expect_eq(component.m_string, std::to_string(idx));
		}
	};
};

Suite callbacks = [] {
	Case { "connecting on_construct/on_destruct won't throw" } = [] {
		auto registry = Registry {};
		registry.connect_on_construct<Component>([&](Registry &, Entity) {});
		registry.connect_on_destruct<Component>([&](Registry &, Entity) {});
	};

	Case { "on_construct/on_destruct won't get called on unrelated component" } = [] {
		auto registry = Registry {};
		registry.connect_on_construct<Component>([&](Registry &, Entity) { expect_unreachable(); });
		registry.connect_on_destruct<Component>([&](Registry &, Entity) { expect_unreachable(); });

		for (auto idx : std::views::iota(0, 100'000))
		{
			registry.add<Component_B>(registry.create_entity(), {});
		}
	};

	Case { "on_construct/on_destruct gets called" } = [] {
		auto registry = Registry {};
		auto all_entities = std::vector<Entity> {};
		auto on_construct_called = std::vector<Entity> {};
		auto on_destruct_called = std::vector<Entity> {};

		registry.connect_on_construct<Component>([&](Registry &, Entity entity) {
			on_construct_called.emplace_back(entity);
		});
		registry.connect_on_destruct<Component>([&](Registry &, Entity entity) {
			on_destruct_called.emplace_back(entity);
		});

		expect_true(on_construct_called.empty());
		expect_true(on_destruct_called.empty());
		for (auto idx : std::views::iota(0, 100'000))
		{
			auto entity = all_entities.emplace_back(registry.create_entity());
			registry.add<Component>(entity, {});
		}
		expect_eq(on_construct_called, all_entities);
		expect_true(on_destruct_called.empty());

		for (auto &entity : all_entities)
		{
			registry.remove<Component>(entity);
		}
		expect_eq(on_construct_called, all_entities);
		expect_eq(on_destruct_called, all_entities);
	};
};

Suite each = [] {
	auto registry = Registry {};

	auto shared_entity_counter = 0u;

	auto component_map_a = std::unordered_map<Entity, Component> {};
	auto entities_a = std::vector<Entity> {};

	for (auto idx : std::views::iota(0, 10'000))
	{
		auto entity = entities_a.emplace_back(registry.create_entity());
		auto &component = registry.add<Component>(
		    entity,
		    { .m_int = idx, .m_string = std::to_string(idx) }
		);

		component_map_a[entity] = component;
	}

	auto component_map_b = std::unordered_map<lt::ecs::Entity, Component_B> {};
	for (auto idx : std::views::iota(0, 10'000))
	{
		auto entity = Entity {};
		if (idx % 3 == 0)
		{
			entity = entities_a[idx];
			++shared_entity_counter;
		}
		else
		{
			entity = registry.create_entity();
		}
		auto &component = registry.add<Component_B>(
		    entity,
		    { .m_float = static_cast<float>(idx) / 2.0f }
		);

		component_map_b[entity] = component;
	}

	Case { "each one element" } = [&] {
		auto counter = 0u;
		registry.each<Component>([&](Entity entity, Component &component) {
			++counter;
			expect_eq(component_map_a[entity], component);
		});

		expect_eq(component_map_a.size(), counter);

		counter = 0u;
		registry.each<Component_B>([&](Entity entity, Component_B &component) {
			++counter;
			expect_eq(component_map_b[entity], component);
		});
		expect_eq(component_map_b.size(), counter);
	};

	Case { "each two element" } = [&] {
		auto counter = 0u;
		registry.each<Component, Component_B>(
		    [&](Entity entity, Component &component_a, Component_B &component_b) {
			    expect_eq(component_map_a[entity], component_a);
			    expect_eq(component_map_b[entity], component_b);
			    ++counter;
		    }
		);

		expect_eq(counter, shared_entity_counter);
	};
};

Suite views = [] {
	auto registry = Registry {};

	auto shared_entity_counter = 0u;

	auto component_map_a = std::unordered_map<Entity, Component> {};
	auto entities_a = std::vector<Entity> {};

	for (auto idx : std::views::iota(0, 10'000))
	{
		auto entity = entities_a.emplace_back(registry.create_entity());
		auto &component = registry.add<Component>(
		    entity,
		    { .m_int = idx, .m_string = std::to_string(idx) }
		);

		component_map_a[entity] = component;
	}

	auto component_map_b = std::unordered_map<Entity, Component_B> {};
	for (auto idx : std::views::iota(0, 10'000))
	{
		auto entity = Entity {};
		if (idx % 3 == 0)
		{
			entity = entities_a[idx];
			++shared_entity_counter;
		}
		else
		{
			entity = registry.create_entity();
		}
		auto &component = registry.add<Component_B>(
		    entity,
		    { .m_float = static_cast<float>(idx) / 2.0f }
		);

		component_map_b[entity] = component;
	}


	Case { "view one component" } = [&] {
		for (const auto &[entity, component] : registry.view<Component>())
		{
			expect_eq(component_map_a[entity], component);
		}

		for (const auto &[entity, component] : registry.view<Component_B>())
		{
			expect_eq(component_map_b[entity], component);
		}
	};

	Case { "view two component" } = [&] {
		auto counter = 0u;
		for (const auto &[entity, component, component_b] : registry.view<Component, Component_B>())
		{
			expect_eq(component_map_a[entity], component);
			expect_eq(component_map_b[entity], component_b);
			++counter;
		}
		expect_eq(counter, shared_entity_counter);

		counter = 0u;
		for (const auto &[entity, component_b, component] : registry.view<Component_B, Component>())
		{
			expect_eq(component_map_b[entity], component_b);
			expect_eq(component_map_a[entity], component);
			++counter;
		}
		expect_eq(counter, shared_entity_counter);
	};
};
