#pragma once

#include <engine/base/base.hpp>
#include <imgui.h>

struct GLFWwindow;

namespace Light {

class Event;

class SharedContext;

// #todo: fix the UserIntreface mess!!
class UserInterface /* singleton */
{
private:
	static UserInterface *s_Context;

private:
	ImGuiWindowFlags m_dockspace_flags;

public:
	static Scope<UserInterface> create(GLFWwindow *windowHandle, Ref<SharedContext> sharedContext);

	UserInterface(const UserInterface &) = delete;
	UserInterface &operator=(const UserInterface &) = delete;

	virtual ~UserInterface() = default;

	void init(GLFWwindow *windowHandle, Ref<SharedContext> sharedContext);

	static void dockspace_begin();
	static void dockspace_end();

	virtual void platform_implementation(
	    GLFWwindow *windowHandle,
	    Ref<SharedContext> sharedContext
	) = 0;

	virtual void begin() = 0;
	virtual void end() = 0;

	virtual void log_debug_data() = 0;

protected:
	UserInterface();

private:
	void set_dark_theme_colors();
};

} // namespace Light
