#include <renderer/backend/vk/context/gpu.hpp>
#include <renderer/backend/vk/context/instance.hpp>
#include <renderer/backend/vk/utils.hpp>

namespace lt::renderer::vk {

Gpu::Gpu(IInstance *instance)
    : m_descriptor_indexing_features(
          { .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES }
      )
{
	auto gpus = static_cast<Instance *>(instance)->enumerate_gpus();

	for (auto &gpu : gpus)
	{
		auto properties = VkPhysicalDeviceProperties {};
		auto features = VkPhysicalDeviceFeatures2 {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
			.pNext = &m_descriptor_indexing_features
		};

		vk_get_physical_device_properties(gpu, &properties);
		vk_get_physical_device_features(gpu, &features);

		if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
		    && features.features.geometryShader)
		{
			m_gpu = gpu;
		}
	}
	ensure(m_gpu, "Failed to find any suitable Vulkan physical device");


	vk_get_physical_device_memory_properties(m_gpu, &m_memory_properties);

	auto count = uint32_t { 0u };
	vk_get_physical_device_queue_family_properties(m_gpu, &count, nullptr);
	m_queue_family_properties.resize(count);
	vk_get_physical_device_queue_family_properties(m_gpu, &count, m_queue_family_properties.data());
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

[[nodiscard]] auto Gpu::create_device(VkDeviceCreateInfo info) const -> VkDevice
{
	auto *device = VkDevice {};
	vkc(vk_create_device(m_gpu, &info, nullptr, &device));
	return device;
}

} // namespace lt::renderer::vk
