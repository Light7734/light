#include <engine/platform/graphics/directx/blender.hpp>
#include <engine/platform/graphics/directx/shared_context.hpp>

namespace Light {

dxBlender::dxBlender(Ref<dxSharedContext> sharedContext)
    : m_context(sharedContext), m_factor_map { // constants
	                                          { BlendFactor::ZERO, D3D11_BLEND_ZERO },
	                                          { BlendFactor::ONE, D3D11_BLEND_ONE },

	                                          // source
	                                          { BlendFactor::SRC_COLOR, D3D11_BLEND_SRC_COLOR },
	                                          { BlendFactor::INVERSE_SRC_COLOR, D3D11_BLEND_INV_SRC_COLOR },

	                                          { BlendFactor::SRC_ALPHA, D3D11_BLEND_SRC_ALPHA },
	                                          { BlendFactor::INVERSE_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA },

	                                          // destination
	                                          { BlendFactor::DST_COLOR, D3D11_BLEND_DEST_COLOR },
	                                          { BlendFactor::INVERSE_DST_COLOR, D3D11_BLEND_INV_DEST_COLOR },

	                                          { BlendFactor::DST_ALPHA, D3D11_BLEND_DEST_ALPHA },
	                                          { BlendFactor::INVERSE_DST_ALPHA, D3D11_BLEND_INV_DEST_ALPHA },

	                                          // source1
	                                          { BlendFactor::SRC1_COLOR, D3D11_BLEND_SRC1_COLOR },
	                                          { BlendFactor::INVERSE_SRC1_COLOR, D3D11_BLEND_INV_SRC1_COLOR },

	                                          { BlendFactor::SRC1_ALPHA, D3D11_BLEND_SRC1_ALPHA },
	                                          { BlendFactor::INVERSE_SRC1_ALPHA, D3D11_BLEND_INV_SRC1_ALPHA }
    }
    , m_blend_state(nullptr)
    , m_desc {}
{
	// factor map
	// blender desc
	m_desc = {};

	m_desc.RenderTarget[0].BlendEnable = true;
	m_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
	m_desc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	m_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	m_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	m_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	m_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	m_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// create blend state
	HRESULT hr;
	DXC(m_context->GetDevice()->CreateBlendState(&m_desc, &m_blend_state));
}

void dxBlender::Enable(BlendFactor srcFactor, BlendFactor dstFactor)
{
	// update desc
	m_desc.RenderTarget[0].BlendEnable = true;
	m_desc.RenderTarget[0].SrcBlend = m_factor_map.at(srcFactor);
	m_desc.RenderTarget[0].DestBlend = m_factor_map.at(dstFactor);

	// re-create blind state
	HRESULT hr;
	DXC(m_context->GetDevice()->CreateBlendState(&m_desc, &m_blend_state));

	// bind blend state
	m_context->GetDeviceContext()->OMSetBlendState(m_blend_state.Get(), nullptr, 0x0000000f);
}

void dxBlender::Disable()
{
	// update desc
	m_desc.RenderTarget[0].BlendEnable = false;

	// re-create blind state
	HRESULT hr;
	DXC(m_context->GetDevice()->CreateBlendState(&m_desc, &m_blend_state));

	// bind blend state
	m_context->GetDeviceContext()->OMSetBlendState(m_blend_state.Get(), nullptr, 0xffffffff);
}

} // namespace Light
