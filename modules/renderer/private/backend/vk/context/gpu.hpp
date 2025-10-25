#pragma once

#include <memory/pointer_types/null_on_move.hpp>
#include <renderer/backend/vk/vulkan.hpp>
#include <renderer/frontend/context/gpu.hpp>
#include <renderer/frontend/context/instance.hpp>

namespace lt::renderer::vk {

class Gpu: public IGpu
{
public:
	Gpu(IInstance *instance);

	[[nodiscard]] auto vk() const -> VkPhysicalDevice
	{
		return m_gpu;
	}

	[[nodiscard]] auto get_queue_family_properties() const -> std::vector<VkQueueFamilyProperties>;

	[[nodiscard]] auto queue_family_supports_presentation(
	    VkSurfaceKHR surface,
	    uint32_t queue_family_idx
	) -> bool;

	[[nodiscard]] auto get_surface_capabilities(VkSurfaceKHR surface) const
	    -> VkSurfaceCapabilitiesKHR;

	[[nodiscard]] auto get_surface_formats(VkSurfaceKHR surface) const
	    -> std::vector<VkSurfaceFormatKHR>;

	[[nodiscard]] auto get_memory_properties() const -> VkPhysicalDeviceMemoryProperties;

private:
	memory::NullOnMove<VkPhysicalDevice> m_gpu = VK_NULL_HANDLE;
};

} // namespace lt::renderer::vk
