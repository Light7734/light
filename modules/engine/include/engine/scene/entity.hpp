#pragma once

#include <engine/base/base.hpp>
#include <engine/scene/components/uuid.hpp>
#include <engine/scene/scene.hpp>
#include <entt/entt.hpp>

namespace Light {

class Entity
{
private:
	entt::entity m_handle;
	Scene *m_scene;

public:
	Entity(entt::entity handle = entt::null, Scene *registry = nullptr);
	~Entity();

	template<typename T, typename... Args>
	inline T &AddComponent(Args &&...args)
	{
		return m_scene->m_registry.emplace<T>(m_handle, std::forward<Args>(args)...);
	}

	template<typename T>
	inline T &GetComponent()
	{
		return m_scene->m_registry.get<T>(m_handle);
	}

	template<typename T>
	inline bool HasComponent()
	{
		return m_scene->m_registry.any_of<T>(m_handle);
	}

	template<typename T>
	inline void RemoveComponent()
	{
		m_scene->m_registry.remove<T>(m_handle);
	}

	inline uint64_t GetUUID()
	{
		return GetComponent<UUIDComponent>().uuid;
	}

	inline bool IsValid() const
	{
		return m_handle != entt::null && m_scene != nullptr;
	}

	operator uint32_t()
	{
		return (uint32_t)m_handle;
	}
};

} // namespace Light
