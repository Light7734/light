#pragma once

#include <engine/base/base.hpp>
#include <engine/user_interface/user_interface.hpp>

struct GLFWwindow;

namespace Light {

class glUserInterface: public UserInterface
{
public:
	glUserInterface() = default;

	~glUserInterface() override;

	void platform_implementation(GLFWwindow *windowHandle, Ref<SharedContext> sharedContext)
	    override;

	void begin() override;

	void end() override;

	void log_debug_data() override;

private:
	GLFWwindow *m_window_handle{};
};

} // namespace Light
