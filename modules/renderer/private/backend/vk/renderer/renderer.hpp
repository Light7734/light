#pragma once

#include <memory/reference.hpp>
#include <ranges>
#include <renderer/backend/vk/context/context.hpp>
#include <renderer/backend/vk/context/device.hpp>
#include <renderer/backend/vk/renderer/pass.hpp>
#include <renderer/backend/vk/utils.hpp>
#include <renderer/frontend/context/context.hpp>
#include <renderer/frontend/renderer/pass.hpp>
#include <renderer/frontend/renderer/renderer.hpp>

namespace lt::renderer::vk {

class Renderer: public IRenderer
{
public:
	Renderer(IContext &context, uint32_t max_frames_in_flight);

	~Renderer() override;

	Renderer(Renderer &&) = default;

	Renderer(const Renderer &) = delete;

	auto operator=(Renderer &&) -> Renderer & = default;

	auto operator=(const Renderer &) -> Renderer & = delete;

	[[nodiscard]] DrawResult draw(uint32_t frame_idx) override;

	void replace_swapchain(ISwapchain *swapchain) override;

private:
	void record_cmd(VkCommandBuffer cmd, uint32_t image_idx);

	memory::NullOnMove<class Device *> m_device {};

	class Swapchain *m_swapchain {};

	memory::Ref<class Pass> m_pass;

	VkCommandPool m_pool = VK_NULL_HANDLE;

	std::vector<VkCommandBuffer> m_cmds;

	std::vector<VkFence> m_frame_fences;

	std::vector<VkSemaphore> m_aquire_image_semaphores;

	std::vector<VkSemaphore> m_submit_semaphores;

	VkExtent2D m_resolution;

	uint32_t m_max_frames_in_flight {};
};

} // namespace lt::renderer::vk
