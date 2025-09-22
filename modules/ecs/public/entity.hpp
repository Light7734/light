#pragma once

#include <ecs/registry.hpp>

namespace lt::ecs {

/** High-level entity convenience wrapper */
class Entity
{
public:
	Entity(Ref<Registry> registry, EntityId identifier)
	    : m_registry(std::move(registry))
	    , m_identifier(identifier)
	{
		ensure(m_registry, "Failed to create Entity ({}): null registry", m_identifier);
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

	auto get_registry() -> Ref<Registry>
	{
		return m_registry;
	}

private:
	Ref<Registry> m_registry;

	EntityId m_identifier;
};


} // namespace lt::ecs
