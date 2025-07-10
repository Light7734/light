#include <glad/gl.h>
#include <ltdebug/assertions.hpp>
#include <renderer/gl/texture.hpp>

namespace Light {

glTexture::glTexture(
    unsigned int width,
    unsigned int height,
    unsigned int components,
    unsigned char *pixels,
    const std::string &filePath
)
    : Texture(filePath)
    , m_texture_id(NULL)
{
	// create texture
	glCreateTextures(GL_TEXTURE_2D, 1, &m_texture_id);

	// set texture parameters
	glTextureParameteri(m_texture_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(m_texture_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// determine formats
	auto format = components == 4u ? GL_RGBA :
	              components == 3u ? GL_RGB :
	              components == 2u ? GL_RG :
	              components == 1u ? GL_RED :
	                                 NULL;

	auto internalFormat = format == GL_RGBA ? GL_RGBA8 :
	                      format == GL_RGB  ? GL_RGB8 :
	                      format == GL_RG   ? GL_RG8 :
	                      format == GL_RED  ? GL_R8 :
	                                          NULL;

	// check
	lt_assert(format, "Invalid number of components: {}", components);


	// #todo: isn't there something like glTextureImage2D ???
	// create texture and mipsmaps
	bind();
	glTexImage2D(
	    GL_TEXTURE_2D,
	    0,
	    internalFormat,
	    width,
	    height,
	    0,
	    format,
	    GL_UNSIGNED_BYTE,
	    pixels
	);
	glGenerateMipmap(GL_TEXTURE_2D);
}

glTexture::~glTexture()
{
	glDeleteTextures(1, &m_texture_id);
}

void glTexture::bind(unsigned int slot /* = 0u */)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

auto glTexture::get_texture() -> void *
{
	return (void *)(intptr_t)m_texture_id;
}

} // namespace Light
