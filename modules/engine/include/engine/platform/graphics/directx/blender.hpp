#pragma once

#include <d3d11.h>
#include <engine/base/base.hpp>
#include <engine/graphics/blender.hpp>
#include <wrl.h>

namespace Light {

class dxSharedContext;

class dxBlender: public Blender
{
private:
	Ref<dxSharedContext> m_context;

	const std::unordered_map<BlendFactor, D3D11_BLEND> m_factor_map;

	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blend_state;

	D3D11_BLEND_DESC m_desc;

public:
	dxBlender(Ref<dxSharedContext> sharedContext);

	void Enable(BlendFactor srcFactor, BlendFactor dstFactor) override;
	void Disable() override;
};

} // namespace Light
