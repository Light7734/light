#pragma once

#include <assets/shader.hpp>
#include <memory/pointer_types/null_on_move.hpp>
#include <renderer/backend/vk/utils.hpp>
#include <renderer/frontend/renderer/pass.hpp>

namespace lt::renderer::vk {

class Pass: public IPass
{
public:
	Pass(
	    class IDevice *device,
	    class ISwapchain *swapchain,
	    const lt::assets::ShaderAsset &vertex_shader,
	    const lt::assets::ShaderAsset &fragment_shader
	);

	~Pass() override;

	Pass(Pass &&) = default;

	Pass(const Pass &) = delete;

	auto operator=(Pass &&) -> Pass & = default;

	auto operator=(const Pass &) -> Pass & = delete;

	void replace_swapchain(const ISwapchain &swapchain);

	[[nodiscard]] auto get_pipeline() -> VkPipeline
	{
		return m_pipeline;
	}

	[[nodiscard]] auto get_layout() -> VkPipelineLayout
	{
		return m_layout;
	}

	[[nodiscard]] auto get_framebuffers() -> std::vector<VkFramebuffer> &
	{
		return m_framebuffers;
	}

private:
	auto create_module(lt::assets::Blob blob) -> VkShaderModule;

	memory::NullOnMove<class Device *> m_device {};

	VkPipeline m_pipeline = VK_NULL_HANDLE;

	VkPipelineLayout m_layout = VK_NULL_HANDLE;

	std::vector<VkFramebuffer> m_framebuffers;
};

} // namespace lt::renderer::vk
