#pragma once

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>

namespace lt::renderer::vk {

class Swapchain
{
public:
	Swapchain()
	{
	}

private:
	VkSwapchainKHR m_swapchain {};

	std::vector<VkImage> images;
	std::vector<VkImageView> image_views;
};

} // namespace lt::renderer::vk
