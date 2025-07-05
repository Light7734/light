#pragma once

#include <d3d11.h>
#include <engine/base/base.hpp>
#include <engine/graphics/graphics_context.hpp>
#include <wrl.h>

struct GLFWwindow;

namespace Light {

class dxGraphicsContext: public GraphicsContext
{
public:
	dxGraphicsContext(GLFWwindow *windowHandle);

	virtual void log_debug_data() override;

private:
	GLFWwindow *m_window_handle;

	Microsoft::WRL::ComPtr<ID3D11Debug> m_debug_interface;

	void setup_device_and_swap_chain(GLFWwindow *windowHandle);

	void setup_render_targets();

	void setup_debug_interface();
};

} // namespace Light
