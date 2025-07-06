#pragma once

#include <engine/base/base.hpp>
#include <engine/graphics/texture.hpp>

namespace Light {

class glTexture: public Texture
{
public:
	glTexture(
	    unsigned int width,
	    unsigned int height,
	    unsigned int components,
	    unsigned char *pixels,
	    const std::string &filePath
	);

	~glTexture();

	void bind(unsigned int slot = 0u) override;

	auto get_texture() -> void * override;

private:
	unsigned int m_texture_id;
};

} // namespace Light
