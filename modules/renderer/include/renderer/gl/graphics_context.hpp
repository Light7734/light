#pragma once


#include <renderer/graphics_context.hpp>

struct GLFWwindow;

namespace lt {

class glGraphicsContext: public GraphicsContext
{
public:
	glGraphicsContext(GLFWwindow *windowHandle);

	void log_debug_data() override;

private:
	GLFWwindow *m_window_handle;

	void set_debug_message_callback();
};

} // namespace lt
