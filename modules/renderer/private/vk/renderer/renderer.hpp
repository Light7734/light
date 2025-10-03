#pragma once

#include <ranges>
#include <renderer/vk/context/context.hpp>
#include <renderer/vk/debug/validation.hpp>
#include <renderer/vk/renderer/pass.hpp>
#include <time/timer.hpp>

namespace lt::renderer::vk {

class Renderer
{
public:
	static constexpr auto max_frames_in_flight = uint32_t { 3u };

	Renderer(Context &context, Ref<Pass> pass)
	    : m_device(context.device().vk())
	    , m_graphics_queue(context.device().get_graphics_queue())
	    , m_present_queue(context.device().get_present_queue())
	    , m_swapchain(context.swapchain().vk())
	    , m_pass(std::move(pass))
	    , m_resolution(context.swapchain().get_resolution())
	{
		ensure(m_device, "Failed to initialize renderer: null device");
		ensure(m_graphics_queue, "Failed to initialize renderer: null graphics queue");
		ensure(m_present_queue, "Failed to initialize renderer: null present queue");
		ensure(m_swapchain, "Failed to initialize renderer: null swapchain");

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
			.commandBufferCount = static_cast<uint32_t>(m_cmds.size()),
		};
		vkc(vk_allocate_command_buffers(m_device, &cmd_info, &m_cmds[0]));

		auto semaphore_info = VkSemaphoreCreateInfo {
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		};

		auto fence_info = VkFenceCreateInfo {
			.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
			.flags = VK_FENCE_CREATE_SIGNALED_BIT,
		};

		for (auto idx : std::views::iota(0u, max_frames_in_flight))
		{
			vkc(vk_create_semaphore(
			    m_device,
			    &semaphore_info,
			    nullptr,
			    &m_aquire_image_semaphores[idx]
			));

			vkc(vk_create_fence(m_device, &fence_info, nullptr, &m_in_flight_fences[idx]));

			set_object_name(
			    m_device,
			    m_aquire_image_semaphores[idx].get(),
			    "aquire semaphore {}",
			    idx
			);

			set_object_name(m_device, m_in_flight_fences[idx].get(), "frame fence {}", idx);

			{
				const auto name = std::format("frame fence {}", idx);
				auto debug_info = VkDebugUtilsObjectNameInfoEXT {
					.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
					.objectType = VK_OBJECT_TYPE_FENCE,
					.objectHandle = reinterpret_cast<uint64_t>(
					    static_cast<VkFence_T *>(m_in_flight_fences[idx].get())
					),
					.pObjectName = name.c_str(),
				};
				vk_set_debug_object_name(m_device, &debug_info);
			}
		}

		m_submit_semaphores.resize(context.swapchain().get_image_count());
		for (auto idx = 0; auto &semaphore : m_submit_semaphores)
		{
			vkc(vk_create_semaphore(m_device, &semaphore_info, nullptr, &semaphore));
			set_object_name(m_device, semaphore.get(), "submit semaphore {}", idx++);
		}
	};

	~Renderer()
	{
		if (!m_device)
		{
			return;
		}

		vkc(vk_device_wait_idle(m_device));

		for (auto [semaphore, fence] :
		     std::views::zip(m_aquire_image_semaphores, m_in_flight_fences))
		{
			vk_destroy_semaphore(m_device, semaphore, nullptr);
			vk_destroy_fence(m_device, fence, nullptr);
		}


		for (auto &semaphore : m_submit_semaphores)
		{
			vk_destroy_semaphore(m_device, semaphore, nullptr);
		}

		vk_destroy_command_pool(m_device, m_pool, nullptr);
	}

	Renderer(Renderer &&) = default;

	Renderer(const Renderer &) = delete;

	auto operator=(Renderer &&) -> Renderer & = default;

	auto operator=(const Renderer &) -> Renderer & = delete;

	auto draw(uint32_t frame_idx) -> bool
	{
		ensure(
		    frame_idx < max_frames_in_flight,
		    "Failed to draw: frame_idx >= max_frames_in_flight"
		);

		auto &flight_fence = m_in_flight_fences[frame_idx];
		auto &aquire_semaphore = m_aquire_image_semaphores[frame_idx];
		auto &cmd = m_cmds[frame_idx];

		try
		{
			vkc(vk_wait_for_fences(
			    m_device,
			    1u,
			    &flight_fence,
			    VK_TRUE,
			    std::numeric_limits<uint64_t>::max()
			));

			auto image_idx = uint32_t {};
			auto result = vk_acquire_next_image_khr(
			    m_device,
			    m_swapchain,
			    1000000ul,
			    aquire_semaphore,
			    VK_NULL_HANDLE,
			    &image_idx
			);
			if (result == VK_SUBOPTIMAL_KHR || result == VK_ERROR_OUT_OF_DATE_KHR)
			{
				return false;
			}

			vkc(vk_reset_fences(m_device, 1u, &flight_fence));
			vkc(vk_reset_command_buffer(cmd, {}));
			record_cmd(cmd, image_idx);

			auto wait_stage = VkPipelineStageFlags {
				VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
			};
			auto &submit_semaphore = m_submit_semaphores[image_idx];
			auto submit_info = VkSubmitInfo {
				.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
				.waitSemaphoreCount = 1u,
				.pWaitSemaphores = &aquire_semaphore,
				.pWaitDstStageMask = &wait_stage,
				.commandBufferCount = 1u,
				.pCommandBuffers = &cmd,
				.signalSemaphoreCount = 1u,
				.pSignalSemaphores = &submit_semaphore,
			};

			vkc(vk_queue_submit(m_graphics_queue, 1u, &submit_info, flight_fence));

			VkResult res;
			auto present_info = VkPresentInfoKHR {
				.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
				.waitSemaphoreCount = 1u,
				.pWaitSemaphores = &submit_semaphore,
				.swapchainCount = 1u,
				.pSwapchains = &m_swapchain,
				.pImageIndices = &image_idx,
				.pResults = &res,
			};

			vk_queue_present_khr(m_present_queue, &present_info);
		}
		catch (const std::exception &exp)
		{
			log_dbg("EXCEPTION: {}", exp.what());
		}

		return true;
	}

	void replace_swapchain(const Swapchain &swapchain)
	{
		vk_device_wait_idle(m_device);

		m_swapchain = swapchain.vk();
		m_resolution = swapchain.get_resolution();
		ensure(m_swapchain, "Failed to replace renderer's swapchain: null swapchain");

		for (auto [semaphore, fence] :
		     std::views::zip(m_aquire_image_semaphores, m_in_flight_fences))
		{
			vk_destroy_semaphore(m_device, semaphore, nullptr);
			vk_destroy_fence(m_device, fence, nullptr);
		}

		for (auto &semaphore : m_submit_semaphores)
		{
			vk_destroy_semaphore(m_device, semaphore, nullptr);
		}

		auto semaphore_info = VkSemaphoreCreateInfo {
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		};

		auto fence_info = VkFenceCreateInfo {
			.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
			.flags = VK_FENCE_CREATE_SIGNALED_BIT,
		};

		for (auto idx : std::views::iota(0u, max_frames_in_flight))
		{
			vkc(vk_create_semaphore(
			    m_device,
			    &semaphore_info,
			    nullptr,
			    &m_aquire_image_semaphores[idx]
			));

			vkc(vk_create_fence(m_device, &fence_info, nullptr, &m_in_flight_fences[idx]));

			set_object_name(
			    m_device,
			    m_aquire_image_semaphores[idx].get(),
			    "aquire semaphore {}",
			    idx
			);

			set_object_name(m_device, m_in_flight_fences[idx].get(), "frame fence {}", idx);

			{
				const auto name = std::format("frame fence {}", idx);
				auto debug_info = VkDebugUtilsObjectNameInfoEXT {
					.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
					.objectType = VK_OBJECT_TYPE_FENCE,
					.objectHandle = reinterpret_cast<uint64_t>(
					    static_cast<VkFence_T *>(m_in_flight_fences[idx].get())
					),
					.pObjectName = name.c_str(),
				};
				vk_set_debug_object_name(m_device, &debug_info);
			}
		}

		m_submit_semaphores.resize(swapchain.get_image_count());
		for (auto idx = 0; auto &semaphore : m_submit_semaphores)
		{
			vkc(vk_create_semaphore(m_device, &semaphore_info, nullptr, &semaphore));
			set_object_name(m_device, semaphore.get(), "submit semaphore {}", idx++);
		}
	}

private:
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


	memory::NullOnMove<VkDevice> m_device = VK_NULL_HANDLE;

	memory::NullOnMove<VkCommandPool> m_pool = VK_NULL_HANDLE;

	std::array<memory::NullOnMove<VkCommandBuffer>, max_frames_in_flight> m_cmds {};

	std::array<memory::NullOnMove<VkSemaphore>, max_frames_in_flight> m_aquire_image_semaphores {};

	std::vector<memory::NullOnMove<VkSemaphore>> m_submit_semaphores;

	std::array<memory::NullOnMove<VkFence>, max_frames_in_flight> m_in_flight_fences {};

	memory::NullOnMove<VkSwapchainKHR> m_swapchain = VK_NULL_HANDLE;

	memory::NullOnMove<VkQueue> m_graphics_queue = VK_NULL_HANDLE;

	memory::NullOnMove<VkQueue> m_present_queue = VK_NULL_HANDLE;

	Ref<Pass> m_pass;

	VkExtent2D m_resolution;
};

} // namespace lt::renderer::vk
