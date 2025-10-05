#pragma once

#include <ecs/registry.hpp>
#include <memory/reference.hpp>

namespace lt::ecs {

/** High-level entity convenience wrapper */
class Entity
{
public:
	Entity(memory::Ref<Registry> registry, EntityId identifier)
	    : m_registry(std::move(registry))
	    , m_identifier(identifier)
	{
		ensure(m_registry, "Failed to create Entity ({}): null registry", m_identifier);
	}

	template<typename Component_T>
	auto add(Component_T component) -> Component_T &
	{
		m_registry->add(m_identifier, component);
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

private:
	memory::Ref<Registry> m_registry;


	EntityId m_identifier;
};


} // namespace lt::ecs
