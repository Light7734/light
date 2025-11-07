#include <renderer/backend/vk/context/device.hpp>
#include <renderer/backend/vk/context/swapchain.hpp>
#include <renderer/backend/vk/renderer/pass.hpp>
#include <renderer/data/frame_constants.hpp>

namespace lt::renderer::vk {

Pass::Pass(
    IDevice *device,
    ISwapchain *swapchain,
    const lt::assets::ShaderAsset &vertex_shader,
    const lt::assets::ShaderAsset &fragment_shader
)
    : m_device(static_cast<Device *>(device))
{
	auto binding = VkDescriptorSetLayoutBinding {
		.binding = 0,
		.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
		.descriptorCount = 1'000,
		.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
	};

	const auto descriptor_binding_flags = VkDescriptorBindingFlagsEXT {
		VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT_EXT
		    | VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT_EXT
		    | VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT_EXT
		    | VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT_EXT,
	};

	constexpr auto descriptor_count = uint32_t { 1'000 };

	auto descriptor_binding_flags_info = VkDescriptorSetLayoutBindingFlagsCreateInfoEXT {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO_EXT,
		.bindingCount = 1,
		.pBindingFlags = &descriptor_binding_flags,
	};


	m_vertices_descriptor_set_layout = m_device->create_descriptor_set_layout(
	    {
	        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
	        .pNext = &descriptor_binding_flags_info,
	        .flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT_EXT,
	        .bindingCount = 1u,
	        .pBindings = &binding,

	    }
	);

	auto pool_size = VkDescriptorPoolSize {
		.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
		.descriptorCount = descriptor_count,
	};

	m_descriptor_pool = m_device->create_desscriptor_pool(
	    {
	        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
	        .poolSizeCount = 1u,
	        .pPoolSizes = &pool_size,
	    }
	);

	auto descriptor_set_variable_descriptor_count_info
	    = VkDescriptorSetVariableDescriptorCountAllocateInfo {
		      .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO,
		      .descriptorSetCount = 1u,
		      .pDescriptorCounts = &descriptor_count,
	      };

	m_vertices_descriptor_set = m_device->allocate_descriptor_set(
	    VkDescriptorSetAllocateInfo {
	        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
	        .pNext = &descriptor_set_variable_descriptor_count_info,
	        .descriptorPool = m_descriptor_pool,
	        .descriptorSetCount = 1u,
	        .pSetLayouts = &m_vertices_descriptor_set_layout,
	    }
	);

	m_layout = m_device->create_pipeline_layout(
	    std::vector<VkDescriptorSetLayout> {
	        m_vertices_descriptor_set_layout,
	    },

	    std::vector<VkPushConstantRange> {
	        VkPushConstantRange {
	            .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
	            .offset = 0u,
	            .size = sizeof(FrameConstants),
	        },
	    }
	);

	auto *vertex_module = create_module(
	    vertex_shader.unpack(lt::assets::ShaderAsset::BlobTag::code)
	);

	auto *fragment_module = create_module(
	    fragment_shader.unpack(lt::assets::ShaderAsset::BlobTag::code)
	);

	auto shader_stages = std::array<VkPipelineShaderStageCreateInfo, 2> {
		VkPipelineShaderStageCreateInfo {
		    .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		    .stage = VK_SHADER_STAGE_VERTEX_BIT,
		    .module = vertex_module,
		    .pName = "main",
		},
		VkPipelineShaderStageCreateInfo {
		    .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		    .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
		    .module = fragment_module,
		    .pName = "main",
		},
	};

	auto dynamic_states = std::array<VkDynamicState, 2> {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR,
	};

	auto dynamic_state = VkPipelineDynamicStateCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.dynamicStateCount = static_cast<uint32_t>(dynamic_states.size()),
		.pDynamicStates = dynamic_states.data(),
	};

	auto vertex_input = VkPipelineVertexInputStateCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
	};

	auto input_assembly = VkPipelineInputAssemblyStateCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
		.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		.primitiveRestartEnable = VK_FALSE,
	};

	auto viewport_state = VkPipelineViewportStateCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
		.viewportCount = 1u,
		.scissorCount = 1u,
	};

	auto rasterization = VkPipelineRasterizationStateCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.depthClampEnable = VK_FALSE,
		.rasterizerDiscardEnable = VK_FALSE,
		.polygonMode = VK_POLYGON_MODE_FILL,
		.cullMode = VK_CULL_MODE_NONE,
		.frontFace = VK_FRONT_FACE_CLOCKWISE,
		.lineWidth = 1.0,
	};

	auto multisampling = VkPipelineMultisampleStateCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
		.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
		.sampleShadingEnable = VK_FALSE,
		.minSampleShading = 1.0,
		.pSampleMask = nullptr,
		.alphaToCoverageEnable = VK_FALSE,
		.alphaToOneEnable = VK_FALSE,
	};

	auto color_blend_attachment = VkPipelineColorBlendAttachmentState {
		.blendEnable = VK_FALSE,
		.srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
		.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,
		.colorBlendOp = VK_BLEND_OP_ADD,
		.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
		.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
		.alphaBlendOp = VK_BLEND_OP_ADD,
		.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT
		                  | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
	};

	auto color_blend = VkPipelineColorBlendStateCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.logicOpEnable = VK_FALSE,
		.logicOp = VK_LOGIC_OP_COPY,
		.attachmentCount = 1,
		.pAttachments = &color_blend_attachment,
		.blendConstants = { 0.0f, 0.0, 0.0, 0.0 },
	};

	// auto attachment_description = VkAttachmentDescription {
	// 	.format =,
	// 	.samples = VK_SAMPLE_COUNT_1_BIT,
	// 	.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
	// 	.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
	// 	.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
	// 	.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
	// 	.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
	// 	.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
	// };

	auto color_attachment_ref = VkAttachmentReference {
		.attachment = 0,
		.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
	};

	auto subpass_description = VkSubpassDescription {
		.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
		.colorAttachmentCount = 1u,
		.pColorAttachments = &color_attachment_ref,
	};

	auto pass_dependency = VkSubpassDependency {
		.srcSubpass = VK_SUBPASS_EXTERNAL,
		.dstSubpass = 0u,
		.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		.srcAccessMask = 0u,
		.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
	};

	auto color_format = static_cast<Swapchain *>(swapchain)->get_format();
	auto rendering_info = VkPipelineRenderingCreateInfoKHR {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO,
		.colorAttachmentCount = 1u,
		.pColorAttachmentFormats = &color_format,

	};

	m_pipeline = m_device->create_graphics_pipeline(
	    VkGraphicsPipelineCreateInfo {
	        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
	        .pNext = &rendering_info,
	        .stageCount = static_cast<uint32_t>(shader_stages.size()),
	        .pStages = shader_stages.data(),
	        .pVertexInputState = &vertex_input,
	        .pInputAssemblyState = &input_assembly,
	        .pViewportState = &viewport_state,
	        .pRasterizationState = &rasterization,
	        .pMultisampleState = &multisampling,
	        .pDepthStencilState = nullptr,
	        .pColorBlendState = &color_blend,
	        .pDynamicState = &dynamic_state,
	        .layout = m_layout,
	        .renderPass = VK_NULL_HANDLE,
	        .subpass = 0u,
	        .basePipelineHandle = VK_NULL_HANDLE,
	        .basePipelineIndex = -1,
	    }
	);

	// m_framebuffers = static_cast<Swapchain *>(swapchain)->create_framebuffers_for_pass(m_pass);

	m_device->destroy_shader_module(vertex_module);
	m_device->destroy_shader_module(fragment_module);
}

Pass::~Pass()
{
	if (!m_device)
	{
		return;
	}

	m_device->wait_idle();

	m_device->destroy_descriptor_set_layout(m_vertices_descriptor_set_layout);
	m_device->free_descriptor_set(m_descriptor_pool, m_vertices_descriptor_set);
	m_device->destroy_descriptor_pool(m_descriptor_pool);

	m_device->destroy_framebuffers(m_framebuffers);
	m_device->destroy_pipeline(m_pipeline);
	// m_device->destroy_pass(m_pass);
	m_device->destroy_pipeline_layout(m_layout);
}

void Pass::replace_swapchain(const ISwapchain &swapchain)
{
	if (!m_device)
	{
		return;
	}

	m_device->wait_idle();
	m_device->destroy_framebuffers(m_framebuffers);
	// m_framebuffers = static_cast<const Swapchain
	// &>(swapchain).create_framebuffers_for_pass(m_pass);
}

auto Pass::create_module(lt::assets::Blob blob) -> VkShaderModule
{
	return m_device->create_shader_module(
	    VkShaderModuleCreateInfo {
	        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
	        .codeSize = blob.size(),
	        .pCode = reinterpret_cast<const uint32_t *>(blob.data()) // NOLINT
	    }
	);
}


} // namespace lt::renderer::vk
