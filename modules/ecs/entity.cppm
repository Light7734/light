export module ecs.entity;

import preliminary;
import ecs.registry;

export namespace lt::ecs {

/** High-level entity convenience wrapper */
class Entity
{
public:
	Entity(const not_null<ref<Registry>> &registry, EntityId identifier)
	    : m_registry(registry.get())
	    , m_identifier(identifier)
	{
	}

	template<typename Component_T>
	auto add(Component_T component) -> Component_T &
	{
		return m_registry->add(m_identifier, component);
	}

	template<typename Component_T>
	auto get() -> Component_T &
	{
		return m_registry->get<Component_T>(m_identifier);
	}

	template<typename Component_T>
	auto get() const -> const Component_T &
	{
		return m_registry->get<Component_T>(m_identifier);
	}

	auto get_registry() -> ref<Registry>
	{
		return m_registry;
	}

	[[nodiscard]] auto id() const -> EntityId
	{
		return m_identifier;
	}

private:
	ref<Registry> m_registry;

	EntityId m_identifier;
};

} // namespace lt::ecs
