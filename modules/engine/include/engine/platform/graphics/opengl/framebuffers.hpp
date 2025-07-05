#pragma once

#include <engine/base/base.hpp>
#include <engine/graphics/framebuffer.hpp>

namespace Light {

class glFramebuffer: public Framebuffer
{
private:
	FramebufferSpecification m_Specification;

	unsigned int m_BufferID;
	unsigned int m_ColorAttachmentID, m_DepthStencilAttachmentID;

public:
	glFramebuffer(const FramebufferSpecification &specification);
	~glFramebuffer();

	void BindAsTarget(const glm::vec4 &clearColor) override;
	void BindAsResource() override;

	void Resize(const glm::uvec2 &size) override;

	inline void *GetColorAttachment() override
	{
		return (void *)m_ColorAttachmentID;
	}
};

} // namespace Light
