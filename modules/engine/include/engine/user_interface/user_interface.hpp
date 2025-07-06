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
public:
	static auto create(GLFWwindow *windowHandle, Ref<SharedContext> sharedContext)
	    -> Scope<UserInterface>;

	static void dockspace_begin();

	static void dockspace_end();

	UserInterface(const UserInterface &) = delete;

	auto operator=(const UserInterface &) -> UserInterface & = delete;

	virtual ~UserInterface() = default;

	void init(GLFWwindow *windowHandle, Ref<SharedContext> sharedContext);

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
	static UserInterface *s_context;

	void set_dark_theme_colors();

	ImGuiWindowFlags m_dockspace_flags;
};

} // namespace Light
