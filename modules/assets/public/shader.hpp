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
	)
	{
		auto stream = std::ofstream {
			destination,
			std::ios::binary | std::ios::trunc,
		};
		ensure(stream.is_open(), "Failed to pack shader asset to {}", destination.string());

		// NOLINTBEGIN(cppcoreguidelines-pro-type-cstyle-cast)
		stream.write((char *)&asset_metadata, sizeof(asset_metadata));
		stream.write((char *)&metadata, sizeof(metadata));

		auto code_blob_metadata = BlobMetadata {
			.tag = std::to_underlying(BlobTag::code),
			.offset = static_cast<size_t>(stream.tellp()) + sizeof(BlobMetadata),
			.compression_type = CompressionType::none,
			.compressed_size = code_blob.size(),
			.uncompressed_size = code_blob.size(),
		};
		stream.write((char *)&code_blob_metadata, sizeof(BlobMetadata));

		stream.write((char *)code_blob.data(), static_cast<long long>(code_blob.size()));
		// NOLINTEND(cppcoreguidelines-pro-type-cstyle-cast)
	}

	ShaderAsset(const std::filesystem::path &path);

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

	void unpack_to(BlobTag tag, std::span<std::byte> destination) const
	{
		ensure(
		    tag == BlobTag::code,
		    "Invalid blob tag for shader asset: {}",
		    std::to_underlying(tag)
		);

		ensure(
		    destination.size() >= m_code_blob_metadata.uncompressed_size,
		    "Failed to unpack shader blob {} to destination ({}) of size {} since it's smaller "
		    "than the blobl's uncompressed size: {}",
		    std::to_underlying(tag),
		    (size_t)(destination.data()), // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
		    destination.size(),
		    m_code_blob_metadata.uncompressed_size
		);

		m_stream.seekg(static_cast<long long>(m_code_blob_metadata.offset));
		m_stream.read(
		    (char *)destination.data(), // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
		    static_cast<long long>(m_code_blob_metadata.uncompressed_size)
		);
	}

	[[nodiscard]] auto unpack(BlobTag tag) const -> Blob
	{
		ensure(
		    tag == BlobTag::code,
		    "Invalid blob tag for shader asset: {}",
		    std::to_underlying(tag)
		);

		auto blob = Blob(m_code_blob_metadata.uncompressed_size);
		unpack_to(tag, blob);

		return blob;
	}

private:
	AssetMetadata m_asset_metadata {};

	Metadata m_metadata {};

	BlobMetadata m_code_blob_metadata {};

	mutable std::ifstream m_stream;
};

} // namespace lt::assets
