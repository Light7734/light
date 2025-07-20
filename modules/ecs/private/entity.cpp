#include <ecs/entity.hpp>
#include <ecs/scene.hpp>

namespace lt {

Entity::Entity(entt::entity handle, Scene *scene): m_handle(handle), m_scene(scene)
{
}

} // namespace lt
