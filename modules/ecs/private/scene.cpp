#include <ecs/components.hpp>
#include <ecs/entity.hpp>
#include <ecs/scene.hpp>

namespace lt {

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

	ensure(false, "Scene::get_entity_by_tag: failed to find entity by tag: {}", tag);
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

} // namespace lt
