#pragma once

#include <memory/pointer_types/null_on_move.hpp>
#include <renderer/vk/debug/validation.hpp>
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

	[[nodiscard]] auto vk() const -> VkSwapchainKHR
	{
		return m_swapchain;
	}

	[[nodiscard]] auto get_resolution() const -> VkExtent2D
	{
		return m_resolution;
	}

	[[nodiscard]] auto get_format() const -> VkFormat
	{
		return m_format;
	}

	[[nodiscard]] auto create_framebuffers_for_pass(VkRenderPass pass) const
	    -> std::vector<VkFramebuffer>
	{
		auto framebuffers = std::vector<VkFramebuffer>(m_swapchain_image_views.size());

		for (auto idx = 0u; auto &framebuffer : framebuffers)
		{
			auto info = VkFramebufferCreateInfo {
				.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
				.renderPass = pass,
				.attachmentCount = 1u,
				.pAttachments = &m_swapchain_image_views[idx++],
				.width = m_resolution.width,
				.height = m_resolution.height,
				.layers = 1u
			};

			vkc(vk_create_frame_buffer(m_device, &info, nullptr, &framebuffer));
		}

		return framebuffers;
	}

private:
	[[nodiscard]] auto get_optimal_image_count(
	    VkSurfaceCapabilitiesKHR capabilities,
	    uint32_t desired_image_count
	) const -> uint32_t;

	memory::NullOnMove<VkDevice> m_device;

	memory::NullOnMove<VkSwapchainKHR> m_swapchain = VK_NULL_HANDLE;

	std::vector<VkImage> m_swapchain_images;

	std::vector<VkImageView> m_swapchain_image_views;

	VkExtent2D m_resolution;

	VkFormat m_format;
};

} // namespace lt::renderer::vk
