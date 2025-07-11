#include <asset_parser/assets/text.hpp>
#include <lz4.h>
#include <nlohmann/json.hpp>

namespace Assets {

/* static */ void TextAsset::pack(const PackageData &data, const std::filesystem::path &out_path)
{
	const auto &[metadata, text_metadata, text] = data;

	auto stream = std::ofstream { out_path, std::ios::binary | std::ios::trunc };
	if (!stream.is_open())
	{
		throw std::runtime_error {
			std::format("Failed to open ofstream for packing Text at: {}", out_path.string())
		};
	}
	stream.seekp(0);

	// NOLINTBEGIN(cppcoreguidelines-pro-type-cstyle-cast)
	stream.write((char *)&current_version, sizeof(current_version));
	stream.write((char *)&metadata, sizeof(metadata));
	stream.write((char *)&text_metadata, sizeof(text_metadata));

	constexpr auto number_of_blobs = uint32_t { 1 };
	stream.write((char *)&number_of_blobs, sizeof(number_of_blobs));

	auto textblob_metadata = BlobMetadata {
		.tag = BlobMetadata::Tag::text,
		.offset = static_cast<size_t>(stream.tellp()) + sizeof(BlobMetadata),
		.compression_type = CompressionType::None,
		.compressed_size = text.size(),
		.uncompressed_size = text.size(),
	};

	stream.write((char *)&textblob_metadata, sizeof(textblob_metadata));
	stream.write((char *)text.data(), static_cast<long>(text.size()));
	// NOLINTEND(cppcoreguidelines-pro-type-cstyle-cast)
}

TextAsset::TextAsset(const std::filesystem::path &path)
{
	m_stream = std::ifstream { path, std::ios::binary };
	if (!m_stream.is_open())
	{
		throw std::runtime_error {
			std::format("Failed to open ifstream for loading Text asset at: {}", path.string())
		};
	}

	// NOLINTBEGIN(cppcoreguidelines-pro-type-cstyle-cast)
	m_stream.read((char *)&version, sizeof(version));
	m_stream.read((char *)&m_asset_metadata, sizeof(m_asset_metadata));
	m_stream.read((char *)&m_metadata, sizeof(m_metadata));

	auto num_blobs = uint32_t {};
	m_stream.read((char *)&num_blobs, sizeof(num_blobs));
	if (num_blobs != 1)
	{
		throw std::runtime_error {
			std::format("Failed to load Text asset: invalid number of blobs: {}", num_blobs)
		};
	}

	m_stream.read((char *)&m_text_blob_metadata, sizeof(m_text_blob_metadata));
	if (m_text_blob_metadata.tag != BlobMetadata::Tag::text)
	{
		throw std::runtime_error {
			std::format(
			    "Failed to load Text asset: invalid blob tag, expected {}, got {}",
			    std::to_underlying(BlobMetadata::Tag::text),
			    std::to_underlying(m_text_blob_metadata.tag)
			),
		};
	}
	// NOLINTEND(cppcoreguidelines-pro-type-cstyle-cast)
}

void TextAsset::unpack_blob(
    BlobMetadata::Tag tag,
    std::byte *destination,
    size_t destination_capacity
) const
{
	if (tag != BlobMetadata::Tag::text)
	{
		throw std::runtime_error {
			std::format("Invalid tag for unpack_blob of TextAsset: {}", std::to_underlying(tag))
		};
	}

	m_stream.seekg(static_cast<long>(m_text_blob_metadata.offset));
	switch (m_text_blob_metadata.compression_type)
	{
	case Assets::CompressionType::None:
		if (m_text_blob_metadata.uncompressed_size != m_text_blob_metadata.compressed_size)
		{
			throw std::runtime_error(
			    "Failed to unpack blob from TextAsset: "
			    "compressed/uncompressed size mismatch for no compression "
			    "type"
			);
		}

		if (m_text_blob_metadata.uncompressed_size > destination_capacity)
		{
			throw std::runtime_error(
			    "Failed to unpack blob from TextAsset: "
			    "uncompressed_size > destination_capacity, unpacking "
			    "would result in segfault"
			);
		}

		if (!m_stream.is_open())
		{
			throw std::runtime_error(
			    "Failed to unpack blob from TextAsset: ifstream is "
			    "closed"
			);
		}

		m_stream.read(
		    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast)
		    (char *)destination,
		    static_cast<long>(m_text_blob_metadata.uncompressed_size)
		);

		return;

	default:
		throw std::runtime_error(
		    std::format(
		        "Failed to unpack blob from TextAsset: unsupported "
		        "compression type: {}",
		        std::to_underlying(m_text_blob_metadata.compression_type)
		    )
		);
	}
}

[[nodiscard]] auto TextAsset::get_asset_metadata() const -> const Asset::Metadata &
{
	return m_asset_metadata;
}

[[nodiscard]] auto TextAsset::get_metadata() const -> const Metadata &
{
	return m_metadata;
}

[[nodiscard]] auto TextAsset::get_blob_metadata(BlobMetadata::Tag tag) const -> const BlobMetadata &
{
	if (tag != BlobMetadata::Tag::text)
	{
		throw std::runtime_error { std::format(
			"Invalid tag for get_blob_metadata of TextAsset: {}",
			std::to_underlying(tag)
		) };
	}

	return m_text_blob_metadata;
}

} // namespace Assets
