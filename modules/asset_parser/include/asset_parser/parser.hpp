#pragma once

#include <stdint.h>
#include <string>
#include <vector>

namespace Assets {

struct AssetFile
{
	uint32_t version;

	enum class Type : uint32_t
	{
		Texture,
		Mesh,
		Material,
	} type;

	std::string json;
	std::vector<uint8_t> blob;
};

enum class CompressionMode : uint32_t
{
	None,
	LZ4,
	LZ4HC,
};

bool save_binary_file(const char* path, const AssetFile& in_file);
bool load_binary_file(const char* path, AssetFile& out_file);

} // namespace Assets
