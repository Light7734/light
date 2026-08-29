export module renderer.vk.renderer;

import preliminary;
import time;
import math.mat4;
import logger;
import assets.shader;
import renderer.vk.api_wrapper;
import renderer.vk.device;
import math.vec2;
import math.components;
import renderer.vk.swapchain;
import renderer.components;
import renderer.vk.buffer;
import renderer.vk.pass;
import renderer.data;
import renderer.vk.gpu;

export namespace lt::renderer::vkb {

class Renderer
{
public:
	enum class Result : u8
	{
		success = 0,
		invalid_swapchain,
		error,
	};

	static constexpr auto frames_in_flight_upper_limit = 5u;

	static constexpr auto frames_in_flight_lower_limit = 1u;

	Renderer(
	    not_null<Gpu *> gpu,
	    not_null<Device *> device,
	    not_null<Swapchain *> swapchain,
	    u32 max_frames_in_flight
	);

	Renderer(Renderer &&) = default;

	Renderer(const Renderer &) = delete;

	auto operator=(Renderer &&) -> Renderer & = default;

	auto operator=(const Renderer &) -> Renderer & = delete;

	~Renderer();

	[[nodiscard]] auto frame(u32 frame_idx, const std::function<void()> &submit_scene) -> Result;

	void replace_swapchain(Swapchain *swapchain);

	void set_frame_constants(FrameConstants constants);

	void submit_sprite(
	    const components::Sprite &sprite,
	    const math::components::Transform &transform
	);

private:
	void record_cmd(vk::CommandBuffer &cmd, u32 image_idx);

	void map_buffers(u32 frame_idx);

	u32 m_max_frames_in_flight {};

	Device *m_device {};

	Swapchain *m_swapchain {};

	ref<Pass> m_pass {};

	vk::CommandPool m_pool {};

	std::vector<vk::CommandBuffer> m_cmds {};

	std::vector<vk::Fence> m_frame_fences {};

	std::vector<vk::Semaphore> m_acquire_image_semaphores {};

	std::vector<vk::Semaphore> m_submit_semaphores {};

	math::vec2_u32 m_resolution {};

	FrameConstants m_frame_constants {};

	Buffer m_vertex_buffer;

	Buffer m_staging_buffer;

	size_t m_staging_offset {};

	std::span<byte> m_staging_map {};

	std::span<components::Sprite::Vertex> m_sprite_vertex_map {};

	size_t m_current_sprite_idx {};

	vk::DescriptorPool m_global_set_pool {};

	vk::DescriptorSet m_global_set {};
};

} // namespace lt::renderer::vkb

namespace lt::renderer::vkb {

Renderer::Renderer(
    not_null<Gpu *> gpu,
    not_null<Device *> device,
    not_null<Swapchain *> swapchain,
    u32 max_frames_in_flight
)
    : m_device(device)
    , m_swapchain(swapchain)
    , m_resolution(m_swapchain->get_resolution())
    , m_max_frames_in_flight(max_frames_in_flight)
    , m_vertex_buffer(
          device,
          gpu,
          {
              .usage = Buffer::Usage::storage,
              .size = 1'000'000,
              .debug_name = "vertex buffer",
          }
      )
    , m_staging_buffer(
          device,
          gpu,
          {
              .usage = Buffer::Usage::staging,
              .size = 1'000'000,
              .debug_name = "staging buffer",
          }
      )
    , m_pass(
          create_ref<Pass>(
              not_null<Device *>(m_device),
              assets::ShaderAsset { "./data/test_assets/sprite.vert.asset" },
              assets::ShaderAsset { "./data/test_assets/triangle.frag.asset" }
          )
      )
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
    , m_global_set_pool(
          m_device->vk(),
          vk::DescriptorPool::CreateInfo {
              .sizes = { { .type = vk::DescriptorSet::Type::storage_buffer, .count = 1'000 } },
              .max_sets = 1'000,
              .name = "global pool",
          }
      )

    , m_global_set(m_global_set_pool.allocate(m_pass->get_descriptor_set_layout()))
{
	ensure(
	    (m_max_frames_in_flight >= frames_in_flight_lower_limit)
	        && (m_max_frames_in_flight <= frames_in_flight_upper_limit),
	    "Recieved max_frames_in_flight ({}) out of bound range: {} to {}",
	    m_max_frames_in_flight,
	    frames_in_flight_lower_limit,
	    frames_in_flight_upper_limit
	);

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

Renderer::~Renderer()
{
	try
	{
		m_device->vk().wait_idle();
	}
	catch (const std::exception &exp)
	{
		log::error("Failed to wait idle on device in renderer destructor:");
		log::error("\twhat: {}", exp.what());
	}
}


[[nodiscard]] auto Renderer::frame(u32 frame_idx, const std::function<void()> &submit_scene)
    -> Result
{
	ensure(
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

	// @WIP(Light): submit the scene!
	ignore = submit_scene;
	// submit_scene();
	record_cmd(cmd, image_idx);

	auto &submit_semaphore = m_submit_semaphores[image_idx];
	m_device->graphics_queue().submit(
	    vk::Queue::SubmitInfo {
	        .command_buffer = &cmd,
	        .wait_stages = vk::PipelineStageFlags::color_attachment_output_bit,
	        .wait_semaphore = &acquire_semaphore,
	        .signal_semaphore = &submit_semaphore,
	        .signal_fence = &frame_fence,
	    }
	);

	m_device->present_queue().present(
	    vk::Queue::PresentInfo {
	        .wait_semaphore = &submit_semaphore,
	        .swapchain = &m_swapchain->vk(),
	        .image_idx = image_idx,
	    }
	);

	return Result::success;
}

void Renderer::replace_swapchain(Swapchain *swapchain)
{
	m_device->vk().wait_idle();
	m_swapchain = swapchain;
	m_resolution = m_swapchain->get_resolution();
}

void Renderer::set_frame_constants(FrameConstants constants)
{
	m_frame_constants = constants;
}

void Renderer::map_buffers(u32 frame_idx)
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

void Renderer::record_cmd(vk::CommandBuffer &cmd, u32 image_idx)
{
	m_staging_map = {};
	m_sprite_vertex_map = {};
	cmd.begin({});

	m_staging_buffer.unmap();

	// if (m_current_sprite_idx)
	// {
	// 	cmd.copy(
	// 	    {
	// 	        .src_buffer = &m_staging_buffer.vk(),
	// 	        .dst_buffer = &m_vertex_buffer.vk(),
	// 	        .src_offset = m_staging_offset,
	// 	        .dst_offset = m_staging_offset,
	// 	        .size = m_current_sprite_idx * sizeof(components::Sprite::Vertex),
	// 	    }
	// 	);
	// }

	// cmd.push_constants(
	//     {
	//         .layout = &m_pass->get_pipeline_layout(),
	//         .shader_stages = vk::ShaderStageFlags::vertex_bit,
	//         .offset = 0u,
	//         .size = sizeof(FrameConstants),
	//         .data = &m_frame_constants,
	//     }
	// );
	//
	// cmd.bind_descriptor_set(
	//     m_global_set,
	//     vk::Pipeline::BindPoint::graphics,
	//     m_pass->get_pipeline_layout(),
	//     0
	// );

	using AccessFlagBits = vk::CommandBuffer::ImageBarrierInfo::AccessFlagBits;
	cmd.image_barrier(
	    {
	        .image = &m_swapchain->get_image(image_idx),
	        .range = vk::Image::full_color_range,
	        .src_stages = vk::PipelineStageFlags::color_attachment_output_bit,
	        .dst_stages = vk::PipelineStageFlags::color_attachment_output_bit,
	        .src_accesses = AccessFlagBits::none,
	        .dst_accesses = AccessFlagBits::color_attachment_write,
	        .src_layout = vk::Image::Layout::undefined,
	        .dst_layout = vk::Image::Layout::color_attachment_optimal,
	    }
	);

	static const lt::time::Timer timer;

	using Attachment = vk::CommandBuffer::RenderingInfo::AttachmentInfo;
	cmd.begin_rendering({
        .area_offset = {0u, 0u,},
        .area_extent = m_resolution,
        .color_attachments = std::vector<Attachment> {
            Attachment{
                .view= &m_swapchain->get_image_view(image_idx),
                .layout = vk::Image::Layout::color_attachment_optimal,
                .load_operation = Attachment::LoadOperation::clear,
                .store_operation = Attachment::StoreOperation::store,
                .color_clear_values = {
                    static_cast<float>(std::sin(timer.elapsed_time().count())),
                    static_cast<float>(std::cos(timer.elapsed_time().count() * 2.0)),
                    static_cast<float>(std::sin(timer.elapsed_time().count() / 2.0)),
                    1.f
                }
            }
        }
    });
	// cmd.bind_pipeline(m_pass->get_pipeline(), vk::Pipeline::BindPoint::graphics);
	// cmd.set_viewport(
	//     {
	//         .origin = {},
	//         .extent = { static_cast<f32>(m_resolution.x), static_cast<f32>(m_resolution.y) },
	//         .min_depth = 0.0f,
	//         .max_depth = 1.0f,
	//     }
	// );
	// cmd.set_scissor({ .offset = {}, .extent = m_resolution });
	// cmd.draw(
	//     {
	//         .vertex_count = static_cast<u32>(m_current_sprite_idx),
	//         .instance_count = 1u,
	//         .first_vertex = 0u,
	//         .first_instance = 0u,
	//     }
	// );
	//
	cmd.end_rendering();
	cmd.image_barrier(
	    {
	        .image = &m_swapchain->get_image(image_idx),
	        .range = vk::Image::full_color_range,
	        .src_stages = vk::PipelineStageFlags::color_attachment_output_bit,
	        .dst_stages = vk::PipelineStageFlags::bottom_of_pipe_bit,
	        .src_accesses = AccessFlagBits::color_attachment_read
	                        | AccessFlagBits::color_attachment_write,
	        .dst_accesses = {},
	        .src_layout = vk::Image::Layout::color_attachment_optimal,
	        .dst_layout = vk::Image::Layout::present_src,

	    }
	);
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
