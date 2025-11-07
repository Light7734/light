export module renderer.backend.vk.gpu;
import renderer.backend.vk.library_wrapper;
import debug.assertions;
import renderer.frontend.instance;
import renderer.frontend.gpu;
import renderer.backend.vk.instance;
import memory.null_on_move;
import std;

namespace lt::renderer::vkb {

export class Gpu: public IGpu
{
public:
	Gpu(IInstance *instance);

	// [[nodiscard]] auto queue_family_supports_presentation(
	//     VkSurfaceKHR surface,
	//     uint32_t queue_family_idx
	// ) -> bool;
	//
	// [[nodiscard]] auto get_surface_capabilities(VkSurfaceKHR surface) const
	//     -> VkSurfaceCapabilitiesKHR;
	//
	// [[nodiscard]] auto get_surface_formats(VkSurfaceKHR surface) const
	//     -> std::vector<VkSurfaceFormatKHR>;
	//
	// [[nodiscard]] auto get_properties() const -> VkPhysicalDeviceProperties
	// {
	// 	return m_properties;
	// }
	//
	// [[nodiscard]] auto get_descriptor_indexing_features() const
	//     -> VkPhysicalDeviceDescriptorIndexingFeatures
	// {
	// 	return m_descriptor_indexing_features;
	// }
	//
	// [[nodiscard]] auto get_memory_properties() const -> VkPhysicalDeviceMemoryProperties
	// {
	// 	return m_memory_properties;
	// }
	//
	// [[nodiscard]] auto get_queue_family_properties() const ->
	// std::vector<VkQueueFamilyProperties>
	// {
	// 	return m_queue_family_properties;
	// }

private:
	vk::Gpu m_gpu;

	vk::Gpu::Properties m_properties {};

	// VkPhysicalDeviceDescriptorIndexingFeatures m_descriptor_indexing_features;

	vk::Gpu::MemoryProperties m_memory_properties {};

	std::vector<vk::Gpu::QueueFamilyProperties> m_queue_family_properties;
};

} // namespace lt::renderer::vkb


module :private;
using namespace lt::renderer::vkb;

Gpu::Gpu(IInstance *instance)
{
	auto gpus = vk::Gpu::enumerate(static_cast<Instance *>(instance)->vk());

	for (auto &gpu : gpus)
	{
		auto properties = gpu.get_properties();
		auto features = gpu.get_features();

		if (properties.device_type == vk::Gpu::Type::discrete_gpu && features.geometry_shader)
		{
			m_gpu = gpu;
		}
	}

	debug::ensure(m_gpu, "Failed to find any suitable Vulkan physical device");

	m_memory_properties = m_gpu.get_memory_properties();
	m_queue_family_properties = m_gpu.get_queue_family_properties();
}

// [[nodiscard]] auto Gpu::queue_family_supports_presentation(
//     VkSurfaceKHR surface,
//     uint32_t queue_family_idx
// ) -> bool
// {
// 	auto supported = VkBool32 { false };
// 	vkc(vk_get_physical_device_surface_support(m_gpu, queue_family_idx, surface, &supported));
//
// 	return supported;
// }
//
// [[nodiscard]] auto Gpu::get_surface_capabilities(VkSurfaceKHR surface) const
//     -> VkSurfaceCapabilitiesKHR
// {
// 	auto capabilities = VkSurfaceCapabilitiesKHR {};
// 	vkc(vk_get_physical_device_surface_capabilities(m_gpu, surface, &capabilities));
// 	return capabilities;
// }
//
// [[nodiscard]] auto Gpu::get_surface_formats(VkSurfaceKHR surface) const
//     -> std::vector<VkSurfaceFormatKHR>
// {
// 	auto count = uint32_t { 0u };
// 	vkc(vk_get_physical_device_surface_formats(m_gpu, surface, &count, nullptr));
//
// 	auto formats = std::vector<VkSurfaceFormatKHR>(count);
// 	vkc(vk_get_physical_device_surface_formats(m_gpu, surface, &count, formats.data()));
//
// 	return formats;
// }

// [[nodiscard]] auto Gpu::create_device(VkDeviceCreateInfo info) const -> VkDevice
// {
// 	auto *device = VkDevice {};
// 	vkc(vk_create_device(m_gpu, &info, nullptr, &device));
// 	return device;
// }
