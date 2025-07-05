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

	void PlatformImplementation(GLFWwindow *windowHandle, Ref<SharedContext> sharedContext)
	    override;

	void Begin() override;
	void End() override;

	void LogDebugData() override;
};

} // namespace Light
