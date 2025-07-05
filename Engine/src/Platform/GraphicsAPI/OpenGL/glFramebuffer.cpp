#include "glFramebuffer.hpp"

#include <glad/gl.h>
#include <glm/glm.hpp>

namespace Light {

glFramebuffer::glFramebuffer(const FramebufferSpecification& specification)
    : m_Specification(specification), m_BufferID(NULL), m_ColorAttachmentID(NULL), m_DepthStencilAttachmentID(NULL)
{
	Resize({ specification.width, specification.height });
}

glFramebuffer::~glFramebuffer()
{
	glDeleteFramebuffers(1, &m_BufferID);
	glDeleteTextures(1, &m_ColorAttachmentID);
	// glDeleteTextures(1, &m_DepthStencilAttachmentID);
}

void glFramebuffer::BindAsTarget(const glm::vec4& clearColor)
{
	// #todo: use viewport instead of default x=0, y=0
	glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);
	glViewport(0, 0, m_Specification.width, m_Specification.height);

	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void glFramebuffer::BindAsResource()
{
	LOG(err, "NO_IMPLEMENT!");
}

void glFramebuffer::Resize(const glm::uvec2& size)
{
	if (m_BufferID)
	{
		glDeleteFramebuffers(1, &m_BufferID);
		glDeleteTextures(1, &m_ColorAttachmentID);
		// glDeleteTextures(1, &m_DepthStencilAttachmentID);
	}

	m_Specification.width  = std::clamp(size.x, 1u, (unsigned int)GL_MAX_TEXTURE_SIZE);
	m_Specification.height = std::clamp(size.y, 1u, (unsigned int)GL_MAX_TEXTURE_SIZE);

	glCreateFramebuffers(1, &m_BufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);

	// create color attachment
	glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachmentID);
	glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.width, m_Specification.height, NULL, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTextureParameteri(m_ColorAttachmentID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_ColorAttachmentID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachmentID, 0);

	// glTextureStorage2D(m_ColorAttachmentID, 0, GL_RGBA8, m_Specification.width, m_Specification.height);

	//	glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthStencilAttachmentID);
	//	glBindTexture(GL_TEXTURE_2D, m_DepthStencilAttachmentID);
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specification.width, m_Specification.height, NULL, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
	//	// glTextureStorage2D(m_DepthStencilAttachmentID, 0, GL_DEPTH24_STENCIL8, m_Specification.width, m_Specification.height);
	//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthStencilAttachmentID, 0);

	ASSERT((glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE), "Framebuffer is incomplete");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} // namespace Light
