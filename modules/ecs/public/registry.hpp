#pragma once

#include <ecs/sparse_set.hpp>

namespace lt::ecs {

using Entity = uint32_t;

/** A registry of components, the heart of an ECS architecture.
 *
 * @todo(Light): Implement grouping
 * @todo(Light): Implement identifier recycling
 * @todo(Light): Optimize views/each
 * @todo(Light): Support >2 component views
 * @todo(Light): Handle more edge cases or specify the undefined behaviors
 *
 * @ref https://skypjack.github.io/
 * @ref https://github.com/alecthomas/entityx
 * @ref https://github.com/skypjack/entt
 * @ref https://github.com/SanderMertens/flecs
 */
class Registry
{
public:
	using UnderlyingSparseSet_T = TypeErasedSparseSet<Entity>;

	using Callback_T = std::function<void(Registry &, Entity)>;

	template<typename Component_T>
	void connect_on_construct(Callback_T callback)
	{
		m_on_construct_hooks[get_type_id<Component_T>()] = callback;
	}

	template<typename Component_T>
	void connect_on_destruct(Callback_T callback)
	{
		m_on_destruct_hooks[get_type_id<Component_T>()] = callback;
	}

	template<typename Component_T>
	void disconnect_on_construct()
	{
		m_on_construct_hooks.erase(get_type_id<Component_T>());
	}

	template<typename Component_T>
	void disconnect_on_destruct()
	{
		m_on_destruct_hooks.erase(get_type_id<Component_T>());
	}

	auto create_entity() -> Entity
	{
		++m_entity_count;
		return m_current++;
	}

	void destroy_entity(Entity entity)
	{
		for (const auto &[key, set] : m_sparsed_sets)
		{
			set->remove(entity);
		}

		--m_entity_count;
	}

	template<typename Component_T>
	auto get(Entity entity) -> Component_T &
	{
		auto &derived_set = get_derived_set<Component_T>();
		return derived_set.at(entity).second;
	}

	template<typename Component_T>
	auto add(Entity entity, Component_T component) -> Component_T &
	{
		auto &derived_set = get_derived_set<Component_T>();
		auto &added_component = derived_set.insert(entity, std::move(component)).second;

		if (m_on_construct_hooks.contains(get_type_id<Component_T>()))
		{
			m_on_construct_hooks[get_type_id<Component_T>()](*this, entity);
		}

		return added_component;
	};

	template<typename Component_T>
	void remove(Entity entity)
	{
		if (m_on_destruct_hooks.contains(get_type_id<Component_T>()))
		{
			m_on_destruct_hooks[get_type_id<Component_T>()](*this, entity);
		}

		auto &derived_set = get_derived_set<Component_T>();
		derived_set.remove(entity);
	}

	template<typename Component_T>
	auto view() -> SparseSet<Component_T, Entity> &
	{
		return get_derived_set<Component_T>();
	};

	template<typename ComponentA_T, typename ComponentB_T>
	    requires(!std::is_same_v<ComponentA_T, ComponentB_T>)
	auto view() -> std::vector<std::tuple<Entity, ComponentA_T &, ComponentB_T &>>
	{
		auto &set_a = get_derived_set<ComponentA_T>();
		auto &set_b = get_derived_set<ComponentB_T>();
		auto view = std::vector<std::tuple<Entity, ComponentA_T &, ComponentB_T &>> {};

		/* iterate over the "smaller" component-set, and check if its entities have the other
		 * component */
		if (set_a.get_size() > set_b.get_size())
		{
			for (auto &[entity, component_b] : set_b)
			{
				if (set_a.contains(entity))
				{
					view.emplace_back(std::tie(entity, set_a.at(entity).second, component_b));
				}
			}
		}
		else
		{
			for (auto &[entity, component_a] : set_a)
			{
				if (set_b.contains(entity))
				{
					view.emplace_back(std::tie(entity, component_a, set_b.at(entity).second));
				}
			}
		}

		return view;
	};

	template<typename Component_T>
	void each(std::function<void(Entity, Component_T &)> functor)
	{
		for (auto &[entity, component] : get_derived_set<Component_T>())
		{
			functor(entity, component);
		}
	};

	template<typename ComponentA_T, typename ComponentB_T>
	    requires(!std::is_same_v<ComponentA_T, ComponentB_T>)
	void each(std::function<void(Entity, ComponentA_T &, ComponentB_T &)> functor)
	{
		auto &set_a = get_derived_set<ComponentA_T>();
		auto &set_b = get_derived_set<ComponentB_T>();

		/* iterate over the "smaller" component-set, and check if its entities have the other
		 * component */
		if (set_a.get_size() > set_b.get_size())
		{
			for (auto &[entity, component_b] : set_b)
			{
				if (set_a.contains(entity))
				{
					functor(entity, set_a.at(entity).second, component_b);
				}
			}

			return;
		}

		for (auto &[entity, component_a] : set_a)
		{
			if (set_b.contains(entity))
			{
				functor(entity, component_a, set_b.at(entity).second);
			}
		}
	};

	[[nodiscard]] auto get_entity_count() const -> size_t
	{
		return static_cast<size_t>(m_entity_count);
	}

private:
	using TypeId = size_t;

	static consteval auto hash_cstr(const char *str) -> TypeId
	{
		constexpr auto fnv_offset_basis = size_t { 14695981039346656037ull };
		constexpr auto fnv_prime = size_t { 1099511628211ull };

		auto hash = fnv_offset_basis;

		for (const auto &ch : std::string_view { str })
		{
			hash *= fnv_prime;
			hash ^= static_cast<uint8_t>(ch);
		}

		return hash;
	}

	template<typename T>
	static consteval auto get_type_id() -> TypeId
	{
#if defined _MSC_VER
	#define GENERATOR_PRETTY_FUNCTION __FUNCSIG__
#elif defined __clang__ || (defined __GNUC__)
	#define GENERATOR_PRETTY_FUNCTION __PRETTY_FUNCTION__
#else
	#error "Compiler not supported"
#endif
		constexpr auto value = hash_cstr(GENERATOR_PRETTY_FUNCTION);

#undef GENERATOR_PRETTY_FUNCTION

		return value;
	}

	template<typename T>
	auto get_derived_set() -> SparseSet<T, Entity> &
	{
		constexpr auto type_id = get_type_id<T>();
		if (!m_sparsed_sets.contains(type_id))
		{
			m_sparsed_sets[type_id] = create_scope<SparseSet<T, Entity>>();
		}

		auto *base_set = m_sparsed_sets[type_id].get();
		auto *derived_set = dynamic_cast<SparseSet<T, Entity> *>(base_set);
		ensure(derived_set, "Failed to downcast to derived set");

		return *derived_set;
	}

	Entity m_current;

	TypeId m_entity_count;

	std::flat_map<TypeId, Scope<UnderlyingSparseSet_T>> m_sparsed_sets;

	std::flat_map<TypeId, Callback_T> m_on_construct_hooks;

	std::flat_map<TypeId, Callback_T> m_on_destruct_hooks;
};

} // namespace lt::ecs
