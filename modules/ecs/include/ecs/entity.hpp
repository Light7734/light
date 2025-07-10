#pragma once

#include <ecs/components/uuid.hpp>
#include <ecs/scene.hpp>
#include <entt/entt.hpp>

namespace lt {

class Entity
{
public:
	Entity(entt::entity handle = entt::null, Scene *scene = nullptr);

	template<typename t, typename... Args>
	auto add_component(Args &&...args) -> t &
	{
		return m_scene->m_registry.emplace<t>(m_handle, std::forward<Args>(args)...);
	}

	template<typename t>
	auto get_component() -> t &
	{
		return m_scene->m_registry.get<t>(m_handle);
	}

	template<typename t>
	auto has_component() -> bool
	{
		return m_scene->m_registry.any_of<t>(m_handle);
	}

	template<typename t>
	void remove_component()
	{
		m_scene->m_registry.remove<t>(m_handle);
	}

	auto get_uuid() -> uint64_t
	{
		return get_component<UUIDComponent>().uuid;
	}

	[[nodiscard]] auto is_valid() const -> bool
	{
		return m_handle != entt::null && m_scene != nullptr;
	}

	operator uint32_t()
	{
		return (uint32_t)m_handle;
	}

private:
	entt::entity m_handle;

	Scene *m_scene;
};

} // namespace lt
