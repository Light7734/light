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
private:
	friend class Entity;
	friend class SceneSerializer;
	friend class SceneHierarchyPanel;

private:
	entt::registry m_Registry;

public:
	Scene();
	~Scene();

	void OnCreate();

	void OnUpdate(float deltaTime);
	void OnRender(const Ref<Framebuffer> &targetFrameBuffer = nullptr);

	Entity CreateEntity(
	    const std::string &name,
	    const TransformComponent &transform = TransformComponent()
	);

	Entity GetEntityByTag(const std::string &tag);

private:
	Entity CreateEntityWithUUID(
	    const std::string &name,
	    UUID uuid,
	    const TransformComponent &transform = TransformComponent()
	);
};

} // namespace Light
