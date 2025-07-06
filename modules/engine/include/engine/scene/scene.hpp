#pragma once

#include <engine/base/base.hpp>
#include <engine/core/uuid.hpp>
#include <engine/scene/components/transform.hpp>
#include <entt/entt.hpp>
#include <glm/glm.hpp>

namespace Light {

class Entity;
class Framebuffer;

class Scene
{
public:
	Scene();

	~Scene();

	void on_create();

	void on_update(float deltaTime);

	void on_render(const Ref<Framebuffer> &targetFrameBuffer = nullptr);

	auto create_entity(
	    const std::string &name,
	    const TransformComponent &transform = TransformComponent()
	) -> Entity;

	auto get_entity_by_tag(const std::string &tag) -> Entity;

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

} // namespace Light
