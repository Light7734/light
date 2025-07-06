#include <engine/platform/graphics/directx/render_command.hpp>
#include <engine/platform/graphics/directx/shared_context.hpp>

namespace Light {

dxRenderCommand::dxRenderCommand(Ref<dxSharedContext> sharedContext): m_context(sharedContext)
{
}

void dxRenderCommand::swap_buffers()
{
#ifdef LIGHT_DEBUG
	HRESULT hr;
	if (FAILED(hr = m_context->get_swap_chain()->Present(1u, 0u)))
	{
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
		{
			log_crt("dxRenderCommand::swap_buffers: DeviceRemoved:");
			log_crt("        {}", m_context->get_device()->GetDeviceRemovedReason());
			throw dxException(hr, __FILE__, __LINE__);
		}
	}
#else
	m_context->get_swap_chain()->Present(0u, 0u);
#endif
}

void dxRenderCommand::clear_back_buffer(const glm::vec4 &clearColor)
{
	m_context->get_device_context()->ClearRenderTargetView(
	    m_context->get_render_target_view().Get(),
	    &clearColor[0]
	);
}

void dxRenderCommand::draw(unsigned int count)
{
	m_context->get_device_context()->draw(count, 0u);
}

void dxRenderCommand::draw_indexed(unsigned int count)
{
	m_context->get_device_context()->draw_indexed(count, 0u, 0u);
}

void dxRenderCommand::default_target_framebuffer()
{
	m_context->get_device_context()
	    ->OMSetRenderTargets(1, m_context->get_render_target_view().GetAddressOf(), nullptr);
}

void dxRenderCommand::set_viewport(
    unsigned int x,
    unsigned int y,
    unsigned int width,
    unsigned int height
)
{
	// #todo: maybe call this somewhere else??
	set_resolution(width, height);

	// create viewport
	auto viewport = D3D11_VIEWPORT {};

	viewport.TopLeftX = x;
	viewport.TopLeftY = y;

	viewport.Width = width;
	viewport.Height = height;

	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	// set viewport
	m_context->get_device_context()->RSSetViewports(1u, &viewport);
}

void dxRenderCommand::set_resolution(unsigned int width, unsigned int height)
{
	auto hr = HRESULT {};

	// remove render target
	auto *nullViews[] = (ID3D11RenderTargetView *) { nullptr };
	m_context->get_device_context()->OMSetRenderTargets(1u, nullViews, nullptr);
	m_context->GetRenderTargetViewRef().reset();

	// resize buffer
	dxc(m_context->get_swap_chain()
	        ->ResizeBuffers(0u, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, NULL));

	// create render target
	auto backBuffer = Microsoft::WRL::ComPtr<ID3D11Resource> { nullptr };
	dxc(m_context->get_swap_chain()->GetBuffer(0u, __uuidof(ID3D11Resource), &backBuffer));
	dxc(m_context->get_device()->CreateRenderTargetView(
	    backBuffer.Get(),
	    nullptr,
	    &m_context->GetRenderTargetViewRef()
	));

	// set render target
	m_context->get_device_context()
	    ->OMSetRenderTargets(1u, m_context->get_render_target_view().GetAddressOf(), nullptr);
}

} // namespace Light
