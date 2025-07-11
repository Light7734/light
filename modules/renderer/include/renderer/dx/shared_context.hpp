#pragma once

#include <d3d11.h>
#include <renderer/shared_context.hpp>
#include <wrl.h>

namespace lt {

class dxSharedContext: public SharedContext
{
public:
	[[nodiscard]] auto get_device() -> Microsoft::WRL::ComPtr<ID3D11Device>
	{
		return m_device;
	}

	[[nodiscard]] auto get_device_context() -> Microsoft::WRL::ComPtr<ID3D11DeviceContext>
	{
		return m_deviceContext;
	}

	[[nodiscard]] auto get_swap_chain() -> Microsoft::WRL::ComPtr<IDXGISwapChain>
	{
		return m_swap_chain;
	}

	[[nodiscard]] auto get_render_target_view() -> Microsoft::WRL::ComPtr<ID3D11RenderTargetView>
	{
		return m_render_target_view;
	}

	[[nodiscard]] auto &GetDeviceRef() -> Microsoft::WRL::ComPtr<ID3D11Device>
	{
		return m_device;
	}

	[[nodiscard]] auto &GetDeviceContextRef() -> Microsoft::WRL::ComPtr<ID3D11DeviceContext>
	{
		return m_deviceContext;
	}

	[[nodiscard]] auto &GetSwapChainRef() -> Microsoft::WRL::ComPtr<IDXGISwapChain>
	{
		return m_swap_chain;
	}

	[[nodiscard]] auto &GetRenderTargetViewRef() -> Microsoft::WRL::ComPtr<ID3D11RenderTargetView>
	{
		return m_render_target_view;
	}

private:
	Microsoft::WRL::ComPtr<ID3D11Device> m_device = nullptr;

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext = nullptr;

	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swap_chain = nullptr;

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_render_target_view = nullptr;
};

} // namespace lt
