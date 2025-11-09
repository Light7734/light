export module renderer.vk.pass;

import renderer.backend.vk.library_wrapper;
import renderer.backend.vk.device;
import renderer.backend.vk.swapchain;
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

	vk::PipelineLayout m_layout;

	vk::Pipeline m_pipeline;

	vk::DescriptorPool m_descriptor_pool;

	vk::DescriptorSetLayout m_vertices_descriptor_set_layout;

	vk::DescriptorSet m_vertices_descriptor_set;
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
	// auto binding = VkDescriptorSetLayoutBinding {
	// 	.binding = 0,
	// 	.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
	// 	.descriptorCount = 1'000,
	// 	.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
	// };
	//
	// const auto descriptor_binding_flags = VkDescriptorBindingFlagsEXT {
	// 	VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT_EXT
	// 	    | VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT_EXT
	// 	    | VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT_EXT
	// 	    | VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT_EXT,
	// };
	//
	// constexpr auto descriptor_count = uint32_t { 1'000 };
	//
	// auto descriptor_binding_flags_info = VkDescriptorSetLayoutBindingFlagsCreateInfoEXT {
	// 	.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO_EXT,
	// 	.bindingCount = 1,
	// 	.pBindingFlags = &descriptor_binding_flags,
	// };
	//
	//
	// m_vertices_descriptor_set_layout = m_device->create_descriptor_set_layout(
	//     {
	//         .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
	//         .pNext = &descriptor_binding_flags_info,
	//         .flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT_EXT,
	//         .bindingCount = 1u,
	//         .pBindings = &binding,
	//
	//     }
	// );
	//
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

	m_layout = vk::PipelineLayout(
	    m_device->vk(),
	    vk::PipelineLayout::CreateInfo {
	        // std::vector<VkDescriptorSetLayout> {
	        //     m_vertices_descriptor_set_layout,
	        // },
	        //
	        // std::vector<VkPushConstantRange> {
	        //     VkPushConstantRange {
	        //         .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
	        //         .offset = 0u,
	        //         .size = sizeof(FrameConstants),
	        //     },
	        // },
	    }
	);

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
