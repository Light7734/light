#include <renderer/vk/context/context.hpp>
#include <renderer/vk/context/instance.hpp>

namespace lt::renderer::vk {

Context::Context(const ecs::Entity &surface_entity)
    : m_surface(surface_entity)
    , m_device(m_surface)
    , m_swapchain(m_device, m_surface)
{
}

} // namespace lt::renderer::vk
