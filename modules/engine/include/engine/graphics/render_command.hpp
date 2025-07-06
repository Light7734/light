#pragma once

#include <engine/base/base.hpp>
#include <glm/glm.hpp>

struct GLFWwindow;

namespace Light {

class SharedContext;

class RenderCommand
{
public:
	static auto create(GLFWwindow *windowHandle, const Ref<SharedContext>& sharedContext)
	    -> Scope<RenderCommand>;

	RenderCommand(const RenderCommand &) = delete;

	auto operator=(const RenderCommand &) -> RenderCommand & = delete;

	virtual ~RenderCommand() = default;

	virtual void swap_buffers() = 0;

	virtual void clear_back_buffer(const glm::vec4 &clearColor) = 0;

	virtual void draw(unsigned int count) = 0;

	virtual void draw_indexed(unsigned int count) = 0;

	virtual void default_target_framebuffer() = 0;

	virtual void set_viewport(
	    unsigned int x,
	    unsigned int y,
	    unsigned int width,
	    unsigned int height
	) = 0;

protected:
	RenderCommand() = default;
};

} // namespace Light
