#pragma once


#include <glm/glm.hpp>

namespace lt {

class SharedContext;

struct FramebufferSpecification
{
	unsigned int width{};

	unsigned int height{};

	unsigned int samples = 1;
};

class Framebuffer
{
public:
virtual ~Framebuffer() = default;
	static auto create(
	    const FramebufferSpecification &specification,
	    const Ref<SharedContext>& sharedContext
	) -> Ref<Framebuffer>;

	virtual void bind_as_target(const glm::vec4 &clearColor) = 0;

	virtual void bind_as_resource() = 0;

	virtual void resize(const glm::uvec2 &size) = 0;

	virtual auto get_color_attachment() -> void * = 0;

protected:
	Framebuffer() = default;
};

} // namespace lt
