#pragma once

#include <d3d11.h>
#include <renderer/blender.hpp>
#include <wrl.h>

namespace Light {

class dxSharedContext;

class dxBlender: public Blender
{
public:
	dxBlender(Ref<dxSharedContext> sharedContext);

	void enable(BlendFactor srcFactor, BlendFactor dstFactor) override;

	void disable() override;

private:
	Ref<dxSharedContext> m_context;

	const std::unordered_map<BlendFactor, D3D11_BLEND> m_factor_map;

	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blend_state;

	D3D11_BLEND_DESC m_desc;
};

} // namespace Light
