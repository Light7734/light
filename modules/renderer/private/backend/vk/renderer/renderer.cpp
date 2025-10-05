#include <memory/reference.hpp>
#include <renderer/backend/vk/context/swapchain.hpp>
#include <renderer/backend/vk/renderer/renderer.hpp>

namespace lt::renderer::vk {

Renderer::Renderer(IContext &context, uint32_t max_frames_in_flight)
    : m_device(static_cast<Device *>(context.device()))
    , m_swapchain(static_cast<Swapchain *>(context.swapchain()))
    , m_resolution(m_swapchain->get_resolution())
    , m_max_frames_in_flight(max_frames_in_flight)
{
	ensure(m_device, "Failed to initialize renderer: null device");
	ensure(m_swapchain, "Failed to initialize renderer: null swapchain");

	// TODO(Light): HARDCODED PASS!!!
	m_pass = memory::create_ref<vk::Pass>(
	    context,
	    assets::ShaderAsset { "./data/test_assets/triangle.vert.asset" },
	    assets::ShaderAsset { "./data/test_assets/triangle.frag.asset" }
	);

	m_pool = m_device->create_command_pool(
	    VkCommandPoolCreateInfo {
	        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
	        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
	        .queueFamilyIndex = m_device->get_family_indices()[0],
	    }
	);

	m_cmds.resize(m_max_frames_in_flight);
	m_cmds = m_device->allocate_command_buffers(
	    VkCommandBufferAllocateInfo {
	        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
	        .commandPool = m_pool,
	        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
	        .commandBufferCount = static_cast<uint32_t>(m_cmds.size()),
	    }
	);

	m_aquire_image_semaphores = m_device->create_semaphores(m_max_frames_in_flight);
	m_frame_fences = m_device->create_fences(
	    VkFenceCreateInfo {
	        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
	        .flags = VK_FENCE_CREATE_SIGNALED_BIT,
	    },
	    m_max_frames_in_flight
	);
	for (auto idx = 0u;
	     auto [semaphore, fence] : std::views::zip(m_aquire_image_semaphores, m_frame_fences))
	{
		m_device->name(semaphore, "acquire image semaphore {}", idx);
		m_device->name(fence, "frame fence {}", idx);
	}

	m_submit_semaphores = m_device->create_semaphores(m_swapchain->get_image_count());
	for (auto idx = 0u; auto &semaphore : m_submit_semaphores)
	{
		m_device->name(semaphore, "submit semaphore {}", idx);
	}
};

Renderer::~Renderer()
{
	if (!m_device)
	{
		return;
	}

	m_device->wait_idle();
	m_device->destroy_semaphores(m_aquire_image_semaphores);
	m_device->destroy_semaphores(m_submit_semaphores);
	m_device->destroy_fences(m_frame_fences);
	m_device->destroy_command_pool(m_pool);
}

[[nodiscard]] auto Renderer::draw(uint32_t frame_idx) -> DrawResult
{
	ensure(
	    frame_idx < m_max_frames_in_flight,
	    "Failed to draw: frame_idx >= max_frames_in_flight ({} >= {})",
	    frame_idx,
	    m_max_frames_in_flight
	);

	auto &frame_fence = m_frame_fences[frame_idx];
	auto &aquire_semaphore = m_aquire_image_semaphores[frame_idx];
	auto &cmd = m_cmds[frame_idx];

	m_device->wait_for_fence(frame_fence);

	auto image_idx = m_device->acquire_image(m_swapchain->vk(), aquire_semaphore);
	if (!image_idx.has_value())
	{
		return {};
	}

	m_device->reset_fence(frame_fence);
	vk_reset_command_buffer(cmd, {});
	record_cmd(cmd, *image_idx);

	auto wait_stage = VkPipelineStageFlags { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	auto &submit_semaphore = m_submit_semaphores[*image_idx];
	m_device->submit(
	    VkSubmitInfo {
	        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
	        .waitSemaphoreCount = 1u,
	        .pWaitSemaphores = &aquire_semaphore,
	        .pWaitDstStageMask = &wait_stage,
	        .commandBufferCount = 1u,
	        .pCommandBuffers = &cmd,
	        .signalSemaphoreCount = 1u,
	        .pSignalSemaphores = &submit_semaphore,
	    },
	    frame_fence
	);

	// TODO(Light): handle result
	auto result = VkResult {};
	m_device->present(
	    VkPresentInfoKHR {
	        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
	        .waitSemaphoreCount = 1u,
	        .pWaitSemaphores = &submit_semaphore,
	        .swapchainCount = 1u,
	        .pSwapchains = m_swapchain->vk_ptr(),
	        .pImageIndices = &image_idx.value(),
	        .pResults = &result,
	    }
	);
	return DrawResult::success;
}

void Renderer::replace_swapchain(ISwapchain *swapchain)
{
	m_device->wait_idle();
	m_swapchain = static_cast<Swapchain *>(swapchain);
	m_resolution = m_swapchain->get_resolution();
}

void Renderer::record_cmd(VkCommandBuffer cmd, uint32_t image_idx)
{
	auto cmd_begin_info = VkCommandBufferBeginInfo {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.flags = {},
		.pInheritanceInfo = nullptr,
	};

	vkc(vk_begin_command_buffer(cmd, &cmd_begin_info));

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

} // namespace lt::renderer::vk
