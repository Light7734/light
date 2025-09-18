#pragma once

#include <math/vec4.hpp>
#include <renderer/render_command.hpp>

namespace lt {

class glRenderCommand: public RenderCommand
{
public:
	glRenderCommand();

	void swap_buffers() override;

	void clear_back_buffer(const math::vec4 &clearColor) override;

	void draw(unsigned int count) override;

	void draw_indexed(unsigned int count) override;

	void default_target_framebuffer() override;

	void set_viewport(
	    unsigned int x,
	    unsigned int y,
	    unsigned int width,
	    unsigned int height
	) override;
};

} // namespace lt
