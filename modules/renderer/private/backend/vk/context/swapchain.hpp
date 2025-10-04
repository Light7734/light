#pragma once

#include <memory/pointer_types/null_on_move.hpp>
#include <renderer/backend/vk/utils.hpp>
#include <renderer/backend/vk/vulkan.hpp>
#include <renderer/frontend/context/device.hpp>
#include <renderer/frontend/context/gpu.hpp>
#include <renderer/frontend/context/surface.hpp>
#include <renderer/frontend/context/swapchain.hpp>

namespace lt::renderer::vk {

class Swapchain: public ISwapchain
{
public:
	Swapchain(ISurface *surface, IGpu *gpu, IDevice *device);
	~Swapchain() override;

	Swapchain(Swapchain &&) = default;

	Swapchain(const Swapchain &) = delete;

	auto operator=(Swapchain &&) -> Swapchain & = default;

	auto operator=(const Swapchain &) const -> Swapchain & = delete;

	[[nodiscard]] auto vk() const -> VkSwapchainKHR
	{
		return m_swapchain;
	}

	[[nodiscard]] auto vk_ptr() -> VkSwapchainKHR *
	{
		return &m_swapchain;
	}

	[[nodiscard]] auto get_resolution() const -> VkExtent2D
	{
		return m_resolution;
	}

	[[nodiscard]] auto get_format() const -> VkFormat
	{
		return m_format;
	}

	[[nodiscard]] auto get_image_count() const -> size_t
	{
		return m_images.size();
	}

	[[nodiscard]] auto create_framebuffers_for_pass(VkRenderPass pass) const
	    -> std::vector<VkFramebuffer>;

private:
	[[nodiscard]] auto get_optimal_image_count(
	    VkSurfaceCapabilitiesKHR capabilities,
	    uint32_t desired_image_count
	) const -> uint32_t;

	memory::NullOnMove<class Surface *> m_surface {};

	class Gpu *m_gpu {};

	class Device *m_device {};

	VkSwapchainKHR m_swapchain = VK_NULL_HANDLE;

	std::vector<VkImage> m_images;

	std::vector<VkImageView> m_image_views;

	VkExtent2D m_resolution {};

	VkFormat m_format {};
};

} // namespace lt::renderer::vk
