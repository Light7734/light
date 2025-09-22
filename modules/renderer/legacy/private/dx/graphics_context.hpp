#pragma once

#include <d3d11.h>
#include <renderer/graphics_context.hpp>
#include <wrl.h>

namespace lt {

class dxGraphicsContext: public GraphicsContext
{
public:
	dxGraphicsContext();

	virtual void log_debug_data() override;

private:
	Microsoft::WRL::ComPtr<ID3D11Debug> m_debug_interface;

	void setup_device_and_swap_chain();

	void setup_render_targets();

	void setup_debug_interface();
};

} // namespace lt
