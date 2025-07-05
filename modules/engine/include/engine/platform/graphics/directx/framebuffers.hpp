#pragma once

#include <d3d11.h>
#include <engine/base/base.hpp>
#include <engine/graphics/framebuffer.hpp>
#include <wrl.h>

namespace Light {

class dxSharedContext;

class dxFramebuffer: public Framebuffer
{
private:
	Ref<dxSharedContext> m_context;

	FramebufferSpecification m_specification;

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_render_target_view;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_color_attachment;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depth_stencil_attachment;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shader_resource_view;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depth_stencil_view;

public:
	dxFramebuffer(
	    const FramebufferSpecification &specification,
	    Ref<dxSharedContext> sharedContext
	);

	inline void *GetColorAttachment() override
	{
		return (void *)m_shader_resource_view.Get();
	}

	void BindAsTarget(const glm::vec4 &clearColor) override;
	void BindAsResource() override;

	void Resize(const glm::uvec2 &size) override;
};

} // namespace Light
