#pragma once

#include <assets/shader.hpp>
#include <renderer/vk/context/context.hpp>
#include <renderer/vk/debug/validation.hpp>

namespace lt::renderer::vk {

class Pass
{
public:
	Pass(
	    Context &context,
	    lt::assets::ShaderAsset vertex_shader,
	    lt::assets::ShaderAsset fragment_shader
	)
	    : m_device(context.device().vk())
	{
		// auto fragment_blob = vertex_shader.unpack(lt::assets::ShaderAsset::BlobTag::code);

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

		auto layout_info = VkPipelineLayoutCreateInfo {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
			.setLayoutCount = 0u,
			.pSetLayouts = nullptr,
			.pushConstantRangeCount = 0u,
			.pPushConstantRanges = nullptr,
		};

		vkc(vk_create_pipeline_layout(m_device, &layout_info, nullptr, &m_layout));

		auto attachment_description = VkAttachmentDescription {
			.format = context.swapchain().get_format(),
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

		auto renderpass_info = VkRenderPassCreateInfo {
			.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
			.attachmentCount = 1u,
			.pAttachments = &attachment_description,
			.subpassCount = 1u,
			.pSubpasses = &subpass_description,
			.dependencyCount = 1u,
			.pDependencies = &pass_dependency,
		};

		vkc(vk_create_render_pass(m_device, &renderpass_info, nullptr, &m_pass));

		auto pipeline_info = VkGraphicsPipelineCreateInfo {
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
		};

		vkc(vk_create_graphics_pipelines(
		    m_device,
		    VK_NULL_HANDLE,
		    1u,
		    &pipeline_info,
		    nullptr,
		    &m_pipeline
		));

		vk_destroy_shader_module(m_device, vertex_module, nullptr);
		vk_destroy_shader_module(m_device, fragment_module, nullptr);

		m_framebuffers = context.swapchain().create_framebuffers_for_pass(m_pass);
	}

	~Pass()
	{
		if (!m_device)
		{
			return;
		}

		for (auto &framebuffer : m_framebuffers)
		{
			vk_destroy_frame_buffer(m_device, framebuffer, nullptr);
		}

		vk_destroy_pipeline(m_device, m_pipeline, nullptr);
		vk_destroy_render_pass(m_device, m_pass, nullptr);
		vk_destroy_pipeline_layout(m_device, m_layout, nullptr);
	}

	Pass(Pass &&) = default;

	Pass(const Pass &) = delete;

	auto operator=(Pass &&) -> Pass & = default;

	auto operator=(const Pass &) -> Pass & = delete;

	void replace_swapchain(const Swapchain &swapchain)
	{
		if (!m_device)
		{
			return;
		}

		vk_device_wait_idle(m_device);
		for (auto &framebuffer : m_framebuffers)
		{
			vk_destroy_frame_buffer(m_device, framebuffer, nullptr);
		}

		m_framebuffers = swapchain.create_framebuffers_for_pass(m_pass);
	}

	[[nodiscard]] auto get_pass() -> VkRenderPass
	{
		return m_pass;
	}

	[[nodiscard]] auto get_pipeline() -> VkPipeline
	{
		return m_pipeline;
	}

	[[nodiscard]] auto get_framebuffers() -> std::vector<VkFramebuffer> &
	{
		return m_framebuffers;
	}

private:
	auto create_module(lt::assets::Blob blob) -> VkShaderModule
	{
		log_dbg("BLOB SIZE: {}", blob.size());
		auto info = VkShaderModuleCreateInfo {
			.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
			.codeSize = blob.size(),
			.pCode = reinterpret_cast<const uint32_t *>(blob.data()) // NOLINT
		};

		auto *module = VkShaderModule { VK_NULL_HANDLE };
		vkc(vk_create_shader_module(m_device, &info, nullptr, &module));

		return module;
	}

	memory::NullOnMove<VkDevice> m_device = VK_NULL_HANDLE;

	memory::NullOnMove<VkPipeline> m_pipeline = VK_NULL_HANDLE;

	memory::NullOnMove<VkRenderPass> m_pass = VK_NULL_HANDLE;

	memory::NullOnMove<VkPipelineLayout> m_layout = VK_NULL_HANDLE;

	std::vector<VkFramebuffer> m_framebuffers;
};

} // namespace lt::renderer::vk
