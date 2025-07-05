#pragma once

#include <d3d11.h>
#include <engine/base/base.hpp>
#include <engine/graphics/shared_context.hpp>
#include <wrl.h>

namespace Light {

class dxSharedContext: public SharedContext
{
private:
	Microsoft::WRL::ComPtr<ID3D11Device> m_Device = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView = nullptr;

public:
	inline Microsoft::WRL::ComPtr<ID3D11Device> GetDevice()
	{
		return m_Device;
	}
	inline Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDeviceContext()
	{
		return m_DeviceContext;
	}
	inline Microsoft::WRL::ComPtr<IDXGISwapChain> GetSwapChain()
	{
		return m_SwapChain;
	}
	inline Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRenderTargetView()
	{
		return m_RenderTargetView;
	}

	inline Microsoft::WRL::ComPtr<ID3D11Device> &GetDeviceRef()
	{
		return m_Device;
	}
	inline Microsoft::WRL::ComPtr<ID3D11DeviceContext> &GetDeviceContextRef()
	{
		return m_DeviceContext;
	}
	inline Microsoft::WRL::ComPtr<IDXGISwapChain> &GetSwapChainRef()
	{
		return m_SwapChain;
	}
	inline Microsoft::WRL::ComPtr<ID3D11RenderTargetView> &GetRenderTargetViewRef()
	{
		return m_RenderTargetView;
	}
};

} // namespace Light
