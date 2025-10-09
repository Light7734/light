#include <renderer/backend/vk/context/device.hpp>
#include <renderer/backend/vk/context/swapchain.hpp>
#include <renderer/backend/vk/renderer/pass.hpp>

namespace lt::renderer::vk {

Pass::Pass(
    IDevice *device,
    ISwapchain *swapchain,
    const lt::assets::ShaderAsset &vertex_shader,
    const lt::assets::ShaderAsset &fragment_shader
)
    : m_device(static_cast<Device *>(device)), m_layout(m_device->create_pipeline_layout(
	    VkPipelineLayoutCreateInfo {
	        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
	        .setLayoutCount = 0u,
	        .pSetLayouts = nullptr,
	        .pushConstantRangeCount = 0u,
	        .pPushConstantRanges = nullptr,
	    }
	))
{
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

	

	auto attachment_description = VkAttachmentDescription {
		.format = static_cast<Swapchain *>(swapchain)->get_format(),
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
		.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
		.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
		.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
		.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
	};

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

	m_pass = m_device->create_pass(
	    VkRenderPassCreateInfo {
	        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
	        .attachmentCount = 1u,
	        .pAttachments = &attachment_description,
	        .subpassCount = 1u,
	        .pSubpasses = &subpass_description,
	        .dependencyCount = 1u,
	        .pDependencies = &pass_dependency,
	    }
	);

	m_pipeline = m_device->create_graphics_pipeline(
	    VkGraphicsPipelineCreateInfo {
	        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
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
	        .renderPass = m_pass,
	        .subpass = 0u,
	        .basePipelineHandle = VK_NULL_HANDLE,
	        .basePipelineIndex = -1,
	    }
	);

	m_framebuffers = static_cast<Swapchain *>(swapchain)->create_framebuffers_for_pass(m_pass);


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
	m_device->destroy_framebuffers(m_framebuffers);
	m_device->destroy_pipeline(m_pipeline);
	m_device->destroy_pass(m_pass);
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
	m_framebuffers = static_cast<const Swapchain &>(swapchain).create_framebuffers_for_pass(m_pass);
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
