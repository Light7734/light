#include <renderer/vk/context/context.hpp>
#include <renderer/vk/context/instance.hpp>

namespace lt::renderer::vk {

Context::Context(const ecs::Entity &surface_entity)
    : m_surface(surface_entity)
    , m_device(m_surface)
    , m_swapchain(m_device, m_surface)
{
	ensure(m_surface.vk(), "Failed to create vulkan context: null surface");
	ensure(m_device.vk(), "Failed to create vulkan context: null device");
	ensure(m_swapchain.vk(), "Failed to create vulkan context: null swapchain");
}

} // namespace lt::renderer::vk
