#include <ranges>
#include <renderer/backend/vk/context/device.hpp>
#include <renderer/backend/vk/context/gpu.hpp>
#include <renderer/backend/vk/context/instance.hpp>
#include <renderer/backend/vk/context/surface.hpp>
#include <renderer/backend/vk/context/swapchain.hpp>
#include <renderer/backend/vk/utils.hpp>

namespace lt::renderer::vk {

Swapchain::Swapchain(ISurface *surface, IGpu *gpu, IDevice *device)
    : m_surface(static_cast<Surface *>(surface))
    , m_gpu(static_cast<Gpu *>(gpu))
    , m_device(static_cast<Device *>(device))
{
	static auto idx = 0u;

	const auto capabilities = m_gpu->get_surface_capabilities(m_surface->vk());
	const auto formats = m_gpu->get_surface_formats(m_surface->vk());

	// TODO(Light): parameterize
	constexpr auto desired_image_count = uint32_t { 3 };
	const auto surface_format = formats.front();
	const auto queue_indices = m_device->get_family_indices();
	m_format = surface_format.format;

	m_swapchain = m_device->create_swapchain(
	    VkSwapchainCreateInfoKHR {
	        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
	        .surface = m_surface->vk(),
	        .minImageCount = get_optimal_image_count(capabilities, desired_image_count),
	        .imageFormat = surface_format.format,
	        .imageColorSpace = surface_format.colorSpace,
	        .imageExtent = capabilities.currentExtent,
	        .imageArrayLayers = 1u,
	        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
	        .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
	        .queueFamilyIndexCount = queue_indices.size(),
	        .pQueueFamilyIndices = queue_indices.data(),
	        .preTransform = capabilities.currentTransform,
	        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
	        .presentMode = VK_PRESENT_MODE_FIFO_KHR, // TODO(Light): parameterize
	        .clipped = VK_TRUE,
	        .oldSwapchain = nullptr,
	    }
	);
	m_device->name(m_swapchain, "swapchain {}", idx++);
	m_device->wait_idle();


	m_images = m_device->get_swapchain_images(m_swapchain);
	m_image_views.resize(m_images.size());
	for (auto idx = 0u; auto [image, view] : std::views::zip(m_images, m_image_views))
	{
		view = m_device->create_image_view(VkImageViewCreateInfo {
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
		});

		m_device->name(image, "swapchain image {}", idx++);
		m_device->name(view, "swapchain image view {}", idx++);
	}
}

Swapchain::~Swapchain()
{
	if (!m_surface)
	{
		return;
	}

	try
	{
		m_device->wait_idle();
		m_device->destroy_image_views(m_image_views);
		m_device->destroy_swapchain(m_swapchain);
	}
	catch (const std::exception &exp)
	{
		log_err("Failed to destroy swapchain:");
		log_err("\twhat: {}", exp.what());
	}
}


[[nodiscard]] auto Swapchain::create_framebuffers_for_pass(VkRenderPass pass) const
    -> std::vector<VkFramebuffer>
{
	auto framebuffers = std::vector<VkFramebuffer>(m_image_views.size());

	for (auto idx = 0u; auto &framebuffer : framebuffers)
	{
		framebuffer = m_device->create_framebuffer(
		    VkFramebufferCreateInfo {
		        .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
		        .renderPass = pass,
		        .attachmentCount = 1u,
		        .pAttachments = &m_image_views[idx++],
		        .width = m_resolution.width,
		        .height = m_resolution.height,
		        .layers = 1u,
		    }
		);
	}

	return framebuffers;
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
