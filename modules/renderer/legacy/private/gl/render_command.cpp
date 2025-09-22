#include <renderer/gl/render_command.hpp>

namespace lt {

glRenderCommand::glRenderCommand(): m_window_handle(windowHandle)
{
}

void glRenderCommand::swap_buffers()
{
}

void glRenderCommand::clear_back_buffer(const math::vec4 &clearColor)
{
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void glRenderCommand::draw(unsigned int count)
{
	glDrawArrays(GL_TRIANGLES, 0, count);
}

void glRenderCommand::draw_indexed(unsigned int count)
{
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

void glRenderCommand::default_target_framebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, {});
}

void glRenderCommand::set_viewport(
    unsigned int x,
    unsigned int y,
    unsigned int width,
    unsigned int height
)
{
	glViewport(x, y, width, height);
}

} // namespace lt
