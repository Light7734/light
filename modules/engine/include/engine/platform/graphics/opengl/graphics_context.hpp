#pragma once

#include <engine/base/base.hpp>
#include <engine/graphics/graphics_context.hpp>

struct GLFWwindow;

namespace Light {

class glGraphicsContext: public GraphicsContext
{
public:
	glGraphicsContext(GLFWwindow *windowHandle);

	void log_debug_data() override;

private:
	GLFWwindow *m_window_handle;

	void set_debug_message_callback();
};

} // namespace Light
