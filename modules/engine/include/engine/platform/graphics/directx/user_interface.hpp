#pragma once

#include <d3d11.h>
#include <engine/base/base.hpp>
#include <engine/user_interface/user_interface.hpp>
#include <wrl.h>

struct GLFWwindow;

namespace Light {

class dxSharedContext;

class dxUserInterface: public UserInterface
{
public:
	dxUserInterface() = default;
	~dxUserInterface();

	void platform_implementation(GLFWwindow *windowHandle, Ref<SharedContext> sharedContext)
	    override;

	void begin() override;
	void end() override;

	void log_debug_data() override;
};

} // namespace Light
