#include <glad/gl.h>
#include <glm/glm.hpp>
#include <renderer/gl/framebuffers.hpp>

namespace lt {

glFramebuffer::glFramebuffer(const FramebufferSpecification &specification)
    : m_specification(specification)
    , m_buffer_id(NULL)
    , m_color_attachment_id(NULL)
    , m_depth_stencil_attachment_id(NULL)
{
	resize({ specification.width, specification.height });
}

glFramebuffer::~glFramebuffer()
{
	glDeleteFramebuffers(1, &m_buffer_id);
	glDeleteTextures(1, &m_color_attachment_id);
	// glDeleteTextures(1, &m_depth_stencil_attachment_id);
}

void glFramebuffer::bind_as_target(const glm::vec4 &clearColor)
{
	// #todo: use viewport instead of default x=0, y=0
	glBindFramebuffer(GL_FRAMEBUFFER, m_buffer_id);
	glViewport(0, 0, m_specification.width, m_specification.height);

	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void glFramebuffer::bind_as_resource()
{
	log_err("NO_IMPLEMENT!");
}

void glFramebuffer::resize(const glm::uvec2 &size)
{
	if (m_buffer_id)
	{
		glDeleteFramebuffers(1, &m_buffer_id);
		glDeleteTextures(1, &m_color_attachment_id);
		// glDeleteTextures(1, &m_depth_stencil_attachment_id);
	}

	m_specification.width = std::clamp(size.x, 1u, (unsigned int)GL_MAX_TEXTURE_SIZE);
	m_specification.height = std::clamp(size.y, 1u, (unsigned int)GL_MAX_TEXTURE_SIZE);

	glCreateFramebuffers(1, &m_buffer_id);
	glBindFramebuffer(GL_FRAMEBUFFER, m_buffer_id);

	// create color attachment
	glCreateTextures(GL_TEXTURE_2D, 1, &m_color_attachment_id);
	glBindTexture(GL_TEXTURE_2D, m_color_attachment_id);
	glTexImage2D(
	    GL_TEXTURE_2D,
	    0,
	    GL_RGBA8,
	    m_specification.width,
	    m_specification.height,
	    NULL,
	    GL_RGBA,
	    GL_UNSIGNED_BYTE,
	    nullptr
	);
	glTextureParameteri(m_color_attachment_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_color_attachment_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(
	    GL_FRAMEBUFFER,
	    GL_COLOR_ATTACHMENT0,
	    GL_TEXTURE_2D,
	    m_color_attachment_id,
	    0
	);

	// glTextureStorage2D(m_color_attachment_id, 0, GL_RGBA8, m_specification.width,
	// m_specification.height);

	//	glCreateTextures(GL_TEXTURE_2D, 1, &m_depth_stencil_attachment_id);
	//	glBindTexture(GL_TEXTURE_2D, m_depth_stencil_attachment_id);
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_specification.width,
	// m_specification.height, NULL, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
	//	// glTextureStorage2D(m_depth_stencil_attachment_id, 0, GL_DEPTH24_STENCIL8,
	// m_specification.width, m_specification.height); 	glFramebufferTexture2D(GL_FRAMEBUFFER,
	// GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depth_stencil_attachment_id, 0);

	ensure(
	    (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE),
	    "Framebuffer is incomplete"
	);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} // namespace lt
