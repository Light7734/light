#pragma once

#include <d3d11.h>
#include <engine/base/base.hpp>
#include <engine/graphics/shared_context.hpp>
#include <wrl.h>

namespace Light {

class dxSharedContext: public SharedContext
{
public:
	inline Microsoft::WRL::ComPtr<ID3D11Device> get_device()
	{
		return m_device;
	}

	inline Microsoft::WRL::ComPtr<ID3D11DeviceContext> get_device_context()
	{
		return m_deviceContext;
	}

	inline Microsoft::WRL::ComPtr<IDXGISwapChain> get_swap_chain()
	{
		return m_swap_chain;
	}

	inline Microsoft::WRL::ComPtr<ID3D11RenderTargetView> get_render_target_view()
	{
		return m_render_target_view;
	}

	inline Microsoft::WRL::ComPtr<ID3D11Device> &GetDeviceRef()
	{
		return m_device;
	}

	inline Microsoft::WRL::ComPtr<ID3D11DeviceContext> &GetDeviceContextRef()
	{
		return m_deviceContext;
	}

	inline Microsoft::WRL::ComPtr<IDXGISwapChain> &GetSwapChainRef()
	{
		return m_swap_chain;
	}

	inline Microsoft::WRL::ComPtr<ID3D11RenderTargetView> &GetRenderTargetViewRef()
	{
		return m_render_target_view;
	}

private:
	Microsoft::WRL::ComPtr<ID3D11Device> m_device = nullptr;

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext = nullptr;

	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swap_chain = nullptr;

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_render_target_view = nullptr;
};

} // namespace Light
