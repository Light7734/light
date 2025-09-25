#include <renderer/vk/context/device.hpp>

namespace lt::renderer::vk {

Device::Device(const Surface &surface)
{
	initialize_physical_device();
	initialize_logical_device();
	Instance::load_device_functions(m_device);
	initialize_queue(surface);
}

Device::~Device()
{
	if (m_device)
	{
		vkc(vk_device_wait_idle(m_device));
		vk_destroy_device(m_device, nullptr);
	}
}

void Device::initialize_physical_device()
{
	auto count = 0u;
	vkc(vk_enumerate_physical_devices(Instance::get(), &count, nullptr));
	ensure(count != 0u, "Failed to find any physical devices with Vulkan support");

	auto devices = std::vector<VkPhysicalDevice>(count);
	vkc(vk_enumerate_physical_devices(Instance::get(), &count, devices.data()));

	for (auto &device : devices)
	{
		auto properties = VkPhysicalDeviceProperties {};
		auto features = VkPhysicalDeviceFeatures {};

		vk_get_physical_device_properties(device, &properties);
		vk_get_physical_device_features(device, &features);

		if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
		    && features.geometryShader)
		{
			m_physical_device = device;
		}
	}
	ensure(m_physical_device, "Failed to find any suitable Vulkan physical device");
}

void Device::initialize_logical_device()
{
	const float priorities = .0f;

	auto queue_info = VkDeviceQueueCreateInfo {
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		.queueFamilyIndex = find_suitable_queue_family(),
		.queueCount = 1u,
		.pQueuePriorities = &priorities,
	};

	auto physical_device_features = VkPhysicalDeviceFeatures {};

	auto extensions = std::vector<const char *> {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
	};

	auto device_info = VkDeviceCreateInfo {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &queue_info,
		.enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
		.ppEnabledExtensionNames = extensions.data(),
		.pEnabledFeatures = &physical_device_features,
	};

	ensure(
	    !vk_create_device(m_physical_device, &device_info, nullptr, &m_device),
	    "Failed to create logical vulkan device"
	);
}

[[nodiscard]] auto Device::find_suitable_queue_family() const -> uint32_t
{
	auto count = 0u;
	vk_get_physical_device_queue_family_properties(m_physical_device, &count, nullptr);
	ensure(count != 0u, "Failed to find any physical devices with Vulkan support");

	auto families = std::vector<VkQueueFamilyProperties>(count);
	vk_get_physical_device_queue_family_properties(m_physical_device, &count, families.data());

	const auto required_flags = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT;
	for (auto idx = 0u; auto &family : families)
	{
		if ((family.queueFlags & required_flags) == required_flags)
		{
			return idx;
		}
	}

	ensure(false, "Failed to find a suitable Vulkan queue family");
	return 0;
}

void Device::initialize_queue(const Surface &surface)
{
	vk_get_device_queue(m_device, find_suitable_queue_family(), 0, &m_queue);

	auto count = uint32_t { 0u };
	vk_get_physical_device_queue_family_properties(m_physical_device, &count, nullptr);

	auto properties = std::vector<VkQueueFamilyProperties>(count);
	vk_get_physical_device_queue_family_properties(m_physical_device, &count, properties.data());

	for (auto idx = uint32_t { 0u }; const auto &property : properties)
	{
		if (property.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			m_graphics_queue_family_index = idx;
		}

		auto has_presentation_support = VkBool32 { false };
		vkc(vk_get_physical_device_surface_support(
		    m_physical_device,
		    idx,
		    surface.vk(),
		    &has_presentation_support
		));
		if (has_presentation_support)
		{
			m_present_queue_family_index = idx;
		}

		++idx;

		if (m_graphics_queue_family_index != VK_QUEUE_FAMILY_IGNORED
		    && m_present_queue_family_index != VK_QUEUE_FAMILY_IGNORED)
		{
			break;
		}
	}

	ensure(
	    m_graphics_queue_family_index != VK_QUEUE_FAMILY_IGNORED,
	    "Failed to find graphics queue family"
	);

	ensure(
	    m_present_queue_family_index != VK_QUEUE_FAMILY_IGNORED,
	    "Failed to find presentation queue family"
	);
}

} // namespace lt::renderer::vk
