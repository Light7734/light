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
	static Ref<Framebuffer> Create(const FramebufferSpecification& specification, Ref<SharedContext> sharedContext);

	virtual void BindAsTarget(const glm::vec4& clearColor) = 0;
	virtual void BindAsResource()                          = 0;

	virtual void Resize(const glm::uvec2& size) = 0;

	virtual void* GetColorAttachment() = 0;

protected:
	Framebuffer() = default;
};

} // namespace Light
