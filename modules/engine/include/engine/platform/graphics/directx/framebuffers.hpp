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
	Ref<dxSharedContext> m_Context;

	FramebufferSpecification m_Specification;

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_ColorAttachment;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_DepthStencilAttachment;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView;

public:
	dxFramebuffer(
	    const FramebufferSpecification &specification,
	    Ref<dxSharedContext> sharedContext
	);

	inline void *GetColorAttachment() override
	{
		return (void *)m_ShaderResourceView.Get();
	}

	void BindAsTarget(const glm::vec4 &clearColor) override;
	void BindAsResource() override;

	void Resize(const glm::uvec2 &size) override;
};

} // namespace Light
