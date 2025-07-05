#pragma once

#include <d3d11.h>
#include <engine/base/base.hpp>
#include <engine/graphics/graphics_context.hpp>
#include <wrl.h>

struct GLFWwindow;

namespace Light {

class dxGraphicsContext: public GraphicsContext
{
private:
	GLFWwindow *m_window_handle;

	Microsoft::WRL::ComPtr<ID3D11Debug> m_debug_interface;

public:
	dxGraphicsContext(GLFWwindow *windowHandle);

	virtual void LogDebugData() override;

private:
	void SetupDeviceAndSwapChain(GLFWwindow *windowHandle);
	void SetupRenderTargets();
	void SetupDebugInterface();
};

} // namespace Light
