#pragma once


#include <renderer/texture.hpp>

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

	~glTexture() override;

	void bind(unsigned int slot = 0u) override;

	auto get_texture() -> void * override;

private:
	unsigned int m_texture_id;
};

} // namespace Light
