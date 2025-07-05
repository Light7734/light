#pragma once

#include <d3d11.h>
#include <engine/base/base.hpp>
#include <engine/graphics/render_command.hpp>
#include <wrl.h>

namespace Light {

class dxSharedContext;

class dxRenderCommand: public RenderCommand
{
private:
	Ref<dxSharedContext> m_Context;

public:
	dxRenderCommand(Ref<dxSharedContext> sharedContext);

	virtual void SwapBuffers() override;
	virtual void ClearBackBuffer(const glm::vec4 &clearColor) override;

	virtual void Draw(unsigned int count) override;
	virtual void DrawIndexed(unsigned int count) override;

	virtual void DefaultTargetFramebuffer() override;

	virtual void SetViewport(
	    unsigned int x,
	    unsigned int y,
	    unsigned int width,
	    unsigned int height
	) override;

private:
	void SetResolution(unsigned int width, unsigned int height);
};

} // namespace Light
