#pragma once

#include <engine/base/base.hpp>

#include <glm/glm.hpp>

namespace Light {

class SharedContext;

struct FramebufferSpecification
{
	unsigned int width, height;
	unsigned int samples = 1;
};

class Framebuffer
{
public:
	static Ref<Framebuffer> create(const FramebufferSpecification& specification, Ref<SharedContext> sharedContext);

	virtual void bind_as_target(const glm::vec4& clearColor) = 0;
	virtual void bind_as_resource()                          = 0;

	virtual void resize(const glm::uvec2& size) = 0;

	virtual void* GetColorAttachment() = 0;

protected:
	Framebuffer() = default;
};

} // namespace Light
