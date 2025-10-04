#include <renderer/backend/vk/context/context.hpp>
#include <renderer/backend/vk/context/device.hpp>
#include <renderer/backend/vk/context/gpu.hpp>
#include <renderer/backend/vk/context/instance.hpp>
#include <renderer/backend/vk/context/surface.hpp>
#include <renderer/backend/vk/context/swapchain.hpp>

namespace lt::renderer::vk {

Context::Context(const ecs::Entity &surface_entity)
    : m_instance(Instance::get())
    , m_surface(create_scope<Surface>(m_instance, surface_entity))
    , m_gpu(create_scope<Gpu>(m_instance))
    , m_device(create_scope<Device>(m_gpu.get(), m_surface.get()))
    , m_swapchain(create_scope<Swapchain>(m_surface.get(), m_gpu.get(), m_device.get()))
{
	ensure(
	    static_cast<Instance *>(m_instance)->vk(),
	    "Failed to create vulkan context: null instance"
	);

	ensure(
	    static_cast<Surface *>(m_surface.get())->vk(),
	    "Failed to create vulkan context: null surface"
	);

	ensure(static_cast<Gpu *>(m_gpu.get())->vk(), "Failed to create vulkan context: null gpu");

	ensure(
	    static_cast<Device *>(m_device.get())->vk(),
	    "Failed to create vulkan context: null device"
	);

	ensure(
	    static_cast<Swapchain *>(m_swapchain.get())->vk(),
	    "Failed to create vulkan context: null swapchain"
	);
}

} // namespace lt::renderer::vk
