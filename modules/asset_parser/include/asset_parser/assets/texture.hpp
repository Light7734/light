#pragma once

#include <array>
#include <asset_parser/parser.hpp>

namespace Assets {

enum class TextureFormat : uint8_t
{
	None = 0,
	RGBA8,
};

struct TextureInfo
{
	size_t size;
	CompressionMode compression_mode;
	TextureFormat format;
	std::array<uint32_t, 3> pixel_size;
	std::string original_file;
};

auto read_texture_info(AssetFile *file) -> TextureInfo;

void unpack_texture(
    TextureInfo *info,
    const void *source_buffer,
    size_t source_size,
    void *destination
);

auto pack_texture(TextureInfo *info, void *pixel_data) -> AssetFile;

} // namespace Assets
