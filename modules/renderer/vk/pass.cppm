export module renderer.vk.pass;
import renderer.data;
import renderer.vk.api_wrapper;
import renderer.vk.device;
import renderer.vk.swapchain;
import assets.shader;
import assets.metadata;
import memory.null_on_move;
import renderer.frontend;
import std;

namespace lt::renderer::vkb {

export class Pass: public IPass
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

	[[nodiscard]] auto get_layout() -> vk::PipelineLayout &
	{
		return m_layout;
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


module :private;
using namespace ::lt::renderer::vkb;
using namespace ::lt::renderer;

Pass::Pass(
    IDevice *device,
    const lt::assets::ShaderAsset &vertex_shader,
    const lt::assets::ShaderAsset &fragment_shader
)
    : m_device(static_cast<Device *>(device))

{
	using enum vk::DescriptorSetLayout::Binding::FlagBits;
	auto bindings = std::vector<vk::DescriptorSetLayout::Binding> {
		{
		    .flags = variable_descriptor_count | partially_bound | update_after_bind
		             | update_unused_while_pending,
		    .idx = 0u,
		    .count = 1'000u,
		    .type = vk::DescriptorSet::Type::storage_buffer,
		    .shader_stages = vk::ShaderStageFlags::vertex_bit,
		},
	};

	using enum vk::DescriptorSetLayout::CreateInfo::FlagBits;
	m_descriptor_set_layout = vk::DescriptorSetLayout(
	    m_device->vk(),
	    vk::DescriptorSetLayout::CreateInfo {
	        .flags = update_after_bind_pool,
	        .bindings = { 
                vk::DescriptorSetLayout::Binding {
                    .flags = variable_descriptor_count | partially_bound | update_after_bind | update_unused_while_pending,
                    .idx = 0u,
                    .count = 1'000u,
                    .type = vk::DescriptorSet::Type::storage_buffer,
                    .shader_stages = vk::ShaderStageFlags::vertex_bit,
                },
            },
	    }
	);

	auto push_constant_ranges = std::vector<vk::PipelineLayout::PushConstantRange> {
		{
		    .shader_stages = vk::ShaderStageFlags::vertex_bit,
		    .offset = 0u,
		    .size = sizeof(FrameConstants),
		},
	};
	m_layout = vk::PipelineLayout(
	    m_device->vk(),
	    vk::PipelineLayout::CreateInfo {
            .descriptor_set_layouts = {
                &m_descriptor_set_layout,
            },
            .push_constant_ranges = push_constant_ranges,
	    }
	);

	// auto pool_size = VkDescriptorPoolSize {
	// 	.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
	// 	.descriptorCount = descriptor_count,
	// };
	//
	// m_descriptor_pool = m_device->create_desscriptor_pool(
	//     {
	//         .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
	//         .poolSizeCount = 1u,
	//         .pPoolSizes = &pool_size,
	//     }
	// );
	//
	// auto descriptor_set_variable_descriptor_count_info
	//     = VkDescriptorSetVariableDescriptorCountAllocateInfo {
	// 	      .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO,
	// 	      .descriptorSetCount = 1u,
	// 	      .pDescriptorCounts = &descriptor_count,
	//       };
	//
	// m_vertices_descriptor_set = m_device->allocate_descriptor_set(
	//     VkDescriptorSetAllocateInfo {
	//         .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
	//         .pNext = &descriptor_set_variable_descriptor_count_info,
	//         .descriptorPool = m_descriptor_pool,
	//         .descriptorSetCount = 1u,
	//         .pSetLayouts = &m_vertices_descriptor_set_layout,
	//     }
	// );


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
                .topology = vk::PrimitiveTopology::triangle_list,
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
