#include <renderer/gl/render_command.hpp>
#include <glad/gl.h>
#ifndef DONT_FUCKING_ORDER_THESSE_PLEASE_FOR_THE_LOVE_OF_GOD_CLANG_FORMAT
	#include <GLFW/glfw3.h>
#endif

namespace lt {

glRenderCommand::glRenderCommand(GLFWwindow *windowHandle): m_window_handle(windowHandle)
{
}

void glRenderCommand::swap_buffers()
{
	glfwSwapBuffers(m_window_handle);
}

void glRenderCommand::clear_back_buffer(const glm::vec4 &clearColor)
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
	glBindFramebuffer(GL_FRAMEBUFFER, NULL);
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
