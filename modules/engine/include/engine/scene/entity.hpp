#pragma once

#include <engine/base/base.hpp>
#include <engine/scene/components/uuid.hpp>
#include <engine/scene/scene.hpp>
#include <entt/entt.hpp>

namespace Light {

class Entity
{
public:
	Entity(entt::entity handle = entt::null, Scene *registry = nullptr);

	~Entity();

	template<typename t, typename... Args>
	inline t &AddComponent(Args &&...args)
	{
		return m_scene->m_registry.emplace<t>(m_handle, std::forward<Args>(args)...);
	}

	template<typename t>
	inline t &GetComponent()
	{
		return m_scene->m_registry.get<t>(m_handle);
	}

	template<typename t>
	inline bool has_component()
	{
		return m_scene->m_registry.any_of<t>(m_handle);
	}

	template<typename t>
	inline void remove_component()
	{
		m_scene->m_registry.remove<t>(m_handle);
	}

	inline uint64_t get_uuid()
	{
		return GetComponent<UUIDComponent>().uuid;
	}

	inline bool is_valid() const
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

} // namespace Light
