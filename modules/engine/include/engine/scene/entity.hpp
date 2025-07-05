#pragma once

#include <engine/base/base.hpp>
#include <engine/scene/components/uuid.hpp>
#include <engine/scene/scene.hpp>
#include <entt/entt.hpp>

namespace Light {

class Entity
{
private:
	entt::entity m_Handle;
	Scene *m_Scene;

public:
	Entity(entt::entity handle = entt::null, Scene *registry = nullptr);
	~Entity();

	template<typename T, typename... Args>
	inline T &AddComponent(Args &&...args)
	{
		return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
	}

	template<typename T>
	inline T &GetComponent()
	{
		return m_Scene->m_Registry.get<T>(m_Handle);
	}

	template<typename T>
	inline bool HasComponent()
	{
		return m_Scene->m_Registry.any_of<T>(m_Handle);
	}

	template<typename T>
	inline void RemoveComponent()
	{
		m_Scene->m_Registry.remove<T>(m_Handle);
	}

	inline uint64_t GetUUID()
	{
		return GetComponent<UUIDComponent>().uuid;
	}

	inline bool IsValid() const
	{
		return m_Handle != entt::null && m_Scene != nullptr;
	}

	operator uint32_t()
	{
		return (uint32_t)m_Handle;
	}
};

} // namespace Light
