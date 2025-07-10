#pragma once


#include <renderer/render_command.hpp>

struct GLFWwindow;

namespace Light {

class glRenderCommand: public RenderCommand
{
public:
	glRenderCommand(GLFWwindow *windowHandle);

	void swap_buffers() override;

	void clear_back_buffer(const glm::vec4 &clearColor) override;

	void draw(unsigned int count) override;

	void draw_indexed(unsigned int count) override;

	void default_target_framebuffer() override;

	void set_viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	    override;

private:
	GLFWwindow *m_window_handle;
};

} // namespace Light
