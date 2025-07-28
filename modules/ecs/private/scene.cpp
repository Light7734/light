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
