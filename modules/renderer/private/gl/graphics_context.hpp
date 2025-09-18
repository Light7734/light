#pragma once


#include <renderer/graphics_context.hpp>

namespace lt {

class glGraphicsContext: public GraphicsContext
{
public:
	glGraphicsContext();

	void log_debug_data() override;

private:
	void set_debug_message_callback();
};

} // namespace lt
