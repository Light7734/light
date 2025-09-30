#pragma once

#include <memory/pointer_types/null_on_move.hpp>
#include <renderer/vk/vulkan.hpp>

namespace lt::renderer::vk {

class Swapchain
{
public:
	Swapchain(const class Device &device, const class Surface &surface);

	~Swapchain();

	Swapchain(Swapchain &&) = default;

	Swapchain(const Swapchain &) = delete;

	auto operator=(Swapchain &&) -> Swapchain & = default;

	auto operator=(const Swapchain &) const -> Swapchain & = delete;

private:
	[[nodiscard]] auto get_optimal_image_count(
	    VkSurfaceCapabilitiesKHR capabilities,
	    uint32_t desired_image_count
	) const -> uint32_t;

	memory::NullOnMove<VkDevice> m_device;

	memory::NullOnMove<VkSwapchainKHR> m_swapchain = VK_NULL_HANDLE;

	std::vector<VkImage> m_swapchain_images;

	std::vector<VkImageView> m_swapchain_image_views;
};

} // namespace lt::renderer::vk
