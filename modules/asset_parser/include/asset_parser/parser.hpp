#pragma once

#include <compressors/compressors.hpp>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <logger/logger.hpp>
#include <utility>
#include <vector>

namespace Assets {

constexpr auto current_version = uint32_t { 1 };

struct BlobMetadata
{
	enum class Tag : uint8_t
	{
		text,
		color,
		depth,
		vertices,
		indices,
	};

	Tag tag;

	size_t offset;

	CompressionType compression_type;

	size_t compressed_size;

	size_t uncompressed_size;
};


using Blob = std::vector<std::byte>;

class Asset
{
public:
	enum class Type : uint32_t // NOLINT(performance-enum-size)
	{
		None,
		Texture,
		Text,
		Mesh,
		Material,
	};

	struct Metadata
	{
		Type type;
	};

	Asset() = default;

	/** Directly unpacks from disk to the destination.
	 *
	 * @note The destination MUST have at least blob_metadata.unpacked_size bytes available for
	 * writing, otherwise segfault could occur!
	 */
	void unpack_blob(BlobMetadata::Tag blob_tag, std::byte *destination);
};


} // namespace Assets
