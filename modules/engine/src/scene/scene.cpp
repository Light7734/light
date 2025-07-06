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

void Scene::on_create()
{
	/* native scripts */
	{
		m_registry.view<NativeScriptComponent>().each([](NativeScriptComponent &nsc) {
			if (nsc.instance == nullptr)
			{
				nsc.instance = nsc.CreateInstance();
				nsc.instance->on_create();
			}
		});
	}
}

void Scene::on_update(float deltaTime)
{
	/* native scripts */
	{
		m_registry.view<NativeScriptComponent>().each([=](NativeScriptComponent &nsc) {
			nsc.instance->on_update(deltaTime);
		});
	}
}

void Scene::on_render(const Ref<Framebuffer> &targetFrameBuffer /* = nullptr */)
{
	auto *sceneCamera = (Camera *) {};
	auto *sceneCameraTransform = (TransformComponent *) {};

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
			Renderer::begin_scene(sceneCamera, *sceneCameraTransform, targetFrameBuffer);

			m_registry.group(entt::get<TransformComponent, SpriteRendererComponent>)
			    .each([](TransformComponent &transformComp,
			             SpriteRendererComponent &spriteRendererComp) {
				    Renderer::draw_quad(
				        transformComp,
				        spriteRendererComp.tint,
				        spriteRendererComp.texture
				    );
			    });

			Renderer::end_scene();
		}
	}
}

auto Scene::create_entity(const std::string &name, const TransformComponent &transform) -> Entity
{
	return create_entity_with_uuid(name, UUID(), transform);
}

auto Scene::get_entity_by_tag(const std::string &tag) -> Entity
{
	// TagComponent tagComp(tag);
	// entt::entity entity = entt::to_entity(m_registry, tagComp);
	auto entity = Entity {};

	m_registry.view<TagComponent>().each([&](TagComponent &tagComp) {
		// if (tagComp.tag == tag)
		// 	entity = entity(entt::to_entity(m_registry, tagComp), this);
	});

	if (entity.is_valid())
	{
		return entity;
	}

	lt_assert(false, "Scene::get_entity_by_tag: failed to find entity by tag: {}", tag);
	return {};
}

auto Scene::create_entity_with_uuid(
    const std::string &name,
    UUID uuid,
    const TransformComponent &transform
) -> Entity
{
	auto entity = Entity { m_registry.create(), this };
	entity.add_component<TagComponent>(name);
	entity.add_component<TransformComponent>(transform);
	entity.add_component<UUIDComponent>(uuid);

	return entity;
}

} // namespace Light
