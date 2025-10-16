#pragma once

#include <memory/reference.hpp>
#include <memory/scope.hpp>

namespace lt {

class Event;
class SharedContext;

class UserInterface
{
public:
	static auto create(memory::Ref<SharedContext> sharedContext) -> memory::Scope<UserInterface>;

	static void dockspace_begin();

	static void dockspace_end();

	UserInterface(const UserInterface &) = delete;

	auto operator=(const UserInterface &) -> UserInterface & = delete;

	virtual ~UserInterface() = default;

	void init(memory::Ref<SharedContext> sharedContext);

	virtual void platform_implementation(memory::Ref<SharedContext> sharedContext) = 0;

	virtual void begin() = 0;

	virtual void end() = 0;

	virtual void log_debug_data() = 0;

protected:
	UserInterface();

private:
	static UserInterface *s_context;

	void set_dark_theme_colors();
};

} // namespace lt
