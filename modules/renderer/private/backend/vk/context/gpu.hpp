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

	[[nodiscard]] auto queue_family_supports_presentation(
	    VkSurfaceKHR surface,
	    uint32_t queue_family_idx
	) -> bool;

	[[nodiscard]] auto get_surface_capabilities(VkSurfaceKHR surface) const
	    -> VkSurfaceCapabilitiesKHR;

	[[nodiscard]] auto get_surface_formats(VkSurfaceKHR surface) const
	    -> std::vector<VkSurfaceFormatKHR>;

	[[nodiscard]] auto create_device(VkDeviceCreateInfo info) const -> VkDevice;

	[[nodiscard]] auto get_properties() const -> VkPhysicalDeviceProperties
	{
		return m_properties;
	}

	[[nodiscard]] auto get_descriptor_indexing_features() const
	    -> VkPhysicalDeviceDescriptorIndexingFeatures
	{
		return m_descriptor_indexing_features;
	}

	[[nodiscard]] auto get_memory_properties() const -> VkPhysicalDeviceMemoryProperties
	{
		return m_memory_properties;
	}

	[[nodiscard]] auto get_queue_family_properties() const -> std::vector<VkQueueFamilyProperties>
	{
		return m_queue_family_properties;
	}

private:
	memory::NullOnMove<VkPhysicalDevice> m_gpu = VK_NULL_HANDLE;

	VkPhysicalDeviceProperties m_properties {};

	VkPhysicalDeviceDescriptorIndexingFeatures m_descriptor_indexing_features;

	VkPhysicalDeviceMemoryProperties m_memory_properties {};

	std::vector<VkQueueFamilyProperties> m_queue_family_properties;
};

} // namespace lt::renderer::vk
