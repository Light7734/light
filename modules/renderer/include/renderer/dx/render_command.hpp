#pragma once

#include <d3d11.h>
#include <renderer/render_command.hpp>
#include <wrl.h>

namespace lt {

class dxSharedContext;

class dxRenderCommand: public RenderCommand
{
public:
	dxRenderCommand(Ref<dxSharedContext> sharedContext);

	virtual void swap_buffers() override;

	virtual void clear_back_buffer(const glm::vec4 &clearColor) override;

	virtual void draw(unsigned int count) override;

	virtual void draw_indexed(unsigned int count) override;

	virtual void default_target_framebuffer() override;

	virtual void set_viewport(
	    unsigned int x,
	    unsigned int y,
	    unsigned int width,
	    unsigned int height
	) override;

private:
	Ref<dxSharedContext> m_context;

	void set_resolution(unsigned int width, unsigned int height);
};

} // namespace lt
