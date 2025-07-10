#include <asset_parser/assets/texture.hpp>
#include <debug/assertions.hpp>
#include <glad/gl.h>
#include <renderer/gl/texture.hpp>

namespace Light {

glTexture::glTexture(const Ref<Assets::TextureAsset> &asset)
{
	const auto metadata = asset->get_metadata();
	const auto blob_metadata = asset->get_blob_metadata(Assets::BlobMetadata::Tag::color);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_texture_id);
	glTextureParameteri(m_texture_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(m_texture_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	auto blob = std::vector<std::byte>(blob_metadata.uncompressed_size);
	asset->unpack_blob(blob_metadata.tag, blob.data(), blob.size());

	bind();
	glTexImage2D(
	    GL_TEXTURE_2D,
	    0,
	    map_num_components_to_internal_format(metadata.num_components),
	    static_cast<int>(metadata.pixel_size[0]),
	    static_cast<int>(metadata.pixel_size[1]),
	    0,
	    map_num_components_to_format(metadata.num_components),
	    GL_UNSIGNED_BYTE,
	    std::bit_cast<unsigned char *>(blob.data())
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

[[nodiscard]] auto glTexture::map_num_components_to_format(uint32_t num_components) const -> int
{
	switch (num_components)
	{
	case 4u: return GL_RGBA;
	case 3u: return GL_RGB;
	case 2u: return GL_RG;
	case 1u: return GL_RED;
	default: lt_assert(false, "Invalid number of components: {}", num_components);
	}

	return {};
}

[[nodiscard]] auto glTexture::map_num_components_to_internal_format(uint32_t num_components) const
    -> int
{
	switch (num_components)
	{
	case 4u: return GL_RGBA8;
	case 3u: return GL_RGB8;
	case 2u: return GL_RG8;
	case 1u: return GL_R8;
	default: lt_assert(false, "Invalid number of components: {}", num_components);
	}

	return {};
}

} // namespace Light
