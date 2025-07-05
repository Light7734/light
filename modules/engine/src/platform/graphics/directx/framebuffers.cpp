#include <engine/platform/graphics/directx/framebuffers.hpp>
#include <engine/platform/graphics/directx/shared_context.hpp>

namespace Light {

dxFramebuffer::dxFramebuffer(
    const FramebufferSpecification &specification,
    Ref<dxSharedContext> sharedContext
)
    : m_Context(sharedContext)
    , m_Specification(specification)
    , m_RenderTargetView(nullptr)
    , m_ColorAttachment(nullptr)
    , m_DepthStencilAttachment(nullptr)
    , m_ShaderResourceView(nullptr)
    , m_DepthStencilView(nullptr)
{
	HRESULT hr;

	D3D11_TEXTURE2D_DESC t2dDesc = {};
	t2dDesc.Width = specification.width;
	t2dDesc.Height = specification.height;
	t2dDesc.MipLevels = 1;
	t2dDesc.ArraySize = 1;
	t2dDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	t2dDesc.SampleDesc.Count = 1u;
	t2dDesc.SampleDesc.Quality = 0u;
	t2dDesc.Usage = D3D11_USAGE_DEFAULT;
	t2dDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	t2dDesc.CPUAccessFlags = NULL;
	t2dDesc.MiscFlags = NULL;
	DXC(m_Context->GetDevice()->CreateTexture2D(&t2dDesc, nullptr, &m_ColorAttachment));

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = t2dDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.MostDetailedMip = 0;
	DXC(m_Context->GetDevice()
	        ->CreateShaderResourceView(m_ColorAttachment.Get(), &srvDesc, &m_ShaderResourceView));

	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = t2dDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0u;
	DXC(m_Context->GetDevice()
	        ->CreateRenderTargetView(m_ColorAttachment.Get(), &rtvDesc, &m_RenderTargetView));
}

void dxFramebuffer::BindAsTarget(const glm::vec4 &clearColor)
{
	FLOAT color[] = {
		clearColor.r,
		clearColor.g,
		clearColor.b,
		clearColor.a,
	};

	m_Context->GetDeviceContext()
	    ->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), nullptr);
	m_Context->GetDeviceContext()->ClearRenderTargetView(m_RenderTargetView.Get(), color);

	D3D11_VIEWPORT viewport;

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	viewport.Width = m_Specification.width;
	viewport.Height = m_Specification.height;

	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	// set viewport
	m_Context->GetDeviceContext()->RSSetViewports(1u, &viewport);
}

void dxFramebuffer::BindAsResource()
{
	LOG(err, "NO_IMPLEMENT");
}

void dxFramebuffer::Resize(const glm::uvec2 &size)
{
	m_Specification.width = std::clamp(size.x, 1u, 16384u);
	m_Specification.height = std::clamp(size.y, 1u, 16384u);

	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

	m_ColorAttachment->GetDesc(&textureDesc);
	m_RenderTargetView->GetDesc(&rtvDesc);
	m_ShaderResourceView->GetDesc(&srvDesc);

	textureDesc.Width = m_Specification.width;
	textureDesc.Height = m_Specification.height;

	HRESULT hr;
	DXC(m_Context->GetDevice()->CreateTexture2D(&textureDesc, nullptr, &m_ColorAttachment));
	DXC(m_Context->GetDevice()
	        ->CreateRenderTargetView(m_ColorAttachment.Get(), &rtvDesc, &m_RenderTargetView));
	DXC(m_Context->GetDevice()
	        ->CreateShaderResourceView(m_ColorAttachment.Get(), &srvDesc, &m_ShaderResourceView));
}

} // namespace Light
