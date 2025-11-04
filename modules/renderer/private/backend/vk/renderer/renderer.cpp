#include <memory/reference.hpp>
#include <renderer/backend/vk/context/swapchain.hpp>
#include <renderer/backend/vk/renderer/renderer.hpp>

namespace lt::renderer::vk {

Renderer::Renderer(IGpu *gpu, IDevice *device, ISwapchain *swapchain, uint32_t max_frames_in_flight)
    : m_device(static_cast<Device *>(device))
    , m_swapchain(static_cast<Swapchain *>(swapchain))
    , m_resolution(m_swapchain->get_resolution())
    , m_max_frames_in_flight(max_frames_in_flight)
    , m_staging_offset()
    , m_vertex_buffer(
          device,
          gpu,
          IBuffer::CreateInfo {
              .usage = IBuffer::Usage::vertex,
              .size = 1'000'000,
              .debug_name = "vertex buffer",
          }
      )
    , m_staging_buffer(
          device,
          gpu,
          IBuffer::CreateInfo {
              .usage = IBuffer::Usage::staging,
              .size = 1'000'000,
              .debug_name = "staging buffer",
          }
      )
{
	ensure(m_device, "Failed to initialize renderer: null device");
	ensure(m_swapchain, "Failed to initialize renderer: null swapchain");

	// TODO(Light): HARDCODED PASS!!!
	m_pass = memory::create_ref<vk::Pass>(
	    m_device,
	    m_swapchain,
	    assets::ShaderAsset { "./data/test_assets/sprite.vert.asset" },
	    assets::ShaderAsset { "./data/test_assets/triangle.frag.asset" }
	);

	m_pool = m_device->create_command_pool(
	    VkCommandPoolCreateInfo {
	        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
	        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
	        .queueFamilyIndex = m_device->get_family_indices()[0],
	    }
	);


	m_transient_pool = m_device->create_command_pool(
	    VkCommandPoolCreateInfo {
	        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
	        .flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT,
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
	m_device->destroy_command_pool(m_transient_pool);
}

[[nodiscard]] auto Renderer::frame(uint32_t frame_idx, std::function<void()> submit_scene) -> Result
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
		return Result::invalid_swapchain;
	}

	m_device->reset_fence(frame_fence);

	map_buffers(frame_idx);
	submit_scene();
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

	return Result::success;
}

void Renderer::replace_swapchain(ISwapchain *swapchain)
{
	m_device->wait_idle();
	m_swapchain = static_cast<Swapchain *>(swapchain);
	m_resolution = m_swapchain->get_resolution();
	m_pass->replace_swapchain(*swapchain);
}

void Renderer::map_buffers(uint32_t frame_idx)
{
	using components::Sprite;

	m_current_sprite_idx = 0;
	m_staging_map = m_staging_buffer.map();
	auto frame_segment_size = m_staging_map.size() / m_max_frames_in_flight;

	m_staging_offset = frame_segment_size * frame_idx;
	m_staging_map = m_staging_map.subspan(m_staging_offset, frame_segment_size);

	m_sprite_vertex_map = std::span<Sprite::Vertex>(
	    std::bit_cast<Sprite::Vertex *>(m_staging_map.data()),
	    m_staging_map.size() / sizeof(Sprite::Vertex)
	);
}

void Renderer::flush_buffers(VkCommandBuffer cmd)
{
	m_staging_map = {};
	m_sprite_vertex_map = {};

	m_staging_buffer.unmap();
	const auto buffer_copy_info = VkBufferCopy {

		.srcOffset = m_staging_offset,
		.dstOffset = m_staging_offset,
		.size = m_current_sprite_idx * sizeof(components::Sprite::Vertex),
	};

	vk_cmd_copy_buffer(cmd, m_staging_buffer.vk(), m_vertex_buffer.vk(), 1u, &buffer_copy_info);
}

void Renderer::record_cmd(VkCommandBuffer cmd, uint32_t image_idx)
{
	const auto cmd_begin_info = VkCommandBufferBeginInfo {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.flags = {},
		.pInheritanceInfo = nullptr,
	};

	const auto begin_frame_barrier = VkImageMemoryBarrier {
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.srcAccessMask = {},
		.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        .image = m_swapchain->get_image(image_idx),
        .subresourceRange = VkImageSubresourceRange{
            .aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
            .baseMipLevel   = 0u,
            .levelCount     = VK_REMAINING_MIP_LEVELS,
            .baseArrayLayer = 0u,
            .layerCount     = VK_REMAINING_ARRAY_LAYERS,
        },

	};

	const auto end_frame_barrier = VkImageMemoryBarrier {
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		.dstAccessMask = {},
		.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
        .image = m_swapchain->get_image(image_idx),

        .subresourceRange = VkImageSubresourceRange{
            .aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
            .baseMipLevel   = 0u,
            .levelCount     = VK_REMAINING_MIP_LEVELS,
            .baseArrayLayer = 0u,
            .layerCount     = VK_REMAINING_ARRAY_LAYERS,
        },
	};

	const auto scissor = VkRect2D {
		.offset = { .x = 0u, .y = 0u },
		.extent = m_resolution,
	};

	const auto viewport = VkViewport {
		.x = 0.0f,
		.y = 0.0f,
		.width = static_cast<float>(m_resolution.width),
		.height = static_cast<float>(m_resolution.height),
		.minDepth = 0.0f,
		.maxDepth = 1.0f,
	};

	const auto color_attachment_info = VkRenderingAttachmentInfoKHR {
		.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
		.imageView = m_swapchain->get_image_view(image_idx),
		.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		.resolveMode = VK_RESOLVE_MODE_NONE,
		.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
		.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
		.clearValue = VkClearValue { .color = { 0.93, 0.93, 0.93, 1.0 } },
	};

	const auto rendering_info = VkRenderingInfoKHR {
		.sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR,
		.renderArea = scissor,
		.layerCount = 1,
		.colorAttachmentCount = 1,
		.pColorAttachments = &color_attachment_info,

	};

	vk_reset_command_buffer(cmd, {});
	vkc(vk_begin_command_buffer(cmd, &cmd_begin_info));
	flush_buffers(cmd);

	vk_cmd_push_constants(
	    cmd,
	    m_pass->get_layout(),
	    VK_SHADER_STAGE_VERTEX_BIT,
	    0u,
	    sizeof(FrameConstants),
	    &m_frame_constants
	);
	vk_cmd_pipeline_barrier(
	    cmd,
	    VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
	    VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
	    0,
	    0,
	    nullptr,
	    0,
	    nullptr,
	    1,
	    &begin_frame_barrier
	);
	vk_cmd_begin_rendering(cmd, &rendering_info);
	vk_cmd_bind_pipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pass->get_pipeline());
	vk_cmd_set_viewport(cmd, 0, 1, &viewport);
	vk_cmd_set_scissors(cmd, 0, 1, &scissor);
	vk_cmd_draw(cmd, m_current_sprite_idx, 1, 0, 0);
	vk_cmd_end_rendering(cmd);
	vk_cmd_pipeline_barrier(
	    cmd,
	    VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
	    VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
	    0,
	    0,
	    nullptr,
	    0,
	    nullptr,
	    1,
	    &end_frame_barrier
	);
	vkc(vk_end_command_buffer(cmd));
}

void Renderer::submit_sprite(
    const components::Sprite &sprite,
    const math::components::Transform &transform
)
{
	using components::Sprite;

	const auto &[x, y, z] = transform.translation;
	const auto &[width, height, _] = transform.scale;

	m_sprite_vertex_map[m_current_sprite_idx++] = components::Sprite::Vertex {
		.position = { x, y + height, z },
		.color = sprite.color,
	};

	m_sprite_vertex_map[m_current_sprite_idx++] = components::Sprite::Vertex {
		.position = { x + width, y + height, z },
		.color = sprite.color,
	};

	m_sprite_vertex_map[m_current_sprite_idx++] = components::Sprite::Vertex {
		.position = { x + width, y, z },
		.color = sprite.color,
	};

	m_sprite_vertex_map[m_current_sprite_idx++] = components::Sprite::Vertex {
		.position = { x + width, y, z },
		.color = sprite.color,
	};

	m_sprite_vertex_map[m_current_sprite_idx++] = components::Sprite::Vertex {
		.position = { x, y, z },
		.color = sprite.color,
	};

	m_sprite_vertex_map[m_current_sprite_idx++] = components::Sprite::Vertex {
		.position = { x, y + height, z },
		.color = sprite.color,
	};
}

} // namespace lt::renderer::vk
