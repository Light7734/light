#pragma once

#include <d3d11.h>
#include <engine/base/base.hpp>
#include <engine/graphics/texture.hpp>
#include <wrl.h>

namespace Light {

class dxSharedContext;

class dxTexture: public Texture
{
public:
	dxTexture(
	    unsigned int width,
	    unsigned int height,
	    unsigned int components,
	    unsigned char *pixels,
	    Ref<dxSharedContext> sharedContext,
	    const std::string &filePath
	);

	void bind(unsigned int slot = 0u) override;

private:
	Ref<dxSharedContext> m_context;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture_2d;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shader_resource_view;

	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler_state;
};

} // namespace Light
