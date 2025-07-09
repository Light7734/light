#pragma once

#include <asset_parser/parser.hpp>
#include <compressors/compressors.hpp>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <logger/logger.hpp>

namespace Assets {

class TextureAsset: public Asset
{
public:
	enum class Format : uint32_t // NOLINT(performance-enum-size)
	{
		None = 0,
		RGBA8,
	};

	struct Metadata
	{
		Format format;

		uint32_t num_components;

		std::array<uint32_t, 3> pixel_size;
	};

	/** Data required to pack a texture asset */
	struct PackageData
	{
		Asset::Metadata metadata;

		Metadata texture_metadata;

		Blob pixels;
	};

	static void pack(const PackageData &data, const std::filesystem::path &out_path);

	TextureAsset(const std::filesystem::path &path);

	void unpack_blob(BlobMetadata::Tag tag, std::byte *destination, size_t destination_capacity);

	[[nodiscard]] auto get_asset_metadata() const -> const Asset::Metadata &;

	[[nodiscard]] auto get_metadata() const -> const Metadata &;

	[[nodiscard]] auto get_blob_metadata(BlobMetadata::Tag tag) const -> const BlobMetadata &;

private:
	uint32_t version {};

	Asset::Metadata m_asset_metadata {};

	Metadata m_metadata {};

	BlobMetadata m_pixel_blob_metadata {};

	std::ifstream m_stream;
};

} // namespace Assets
