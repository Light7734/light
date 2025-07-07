#pragma once

#include "AssetParser.hpp"

namespace Assets {

enum class TextureFormat
{
	None = 0,
	RGBA8,
};

struct TextureInfo
{
	size_t size;
	CompressionMode compression_mode;
	TextureFormat format;
	uint32_t pixel_size[3];
	std::string original_file;
};

TextureInfo read_texture_info(AssetFile* file);

void unpack_texture(
  TextureInfo* info,
  const void* source_buffer,
  size_t source_size,
  void* destination
);

AssetFile pack_texture(TextureInfo* info, void* pixel_data);

} // namespace Assets
