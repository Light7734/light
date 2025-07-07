#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Assets {

struct AssetFile
{
	uint32_t version;

	enum class Type : uint32_t // NOLINT(performance-enum-size)
	{
		Texture,
		Mesh,
		Material,
	} type;

	std::string json;
	std::vector<uint8_t> blob;
};

enum class CompressionMode : uint32_t // NOLINT(performance-enum-size)
{
	None,
	LZ4,
	LZ4HC,
};

auto save_binary_file(const char *path, const AssetFile &in_file) -> bool;
auto load_binary_file(const char *path, AssetFile &out_file) -> bool;

} // namespace Assets
