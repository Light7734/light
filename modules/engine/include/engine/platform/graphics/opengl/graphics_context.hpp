#pragma once

#include <engine/base/base.hpp>
#include <engine/graphics/graphics_context.hpp>

struct GLFWwindow;

namespace Light {

class glGraphicsContext: public GraphicsContext
{
private:
	GLFWwindow *m_WindowHandle;

public:
	glGraphicsContext(GLFWwindow *windowHandle);

	void LogDebugData() override;

private:
	void SetDebugMessageCallback();
};

} // namespace Light
