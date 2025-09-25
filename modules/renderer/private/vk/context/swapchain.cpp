#include <ranges>
#include <renderer/vk/context/swapchain.hpp>

namespace lt::renderer::vk {

Swapchain::Swapchain(const Device &device, const Surface &surface): m_device(device.vk())
{
	auto *physical_device = device.physical();

	auto capabilities = VkSurfaceCapabilitiesKHR {};
	vkc(vk_get_physical_device_surface_capabilities(physical_device, surface.vk(), &capabilities));

	auto count = uint32_t { 0 };
	vkc(vk_get_physical_device_surface_formats(physical_device, surface.vk(), &count, nullptr));

	auto formats = std::vector<VkSurfaceFormatKHR>(count);
	vkc(vk_get_physical_device_surface_formats(
	    physical_device,
	    surface.vk(),
	    &count,
	    formats.data()
	));
	ensure(!formats.empty(), "Surface has no formats!");

	// TODO(Light): parameterize
	constexpr auto desired_swapchain_image_count = uint32_t { 3 };
	const auto surface_format = formats.front();
	const auto queue_indices = device.get_family_indices();

	auto create_info = VkSwapchainCreateInfoKHR {
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.surface = surface.vk(),
		.minImageCount = get_optimal_image_count(capabilities, desired_swapchain_image_count),
		.imageFormat = surface_format.format,
		.imageColorSpace = surface_format.colorSpace,
		.imageExtent = surface.get_framebuffer_size(),
		.imageArrayLayers = 1u,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = queue_indices.size(),
		.pQueueFamilyIndices = queue_indices.data(),
		.preTransform = capabilities.currentTransform,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = VK_PRESENT_MODE_FIFO_RELAXED_KHR, // TODO(Light): parameterize
		.clipped = VK_TRUE,
		.oldSwapchain = nullptr,
	};

	vkc(vk_create_swapchain_khr(device.vk(), &create_info, nullptr, &m_swapchain));
	vkc(vk_device_wait_idle(device.vk()));

	auto image_count = uint32_t { 0u };
	vk_get_swapchain_images_khr(device.vk(), m_swapchain, &image_count, nullptr);

	m_swapchain_images.resize(image_count);
	m_swapchain_image_views.resize(image_count);
	vk_get_swapchain_images_khr(device.vk(), m_swapchain, &image_count, m_swapchain_images.data());

	for (auto [image, view] : std::views::zip(m_swapchain_images, m_swapchain_image_views))
	{
		auto create_info = VkImageViewCreateInfo {
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.image = image,
			.viewType = VK_IMAGE_VIEW_TYPE_2D,
			.format = surface_format.format,
            .components = VkComponentMapping {
                .r = VK_COMPONENT_SWIZZLE_IDENTITY,
                .g = VK_COMPONENT_SWIZZLE_IDENTITY,
                .b = VK_COMPONENT_SWIZZLE_IDENTITY,
                .a = VK_COMPONENT_SWIZZLE_IDENTITY,
            },
            .subresourceRange = VkImageSubresourceRange {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .baseMipLevel = 0u,
                .levelCount = 1u,
                .baseArrayLayer = 0u,
                .layerCount = 1u,
            }
		};

		vkc(vk_create_image_view(device.vk(), &create_info, nullptr, &view));
	}
}

Swapchain::~Swapchain()
{
	try
	{
		if (m_device)
		{
			vkc(vk_device_wait_idle(m_device));
			for (auto &view : m_swapchain_image_views)
			{
				vk_destroy_image_view(m_device, view, nullptr);
			}

			vk_destroy_swapchain_khr(m_device, m_swapchain, nullptr);
		}
	}
	catch (const std::exception &exp)
	{
		log_err("Failed to destroy swapchain:");
		log_err("\twhat: {}", exp.what());
	}
}

[[nodiscard]] auto Swapchain::get_optimal_image_count(
    VkSurfaceCapabilitiesKHR capabilities,
    uint32_t desired_image_count
) const -> uint32_t
{
	const auto min_image_count = capabilities.minImageCount;
	const auto max_image_count = capabilities.maxImageCount;

	const auto has_max_limit = max_image_count != 0;

	// Desired image count is in range
	if ((!has_max_limit || max_image_count >= desired_image_count)
	    && min_image_count <= desired_image_count)
	{
		return desired_image_count;
	}

	// Fall-back to 2 if in ange
	if (min_image_count <= 2 && max_image_count >= 2)
	{
		return 2;
	}

	// Fall-back to min_image_count
	return min_image_count;
}


} // namespace lt::renderer::vk
