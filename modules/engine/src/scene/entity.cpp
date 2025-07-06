#include <engine/scene/entity.hpp>
#include <engine/scene/scene.hpp>

namespace Light {

Entity::Entity(entt::entity handle, Scene *scene): m_handle(handle), m_scene(scene)
{
}

Entity::~Entity()
= default;

} // namespace Light
