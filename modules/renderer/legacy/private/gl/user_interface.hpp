#pragma once


#include <ui/ui.hpp>

namespace lt {

class glUserInterface: public UserInterface
{
public:
	glUserInterface() = default;

	~glUserInterface() override;

	void platform_implementation(Ref<SharedContext> sharedContext) override;

	void begin() override;

	void end() override;

	void log_debug_data() override;
};

} // namespace lt
