#pragma once

#include <renderer/vk/context/context.hpp>
#include <renderer/vk/debug/validation.hpp>
#include <renderer/vk/renderer/pass.hpp>
#include <time/timer.hpp>

namespace lt::renderer::vk {

class Renderer
{
public:
	Renderer(Context &context, Ref<Pass> pass)
	    : m_device(context.device().vk())
	    , m_graphics_queue(context.device().get_graphics_queue())
	    , m_present_queue(context.device().get_present_queue())
	    , m_swapchain(context.swapchain().vk())
	    , m_pass(std::move(pass))
	    , m_resolution(context.swapchain().get_resolution())
	{
		auto pool_info = VkCommandPoolCreateInfo {
			.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
			.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
			.queueFamilyIndex = context.device().get_family_indices()[0],

		};
		vkc(vk_create_command_pool(m_device, &pool_info, nullptr, &m_pool));

		auto cmd_info = VkCommandBufferAllocateInfo {
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
			.commandPool = m_pool,
			.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
			.commandBufferCount = 1u,
		};
		vkc(vk_allocate_command_buffers(m_device, &cmd_info, &m_cmd));

		auto semaphore_info = VkSemaphoreCreateInfo {
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		};

		auto fence_info = VkFenceCreateInfo {
			.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
			.flags = VK_FENCE_CREATE_SIGNALED_BIT,
		};

		vkc(vk_create_semaphore(m_device, &semaphore_info, nullptr, &m_image_available_semaphore));
		vkc(vk_create_semaphore(m_device, &semaphore_info, nullptr, &m_render_finished_semaphore));
		vkc(vk_create_fence(m_device, &fence_info, nullptr, &m_in_flight_fence));
	};

	void record_cmd(VkCommandBuffer cmd, uint32_t image_idx)
	{
		auto cmd_begin_info = VkCommandBufferBeginInfo {
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
			.flags = {},
			.pInheritanceInfo = nullptr,
		};

		vkc(vk_begin_command_buffer(cmd, &cmd_begin_info));

		static auto timer = Timer {};

		auto clear_value = VkClearValue {
			.color = { 
                0.93,
                0.93,
                0.93,
               1.0,
            },
		};

		auto pass_begin_info = VkRenderPassBeginInfo {
			.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
			.renderPass = m_pass->get_pass(),
			.framebuffer = m_pass->get_framebuffers()[image_idx],
			.renderArea = { .offset = {}, .extent = m_resolution },
			.clearValueCount = 1u,
			.pClearValues = &clear_value
		};
		vk_cmd_begin_render_pass(cmd, &pass_begin_info, VK_SUBPASS_CONTENTS_INLINE);
		vk_cmd_bind_pipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pass->get_pipeline());

		auto viewport = VkViewport {
			.x = 0.0f,
			.y = 0.0f,
			.width = static_cast<float>(m_resolution.width),
			.height = static_cast<float>(m_resolution.height),
			.minDepth = 0.0f,
			.maxDepth = 1.0f,
		};
		vk_cmd_set_viewport(cmd, 0, 1, &viewport);

		auto scissor = VkRect2D {
			.offset = { 0u, 0u },
			.extent = m_resolution,
		};
		vk_cmd_set_scissors(cmd, 0, 1, &scissor);

		vk_cmd_draw(cmd, 3, 1, 0, 0);
		vk_cmd_end_render_pass(cmd);
		vkc(vk_end_command_buffer(cmd));
	}

	void draw()
	{
		try
		{
			vkc(vk_wait_for_fences(m_device, 1u, &m_in_flight_fence, VK_TRUE, UINT64_MAX));
			vkc(vk_reset_fences(m_device, 1u, &m_in_flight_fence));

			auto image_idx = uint32_t {};
			vkc(vk_acquire_next_image_khr(
			    m_device,
			    m_swapchain,
			    UINT64_MAX,
			    m_image_available_semaphore,
			    VK_NULL_HANDLE,
			    &image_idx
			));

			vkc(vk_reset_command_buffer(m_cmd, {}));
			record_cmd(m_cmd, image_idx);

			auto wait_stage = VkPipelineStageFlags {
				VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
			};
			auto submit_info = VkSubmitInfo {
				.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
				.waitSemaphoreCount = 1u,
				.pWaitSemaphores = &m_image_available_semaphore,
				.pWaitDstStageMask = &wait_stage,
				.commandBufferCount = 1u,
				.pCommandBuffers = &m_cmd,
				.signalSemaphoreCount = 1u,
				.pSignalSemaphores = &m_render_finished_semaphore,
			};

			vkc(vk_queue_submit(m_graphics_queue, 1u, &submit_info, m_in_flight_fence));

			auto present_info = VkPresentInfoKHR {
				.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
				.waitSemaphoreCount = 1u,
				.pWaitSemaphores = &m_render_finished_semaphore,
				.swapchainCount = 1u,
				.pSwapchains = &m_swapchain,
				.pImageIndices = &image_idx,
				.pResults = nullptr,
			};

			vk_queue_present_khr(m_present_queue, &present_info);
		}
		catch (const std::exception &exp)
		{
			log_dbg("EXCEPTION: {}", exp.what());
		}
	}

	~Renderer()
	{
		if (!m_device)
		{
			return;
		}

		vk_destroy_semaphore(m_device, m_render_finished_semaphore, nullptr);
		vk_destroy_semaphore(m_device, m_image_available_semaphore, nullptr);
		vk_destroy_fence(m_device, m_in_flight_fence, nullptr);
		vk_destroy_command_pool(m_device, m_pool, nullptr);
	}

	Renderer(Renderer &&) = default;

	Renderer(const Renderer &) = delete;

	auto operator=(Renderer &&) -> Renderer & = default;

	auto operator=(const Renderer &) -> Renderer & = delete;

private:
	memory::NullOnMove<VkDevice> m_device = VK_NULL_HANDLE;

	memory::NullOnMove<VkCommandPool> m_pool = VK_NULL_HANDLE;

	memory::NullOnMove<VkCommandBuffer> m_cmd = VK_NULL_HANDLE;

	memory::NullOnMove<VkSemaphore> m_image_available_semaphore = VK_NULL_HANDLE;

	memory::NullOnMove<VkSemaphore> m_render_finished_semaphore = VK_NULL_HANDLE;

	memory::NullOnMove<VkFence> m_in_flight_fence = VK_NULL_HANDLE;

	memory::NullOnMove<VkSwapchainKHR> m_swapchain = VK_NULL_HANDLE;

	memory::NullOnMove<VkQueue> m_graphics_queue = VK_NULL_HANDLE;

	memory::NullOnMove<VkQueue> m_present_queue = VK_NULL_HANDLE;

	Ref<Pass> m_pass;

	VkExtent2D m_resolution;
};

} // namespace lt::renderer::vk
