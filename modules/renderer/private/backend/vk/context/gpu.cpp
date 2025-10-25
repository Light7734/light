#include <renderer/backend/vk/context/gpu.hpp>
#include <renderer/backend/vk/context/instance.hpp>
#include <renderer/backend/vk/utils.hpp>

namespace lt::renderer::vk {

Gpu::Gpu(IInstance *instance)
{
	auto gpus = static_cast<Instance *>(instance)->enumerate_gpus();

	for (auto &gpu : gpus)
	{
		auto properties = VkPhysicalDeviceProperties {};
		auto features = VkPhysicalDeviceFeatures {};

		vk_get_physical_device_properties(gpu, &properties);
		vk_get_physical_device_features(gpu, &features);

		if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
		    && features.geometryShader)
		{
			m_gpu = gpu;
		}
	}
	ensure(m_gpu, "Failed to find any suitable Vulkan physical device");
}

[[nodiscard]] auto Gpu::get_queue_family_properties() const -> std::vector<VkQueueFamilyProperties>
{
	auto count = uint32_t { 0u };
	vk_get_physical_device_queue_family_properties(m_gpu, &count, nullptr);

	auto properties = std::vector<VkQueueFamilyProperties>(count);
	vk_get_physical_device_queue_family_properties(m_gpu, &count, properties.data());

	return properties;
}

[[nodiscard]] auto Gpu::queue_family_supports_presentation(
    VkSurfaceKHR surface,
    uint32_t queue_family_idx
) -> bool
{
	auto supported = VkBool32 { false };
	vkc(vk_get_physical_device_surface_support(m_gpu, queue_family_idx, surface, &supported));

	return supported;
}

[[nodiscard]] auto Gpu::get_surface_capabilities(VkSurfaceKHR surface) const
    -> VkSurfaceCapabilitiesKHR
{
	auto capabilities = VkSurfaceCapabilitiesKHR {};
	vkc(vk_get_physical_device_surface_capabilities(m_gpu, surface, &capabilities));
	return capabilities;
}

[[nodiscard]] auto Gpu::get_surface_formats(VkSurfaceKHR surface) const
    -> std::vector<VkSurfaceFormatKHR>
{
	auto count = uint32_t { 0u };
	vkc(vk_get_physical_device_surface_formats(m_gpu, surface, &count, nullptr));

	auto formats = std::vector<VkSurfaceFormatKHR>(count);
	vkc(vk_get_physical_device_surface_formats(m_gpu, surface, &count, formats.data()));

	return formats;
}

[[nodiscard]] auto Gpu::get_memory_properties() const -> VkPhysicalDeviceMemoryProperties
{
	auto memory_properties = VkPhysicalDeviceMemoryProperties {};
	vk_get_physical_device_memory_properties(m_gpu, &memory_properties);
	return memory_properties;
}

} // namespace lt::renderer::vk
