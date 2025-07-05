#include <engine/graphics/renderer.hpp>
#include <engine/scene/components.hpp>
#include <engine/scene/entity.hpp>
#include <engine/scene/scene.hpp>
#include <glm/glm.hpp>

namespace Light {

Scene::Scene(): m_registry()
{
}

Scene::~Scene()
{
}

void Scene::OnCreate()
{
	/* native scripts */
	{
		m_registry.view<NativeScriptComponent>().each([](NativeScriptComponent &nsc) {
			if (nsc.instance == nullptr)
			{
				nsc.instance = nsc.CreateInstance();
				nsc.instance->OnCreate();
			}
		});
	}
}

void Scene::OnUpdate(float deltaTime)
{
	/* native scripts */
	{
		m_registry.view<NativeScriptComponent>().each([=](NativeScriptComponent &nsc) {
			nsc.instance->OnUpdate(deltaTime);
		});
	}
}

void Scene::OnRender(const Ref<Framebuffer> &targetFrameBuffer /* = nullptr */)
{
	Camera *sceneCamera = nullptr;
	TransformComponent *sceneCameraTransform;

	/* scene camera */
	{
		m_registry.group(entt::get<TransformComponent, CameraComponent>)
		    .each([&](TransformComponent &transformComp, CameraComponent &cameraComp) {
			    if (cameraComp.isPrimary)
			    {
				    sceneCamera = &cameraComp.camera;
				    sceneCameraTransform = &transformComp;
			    }
		    });
	}

	/* draw quads */
	{
		if (sceneCamera)
		{
			Renderer::BeginScene(sceneCamera, *sceneCameraTransform, targetFrameBuffer);

			m_registry.group(entt::get<TransformComponent, SpriteRendererComponent>)
			    .each([](TransformComponent &transformComp,
			             SpriteRendererComponent &spriteRendererComp) {
				    Renderer::DrawQuad(
				        transformComp,
				        spriteRendererComp.tint,
				        spriteRendererComp.texture
				    );
			    });

			Renderer::EndScene();
		}
	}
}

Entity Scene::CreateEntity(const std::string &name, const TransformComponent &transform)
{
	return CreateEntityWithUUID(name, UUID(), transform);
}

Entity Scene::GetEntityByTag(const std::string &tag)
{
	// TagComponent tagComp(tag);
	// entt::entity entity = entt::to_entity(m_registry, tagComp);
	Entity entity;

	m_registry.view<TagComponent>().each([&](TagComponent &tagComp) {
		// if (tagComp.tag == tag)
		// 	entity = Entity(entt::to_entity(m_registry, tagComp), this);
	});

	if (entity.IsValid())
		return entity;
	else
	{
		ASSERT("Scene::GetEntityByTag: failed to find entity by tag: {}", tag);
		return Entity();
	}
}

Entity Scene::CreateEntityWithUUID(
    const std::string &name,
    UUID uuid,
    const TransformComponent &transform
)
{
	Entity entity { m_registry.create(), this };
	entity.AddComponent<TagComponent>(name);
	entity.AddComponent<TransformComponent>(transform);
	entity.AddComponent<UUIDComponent>(uuid);

	return entity;
}

} // namespace Light
