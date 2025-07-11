#pragma once

#include <asset_parser/parser.hpp>
#include <compressors/compressors.hpp>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <logger/logger.hpp>

namespace Assets {

class TextAsset: public Asset
{
public:
	struct Metadata
	{
		uint32_t lines {};
	};

	/** Data required to pack a text asset */
	struct PackageData
	{
		Asset::Metadata metadata;

		Metadata text_metadata;

		Blob text_blob;
	};

	static void pack(const PackageData &data, const std::filesystem::path &out_path);

	TextAsset(const std::filesystem::path &path);

	void unpack_blob(
	    BlobMetadata::Tag tag,
	    std::byte *destination,
	    size_t destination_capacity
	) const;

	[[nodiscard]] auto get_asset_metadata() const -> const Asset::Metadata &;

	[[nodiscard]] auto get_metadata() const -> const Metadata &;

	[[nodiscard]] auto get_blob_metadata(BlobMetadata::Tag tag) const -> const BlobMetadata &;

private:
	uint32_t version {};

	Asset::Metadata m_asset_metadata {};

	Metadata m_metadata {};

	BlobMetadata m_text_blob_metadata {};

	mutable std::ifstream m_stream;
};

} // namespace Assets
