export module ecs.entity;
import debug.assertions;
import memory.reference;
import ecs.registry;
import std;

namespace lt::ecs {

/** High-level entity convenience wrapper */
export class Entity
{
public:
	Entity(memory::Ref<Registry> registry, EntityId identifier)
	    : m_registry(std::move(registry))
	    , m_identifier(identifier)
	{
		debug::ensure(m_registry, "Failed to create Entity ({}): null registry", m_identifier);
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

	auto get_registry() -> memory::Ref<Registry>
	{
		return m_registry;
	}

	[[nodiscard]] auto id() const -> EntityId
	{
		return m_identifier;
	}

private:
	memory::Ref<Registry> m_registry;

	EntityId m_identifier;
};


} // namespace lt::ecs
