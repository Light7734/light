#include <engine/platform/graphics/directx/render_command.hpp>
#include <engine/platform/graphics/directx/shared_context.hpp>

namespace Light {

dxRenderCommand::dxRenderCommand(Ref<dxSharedContext> sharedContext): m_Context(sharedContext)
{
}

void dxRenderCommand::SwapBuffers()
{
#ifdef LIGHT_DEBUG
	HRESULT hr;
	if (FAILED(hr = m_Context->GetSwapChain()->Present(1u, 0u)))
	{
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
		{
			LOG(critical, "dxRenderCommand::SwapBuffers: DeviceRemoved:");
			LOG(critical, "        {}", m_Context->GetDevice()->GetDeviceRemovedReason());
			throw dxException(hr, __FILE__, __LINE__);
		}
	}
#else
	m_Context->GetSwapChain()->Present(0u, 0u);
#endif
}

void dxRenderCommand::ClearBackBuffer(const glm::vec4 &clearColor)
{
	m_Context->GetDeviceContext()->ClearRenderTargetView(
	    m_Context->GetRenderTargetView().Get(),
	    &clearColor[0]
	);
}

void dxRenderCommand::Draw(unsigned int count)
{
	m_Context->GetDeviceContext()->Draw(count, 0u);
}

void dxRenderCommand::DrawIndexed(unsigned int count)
{
	m_Context->GetDeviceContext()->DrawIndexed(count, 0u, 0u);
}

void dxRenderCommand::DefaultTargetFramebuffer()
{
	m_Context->GetDeviceContext()
	    ->OMSetRenderTargets(1, m_Context->GetRenderTargetView().GetAddressOf(), nullptr);
}

void dxRenderCommand::SetViewport(
    unsigned int x,
    unsigned int y,
    unsigned int width,
    unsigned int height
)
{
	// #todo: maybe call this somewhere else??
	SetResolution(width, height);

	// create viewport
	D3D11_VIEWPORT viewport;

	viewport.TopLeftX = x;
	viewport.TopLeftY = y;

	viewport.Width = width;
	viewport.Height = height;

	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	// set viewport
	m_Context->GetDeviceContext()->RSSetViewports(1u, &viewport);
}

void dxRenderCommand::SetResolution(unsigned int width, unsigned int height)
{
	HRESULT hr;

	// remove render target
	ID3D11RenderTargetView *nullViews[] = { nullptr };
	m_Context->GetDeviceContext()->OMSetRenderTargets(1u, nullViews, nullptr);
	m_Context->GetRenderTargetViewRef().Reset();

	// resize buffer
	DXC(m_Context->GetSwapChain()
	        ->ResizeBuffers(0u, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, NULL));

	// create render target
	Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer = nullptr;
	DXC(m_Context->GetSwapChain()->GetBuffer(0u, __uuidof(ID3D11Resource), &backBuffer));
	DXC(m_Context->GetDevice()->CreateRenderTargetView(
	    backBuffer.Get(),
	    nullptr,
	    &m_Context->GetRenderTargetViewRef()
	));

	// set render target
	m_Context->GetDeviceContext()
	    ->OMSetRenderTargets(1u, m_Context->GetRenderTargetView().GetAddressOf(), nullptr);
}

} // namespace Light
