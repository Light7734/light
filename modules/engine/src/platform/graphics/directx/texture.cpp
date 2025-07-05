#include <engine/platform/graphics/directx/shared_context.hpp>
#include <engine/platform/graphics/directx/texture.hpp>

namespace Light {

dxTexture::dxTexture(
    unsigned int width,
    unsigned int height,
    unsigned int components,
    unsigned char *pixels,
    Ref<dxSharedContext> sharedContext,
    const std::string &filePath
)
    : Texture(filePath)
    , m_context(sharedContext)
    , m_texture_2d(nullptr)
    , m_shader_resource_view(nullptr)
    , m_sampler_state(nullptr)
{
	// texture2d desc
	D3D11_TEXTURE2D_DESC t2dDesc = {};
	t2dDesc.Width = width;
	t2dDesc.Height = height;
	t2dDesc.MipLevels = 0u;
	t2dDesc.ArraySize = 1u;
	t2dDesc.Format = components == 4u ? DXGI_FORMAT_R8G8B8A8_UNORM :
	                 components == 3u ? DXGI_FORMAT_R8G8B8A8_UNORM :
	                                    // #todo: figure out what to do with this bitch ._.
	                     components == 2u ? DXGI_FORMAT_R8G8_UNORM :
	                 components == 1u     ? DXGI_FORMAT_R8_UNORM :
	                                        DXGI_FORMAT_UNKNOWN;
	t2dDesc.SampleDesc.Count = 1u;
	t2dDesc.SampleDesc.Quality = 0u;
	t2dDesc.Usage = D3D11_USAGE_DEFAULT;
	t2dDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	t2dDesc.CPUAccessFlags = NULL;
	t2dDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	// create texture
	HRESULT hr;
	dxc(m_context->get_device()->CreateTexture2D(&t2dDesc, nullptr, &m_texture_2d));
	m_context->get_device_context()
	    ->UpdateSubresource(m_texture_2d.Get(), 0u, nullptr, pixels, width * 4u, 0u);

	m_texture_2d->GetDesc(&t2dDesc);

	// shader resource view desc
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = t2dDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0u;
	srvDesc.Texture2D.MipLevels = -1;

	// create shader resource view
	m_context->get_device()
	    ->CreateShaderResourceView(m_texture_2d.Get(), &srvDesc, &m_shader_resource_view);
	m_context->get_device_context()->GenerateMips(m_shader_resource_view.Get());

	// sampler desc
	D3D11_SAMPLER_DESC sDesc = {};
	sDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sDesc.MinLOD = 0.0f;
	sDesc.MipLODBias = 0.0f;
	sDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// create sampler
	m_context->get_device()->CreateSamplerState(&sDesc, &m_sampler_state);
}

void dxTexture::bind(unsigned int slot /* = 0u */)
{
	m_context->get_device_context()->PSSetSamplers(slot, 1u, m_sampler_state.GetAddressOf());
	m_context->get_device_context()
	    ->PSSetShaderResources(slot, 1u, m_shader_resource_view.GetAddressOf());
}

} // namespace Light
