#pragma once

#include <assets/metadata.hpp>

namespace lt::assets {

class ShaderAsset
{
public:
	static constexpr auto asset_type_identifier = Type_T { "SHADER_________" };

	enum class BlobTag : Tag_T
	{
		code,
	};

	enum class Type : uint8_t
	{
		vertex,
		fragment,
		geometry,
		compute,
	};

	struct Metadata
	{
		Type type;
	};

	static void pack(
	    const std::filesystem::path &destination,
	    AssetMetadata asset_metadata,
	    Metadata metadata,
	    Blob code_blob
	);

	ShaderAsset(const std::filesystem::path &path);

	void unpack_to(BlobTag tag, std::span<std::byte> destination) const;

	[[nodiscard]] auto unpack(BlobTag tag) const -> Blob;

	[[nodiscard]] auto get_asset_metadata() const -> const AssetMetadata &
	{
		return m_asset_metadata;
	}

	[[nodiscard]] auto get_metadata() const -> const Metadata &
	{
		return m_metadata;
	}

	[[nodiscard]] auto get_blob_metadata(BlobTag tag) const -> const BlobMetadata &
	{
		ensure(
		    tag == BlobTag::code,
		    "Invalid blob tag for shader asset: {}",
		    std::to_underlying(tag)
		);

		return m_code_blob_metadata;
	}

private:
	AssetMetadata m_asset_metadata {};

	Metadata m_metadata {};

	BlobMetadata m_code_blob_metadata {};

	mutable std::ifstream m_stream;
};

} // namespace lt::assets
