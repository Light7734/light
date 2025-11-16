export module renderer.vk.renderer;
import assets.shader;
import debug.assertions;
import renderer.vk.api_wrapper;
import memory.reference;
import memory.null_on_move;
import renderer.vk.device;
import math.vec2;
import math.components;
import renderer.vk.swapchain;
import renderer.components;
import renderer.vk.buffer;
import renderer.vk.pass;
import renderer.data;
import renderer.frontend;
import std;

namespace lt::renderer::vkb {

export class Renderer: public IRenderer
{
public:
	Renderer(
	    class IGpu *gpu,
	    class IDevice *device,
	    class ISwapchain *swapchain,
	    std::uint32_t max_frames_in_flight
	);

	[[nodiscard]] auto frame(std::uint32_t frame_idx, std::function<void()> submit_scene)
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
	void record_cmd(vk::CommandBuffer &cmd, std::uint32_t image_idx);

	void map_buffers(std::uint32_t frame_idx);

	std::uint32_t m_max_frames_in_flight {};

	Device *m_device {};

	Swapchain *m_swapchain {};

	memory::Ref<Pass> m_pass;

	vk::CommandPool m_pool;

	std::vector<vk::CommandBuffer> m_cmds;

	std::vector<vk::Fence> m_frame_fences;

	std::vector<vk::Semaphore> m_acquire_image_semaphores;

	std::vector<vk::Semaphore> m_submit_semaphores;

	math::uvec2 m_resolution;

	FrameConstants m_frame_constants;

	Buffer m_vertex_buffer;

	Buffer m_staging_buffer;

	std::size_t m_staging_offset;

	std::span<std::byte> m_staging_map;

	std::span<components::Sprite::Vertex> m_sprite_vertex_map;

	std::size_t m_current_sprite_idx;
};

} // namespace lt::renderer::vkb

module :private;
namespace lt::renderer::vkb {

Renderer::Renderer(
    IGpu *gpu,
    IDevice *device,
    ISwapchain *swapchain,
    std::uint32_t max_frames_in_flight
)
    : m_device(static_cast<Device *>(device))
    , m_swapchain(static_cast<Swapchain *>(swapchain))
    , m_resolution(m_swapchain->get_resolution())
    , m_max_frames_in_flight(max_frames_in_flight)
    , m_staging_offset()
    , m_vertex_buffer(
          device,
          gpu,
          {
              .usage = IBuffer::Usage::vertex,
              .size = 1'000'000,
              .debug_name = "vertex buffer",
          }
      )
    , m_staging_buffer(
          device,
          gpu,
          {
              .usage = IBuffer::Usage::staging,
              .size = 1'000'000,
              .debug_name = "staging buffer",
          }
      )
    , m_pass(memory::create_ref<Pass>(
          m_device,
          assets::ShaderAsset { "./data/test_assets/sprite.vert.asset" },
          assets::ShaderAsset { "./data/test_assets/triangle.frag.asset" }
      ))
    , m_pool(
          m_device->vk(),
          {
              .flags = vk::CommandPool::CreateInfo::FlagBits::reset_command_buffer,
          }
      )
    , m_cmds(m_pool.allocate(m_max_frames_in_flight, vk::CommandPool::BufferLevel::primary))
    , m_acquire_image_semaphores(m_max_frames_in_flight)
    , m_frame_fences(m_max_frames_in_flight)
    , m_submit_semaphores(m_swapchain->get_image_count())
{
	for (auto [semaphore, fence] : std::views::zip(m_acquire_image_semaphores, m_frame_fences))
	{
		semaphore = vk::Semaphore(m_device->vk());
		fence = vk::Fence(m_device->vk(), { .signaled = true });
	}

	for (auto &semaphore : m_submit_semaphores)
	{
		semaphore = vk::Semaphore(m_device->vk());
	}
};

[[nodiscard]] auto Renderer::frame(std::uint32_t frame_idx, std::function<void()> submit_scene)
    -> Result
{
	debug::ensure(
	    frame_idx < m_max_frames_in_flight,
	    "Failed to draw: frame_idx >= max_frames_in_flight ({} >= {})",
	    frame_idx,
	    m_max_frames_in_flight
	);

	auto &frame_fence = m_frame_fences[frame_idx];
	auto &acquire_semaphore = m_acquire_image_semaphores[frame_idx];
	auto &cmd = m_cmds[frame_idx];

	frame_fence.wait();
	const auto image_idx = m_swapchain->vk().acquire_image(acquire_semaphore);
	frame_fence.reset();

	map_buffers(frame_idx);
	submit_scene();
	record_cmd(cmd, image_idx);

	auto &submit_semaphore = m_submit_semaphores[image_idx];
	m_device->graphics_queue().submit(vk::Queue::SubmitInfo {
	    .command_buffer = &cmd,
	    .wait_stages = vk::PipelineStageFlags::color_attachment_output_bit,
	    .wait_semaphore = &acquire_semaphore,
	    .signal_semaphore = &submit_semaphore,
	    .signal_fence = &frame_fence,
	});

	m_device->present_queue().present(vk::Queue::PresentInfo {
	    .wait_semaphore = &submit_semaphore,
	    .swapchain = &m_swapchain->vk(),
	    .image_idx = image_idx,
	});

	return Result::success;
}

void Renderer::replace_swapchain(ISwapchain *swapchain)
{
	m_device->vk().wait_idle();
	m_swapchain = static_cast<Swapchain *>(swapchain);
	m_resolution = m_swapchain->get_resolution();
}

void Renderer::map_buffers(std::uint32_t frame_idx)
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

void Renderer::record_cmd(vk::CommandBuffer &cmd, std::uint32_t image_idx)
{
	// const auto cmd_begin_info = VkCommandBufferBeginInfo {
	// 	.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
	// 	.flags = {},
	// 	.pInheritanceInfo = nullptr,
	// };

	// vk_reset_command_buffer(cmd, {});
	// vkc(vk_begin_command_buffer(cmd, &cmd_begin_info));
	// const auto begin_frame_barrier = VkImageMemoryBarrier {
	// 	.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
	// 	.srcAccessMask = {},
	// 	.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
	// 	.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
	// 	.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
	//        .image = m_swapchain->get_image(image_idx),
	//        .range = vk::Image::full_color_range,
	//        .subresourceRange = VkImageSubresourceRange{
	//            .aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
	//            .baseMipLevel   = 0u,
	//            .levelCount     = VK_REMAINING_MIP_LEVELS,
	//            .baseArrayLayer = 0u,
	//            .layerCount     = VK_REMAINING_ARRAY_LAYERS,
	//        },
	// };
	//
	//
	// vk_cmd_pipeline_barrier(
	//     cmd,
	//     VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
	//     VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
	//     0,
	//     0,
	//     nullptr,
	//     0,
	//     nullptr,
	//     1,
	//     &begin_frame_barrier
	// );
	//
	// const auto end_frame_barrier = VkImageMemoryBarrier {
	// 	.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
	// 	.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
	// VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT, 	.dstAccessMask = {}, 	.oldLayout =
	// VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, 	.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
	//        .image = m_swapchain->get_image(image_idx),
	//
	//        .subresourceRange = VkImageSubresourceRange{
	//            .aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
	//            .baseMipLevel   = 0u,
	//            .levelCount     = VK_REMAINING_MIP_LEVELS,
	//            .baseArrayLayer = 0u,
	//            .layerCount     = VK_REMAINING_ARRAY_LAYERS,
	//        },
	// };
	// vk_cmd_pipeline_barrier(
	//     cmd,
	//     VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
	//     VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
	//     0,
	//     0,
	//     nullptr,
	//     0,
	//     nullptr,
	//     1,
	//     &end_frame_barrier
	// );

	// const auto scissor = VkRect2D {
	// 	.offset = { .x = 0u, .y = 0u },
	// 	.extent = m_resolution,
	// };
	// const auto viewport = VkViewport {
	// 	.x = 0.0f,
	// 	.y = 0.0f,
	// 	.width = static_cast<float>(m_resolution.width),
	// 	.height = static_cast<float>(m_resolution.height),
	// 	.minDepth = 0.0f,
	// 	.maxDepth = 1.0f,
	// };

	// const auto color_attachment_info = VkRenderingAttachmentInfoKHR {
	// 	.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
	// 	.imageView = m_swapchain->get_image_view(image_idx),
	// 	.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
	// 	.resolveMode = VK_RESOLVE_MODE_NONE,
	// 	.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
	// 	.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
	// 	.clearValue = VkClearValue { .color = { 0.93, 0.93, 0.93, 1.0 } },
	// };

	// const auto rendering_info = VkRenderingInfoKHR {
	// 	.sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR,
	// 	.renderArea = scissor,
	// 	.layerCount = 1,
	// 	.colorAttachmentCount = 1,
	// 	.pColorAttachments = &color_attachment_info,
	//
	// };

	m_staging_map = {};
	m_sprite_vertex_map = {};
	cmd.begin({});

	m_staging_buffer.unmap();
	cmd.copy({
	    .src_buffer = &m_staging_buffer.vk(),
	    .dst_buffer = &m_vertex_buffer.vk(),
	    .src_offset = m_staging_offset,
	    .dst_offset = m_staging_offset,
	    .size = m_current_sprite_idx * sizeof(components::Sprite::Vertex),
	});
	cmd.push_constants({
	    .layout = &m_pass->get_layout(),
	    .shader_stages = vk::ShaderStageFlags::vertex_bit,
	    .offset = 0u,
	    .size = sizeof(FrameConstants),
	    .data = &m_frame_constants,
	});

	using AccessFlagBits = vk::CommandBuffer::ImageBarrierInfo::AccessFlagBits;
	cmd.image_barrier({
	    .image = &m_swapchain->get_image(image_idx),
	    .range = vk::Image::full_color_range,
	    .src_stages = vk::PipelineStageFlags::color_attachment_output_bit,
	    .dst_stages = vk::PipelineStageFlags::color_attachment_output_bit,
	    .src_accesses = AccessFlagBits::none,
	    .dst_accesses = AccessFlagBits::color_attachment_write,
	    .src_layout = vk::Image::Layout::undefined,
	    .dst_layout = vk::Image::Layout::color_attachment_optimal,
	});

	using Attachment = vk::CommandBuffer::RenderingInfo::AttachmentInfo;
	cmd.begin_rendering(
	    {
        .area_offset = {0u, 0u,},
        .area_extent = m_resolution,
        .color_attachments = std::vector<Attachment> {
        Attachment{
            .view= &m_swapchain->get_image_view(image_idx),
            .layout = vk::Image::Layout::color_attachment_optimal,
            .load_operation = Attachment::LoadOperation::load,
            .store_operation = Attachment::StoreOperation::store,
            .color_clear_values = {.5f, .5f, .5f, 1.f}
        }
        }
	    }
	);
	cmd.bind_pipeline(m_pass->get_pipeline(), vk::Pipeline::BindPoint::graphics);
	//    cmd.set_viewport();
	//    cmd.set_scissors();
	cmd.draw({
	    .vertex_count = static_cast<std::uint32_t>(m_current_sprite_idx),
	    .instance_count = 1u,
	    .first_vertex = 0u,
	    .first_instance = 0u,
	});

	cmd.end_rendering();
	cmd.image_barrier({
	    .image = &m_swapchain->get_image(image_idx),
	    .src_stages = vk::PipelineStageFlags::color_attachment_output_bit,
	    .dst_stages = vk::PipelineStageFlags::bottom_of_pipe_bit,
	    .src_accesses = AccessFlagBits::color_attachment_read
	                    | AccessFlagBits::color_attachment_write,
	    .dst_accesses = {},
	    .src_layout = vk::Image::Layout::color_attachment_optimal,
	    .dst_layout = vk::Image::Layout::present_src,

	});
	cmd.end();
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

} // namespace lt::renderer::vkb
