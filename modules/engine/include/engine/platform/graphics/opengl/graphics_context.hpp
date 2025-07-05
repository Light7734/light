#pragma once

#include <engine/base/base.hpp>
#include <engine/graphics/graphics_context.hpp>

struct GLFWwindow;

namespace Light {

class glGraphicsContext: public GraphicsContext
{
private:
	GLFWwindow *m_window_handle;

public:
	glGraphicsContext(GLFWwindow *windowHandle);

	void log_debug_data() override;

private:
	void set_debug_message_callback();
};

} // namespace Light
