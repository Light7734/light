#pragma once

#include <memory/reference.hpp>
#include <ranges>
#include <renderer/backend/vk/context/device.hpp>
#include <renderer/backend/vk/data/buffer.hpp>
#include <renderer/backend/vk/renderer/pass.hpp>
#include <renderer/backend/vk/utils.hpp>
#include <renderer/frontend/data/buffer.hpp>
#include <renderer/frontend/renderer/pass.hpp>
#include <renderer/frontend/renderer/renderer.hpp>

namespace lt::renderer::vk {

class Renderer: public IRenderer
{
public:
	Renderer(
	    class IGpu *gpu,
	    class IDevice *device,
	    class ISwapchain *swapchain,
	    uint32_t max_frames_in_flight
	);

	~Renderer() override;

	Renderer(Renderer &&) = default;

	Renderer(const Renderer &) = delete;

	auto operator=(Renderer &&) -> Renderer & = default;

	auto operator=(const Renderer &) -> Renderer & = delete;

	[[nodiscard]] auto frame(uint32_t frame_idx, std::function<void()> submit_scene)
	    -> Result override;

	void replace_swapchain(ISwapchain *swapchain) override;

	void set_frame_constants(FrameConstants constants) override
	{
		m_frame_constants = constants;
	}

	void submit_sprite(
	    const components::Sprite &sprite,
	    const math::components::Transform &transform
	) override;

private:
	void record_cmd(VkCommandBuffer cmd, uint32_t image_idx);

	void map_buffers(uint32_t frame_idx);

	void flush_buffers(VkCommandBuffer cmd);

	memory::NullOnMove<class Device *> m_device {};

	class Swapchain *m_swapchain {};

	memory::Ref<class Pass> m_pass;

	VkCommandPool m_pool = VK_NULL_HANDLE;

	VkCommandPool m_transient_pool = VK_NULL_HANDLE;

	std::vector<VkCommandBuffer> m_cmds;

	std::vector<VkFence> m_frame_fences;

	std::vector<VkSemaphore> m_aquire_image_semaphores;

	std::vector<VkSemaphore> m_submit_semaphores;

	VkExtent2D m_resolution;

	uint32_t m_max_frames_in_flight {};

	FrameConstants m_frame_constants;

	Buffer m_vertex_buffer;

	Buffer m_staging_buffer;

	size_t m_staging_offset;

	std::span<std::byte> m_staging_map;

	std::span<components::Sprite::Vertex> m_sprite_vertex_map;

	size_t m_current_sprite_idx;
};

} // namespace lt::renderer::vk
