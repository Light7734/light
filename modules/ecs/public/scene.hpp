#pragma once

#include <ecs/components/transform.hpp>
#include <ecs/uuid.hpp>
#include <entt/entt.hpp>
#include <functional>

namespace lt {

class Entity;
class Framebuffer;

class Scene
{
public:
	template<typename... T>
	auto group()
	{
		return m_registry.group(entt::get<T...>);
	}

	auto create_entity(
	    const std::string &name,
	    const TransformComponent &transform = TransformComponent()
	) -> Entity;

	auto get_entity_by_tag(const std::string &tag) -> Entity;

	auto get_entt_registry() -> entt::registry &
	{
		return m_registry;
	}

private:
	friend class Entity;

	friend class SceneSerializer;

	friend class SceneHierarchyPanel;

	entt::registry m_registry;

	auto create_entity_with_uuid(
	    const std::string &name,
	    UUID uuid,
	    const TransformComponent &transform = TransformComponent()
	) -> Entity;
};

namespace ecs {

using Registry = Scene;

using Entity = ::lt::Entity;

} // namespace ecs

} // namespace lt
