#pragma once


#include <renderer/framebuffer.hpp>

namespace lt {

class glFramebuffer: public Framebuffer
{
public:
	glFramebuffer(const FramebufferSpecification &specification);

	virtual ~glFramebuffer();

	void bind_as_target(const glm::vec4 &clearColor) override;

	void bind_as_resource() override;

	void resize(const glm::uvec2 &size) override;

	auto get_color_attachment() -> void * override
	{
		return (void *)m_color_attachment_id;
	}

private:
	FramebufferSpecification m_specification;

	unsigned int m_buffer_id;

	unsigned int m_color_attachment_id;

	unsigned int m_depth_stencil_attachment_id;
};

} // namespace lt
