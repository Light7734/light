#pragma once

#include <engine/base/base.hpp>
#include <engine/user_interface/user_interface.hpp>

struct GLFWwindow;

namespace Light {

class glUserInterface: public UserInterface
{
private:
	GLFWwindow *m_window_handle;

public:
	glUserInterface() = default;
	~glUserInterface();

	void PlatformImplementation(GLFWwindow *windowHandle, Ref<SharedContext> sharedContext)
	    override;

	void Begin() override;
	void End() override;

	void LogDebugData() override;
};

} // namespace Light
