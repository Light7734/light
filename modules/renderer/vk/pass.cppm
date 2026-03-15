export module renderer.vk.pass;

import preliminary;
import renderer.data;
import renderer.vk.api_wrapper;
import renderer.vk.device;
import renderer.vk.swapchain;
import assets.shader;
import assets.metadata;
import memory.null_on_move;
import renderer.frontend;

export namespace lt::renderer::vkb {

class Pass: public IPass
{
public:
	Pass(
	    class IDevice *device,
	    const lt::assets::ShaderAsset &vertex_shader,
	    const lt::assets::ShaderAsset &fragment_shader
	);

	[[nodiscard]] auto get_pipeline() -> vk::Pipeline &
	{
		return m_pipeline;
	}

	[[nodiscard]] auto get_pipeline_layout() -> vk::PipelineLayout &
	{
		return m_layout;
	}

	[[nodiscard]] auto get_descriptor_set_layout() -> vk::DescriptorSetLayout &
	{
		return m_descriptor_set_layout;
	}

private:
	Device *m_device {};

	vk::DescriptorSetLayout m_descriptor_set_layout;

	vk::DescriptorPool m_descriptor_pool;

	vk::DescriptorSet m_vertices_descriptor_set;

	vk::PipelineLayout m_layout;

	vk::Pipeline m_pipeline;
};

} // namespace lt::renderer::vkb

/** @todo(Light): unimplemented in gcc -- is it even right to use a private fragment? */
// module :private;
namespace lt::renderer::vkb {

using enum vk::DescriptorSetLayout::Binding::FlagBits;

Pass::Pass(
    IDevice *device,
    const lt::assets::ShaderAsset &vertex_shader,
    const lt::assets::ShaderAsset &fragment_shader
)
    : m_device(dynamic_cast<Device *>(device))
      , m_descriptor_set_layout(m_device->vk(),{
        .flags = vk::DescriptorSetLayout::CreateInfo::FlagBits::update_after_bind_pool,
        .bindings = { 
        {
            .flags = partially_bound | update_after_bind | update_unused_while_pending,
            .idx = 0u,
            .count = 1'000u,
            .type = vk::DescriptorSet::Type::storage_buffer,
            .shader_stages = vk::ShaderStageFlags::vertex_bit,
        },
    }}),
	m_layout(vk::PipelineLayout(m_device->vk(),{
        .descriptor_set_layouts = { &m_descriptor_set_layout },
        .push_constant_ranges = { {  vk::ShaderStageFlags::vertex_bit,  0u,  sizeof(FrameConstants) } }
    }))
{
	auto shaders = std::vector<std::pair<vk::ShaderModule, vk::ShaderStageFlags::T>> {};
	shaders.emplace_back(
	    vk::ShaderModule(
	        m_device->vk(),
	        vk::ShaderModule::CreateInfo {
	            .code = vertex_shader.unpack(lt::assets::ShaderAsset::BlobTag::code),
	        }
	    ),
	    vk::ShaderStageFlags::vertex_bit
	);
	shaders.emplace_back(
	    vk::ShaderModule(
	        m_device->vk(),
	        vk::ShaderModule::CreateInfo {
	            .code = fragment_shader.unpack(lt::assets::ShaderAsset::BlobTag::code),
	        }
	    ),
	    vk::ShaderStageFlags::fragment_bit
	);

	m_pipeline = vk::Pipeline(
	    m_device->vk(),
	    m_layout,
	    vk::Pipeline::CreateInfo {
	        .shaders = std::move(shaders),
	        .input_assembly_state = {
                .topology = vk::PrimitiveTopology::triangle_strip,
                .primitive_restart_enabled = true,
            },
	        .viewport_state = {
                .viewport_count = 1u,
                .scissor_count = 1u,
            },
	        .rasterization_state = vk::Pipeline::RasterizationState {},
	        .multisampling_state = vk::Pipeline::MultisamplingState {},
            .attachment_state = vk::
	            Pipeline::AttachmentState {},

        .debug_name = "abcdefgh"
	    }
	);
}

} // namespace lt::renderer::vkb
