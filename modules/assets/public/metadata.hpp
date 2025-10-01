#pragma once

namespace lt::assets {

using Type_T = std::array<const char, 16>;

using Tag_T = uint8_t;

using Version = uint8_t;

using Blob = std::vector<std::byte>;

constexpr auto current_version = Version { 1u };

enum class CompressionType : uint8_t
{
	none,
	lz4,
	lz4_hc,
};

struct AssetMetadata
{
	Version version;

	Type_T type;
};

struct BlobMetadata
{
	Tag_T tag;

	size_t offset;

	CompressionType compression_type;

	size_t compressed_size;

	size_t uncompressed_size;
};

} // namespace lt::assets
