#include <engine/scene/entity.hpp>
#include <engine/scene/scene.hpp>

namespace Light {

Entity::Entity(entt::entity handle, Scene *scene): m_Handle(handle), m_Scene(scene)
{
}

Entity::~Entity()
{
}

} // namespace Light
