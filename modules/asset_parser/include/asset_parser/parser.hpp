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
		Texture,
		Mesh,
		Material,
	};

	struct Metadata
	{
		Type type;
	};

	Asset() = default;

	Asset(Metadata metadata, std::filesystem::path path, std::ifstream stream)
	    : m_metadata(metadata)
	    , m_file_path(std::move(path))
	    , m_stream(std::move(stream))
	{
	}

	/** Directly unpacks from disk to the destination.
	 *
	 * @note The destination MUST have at least blob_metadata.unpacked_size bytes available for
	 * writing, otherwise segfault could occur!
	 */
	void unpack_blob(BlobMetadata::Tag blob_tag, std::byte *destination);

	[[nodiscard]] auto get_metadata() const -> const Metadata &
	{
		return m_metadata;
	}

	[[nodiscard]] auto get_file_path() const -> std::filesystem::path
	{
		return m_file_path;
	}

private:
	Metadata m_metadata;

	std::filesystem::path m_file_path;

	std::ifstream m_stream;
};

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

	/** Data required to pack a texture */
	struct PackageData
	{
		Asset::Metadata metadata;

		Metadata texture_metadata;

		Blob pixels;
	};

	TextureAsset(const std::filesystem::path &path)
	{
		m_stream = std::ifstream { path, std::ios::binary };
		if (!m_stream.is_open())
		{
			throw std::runtime_error { std::format(
				"Failed to open ifm_stream for loading texture asset at: {}",
				path.string()
			) };
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
				std::format("Failed to load texture asset: invalid number of blobs: {}", num_blobs)
			};
		}

		m_stream.read((char *)&m_pixel_blob_metadata, sizeof(m_pixel_blob_metadata));
		if (m_pixel_blob_metadata.tag != BlobMetadata::Tag::color)
		{
			throw std::runtime_error {
				std::format(
				    "Failed to load texture asset: invalid blob tag, expected {}, got {}",
				    std::to_underlying(BlobMetadata::Tag::color),
				    std::to_underlying(m_pixel_blob_metadata.tag)
				),
			};
		}
		// NOLINTEND(cppcoreguidelines-pro-type-cstyle-cast)
	}

	void unpack_blob(BlobMetadata::Tag tag, std::byte *destination, size_t destination_capacity)
	{
		if (tag != BlobMetadata::Tag::color)
		{
			throw std::runtime_error { std::format(
				"Invalid tag for unpack_blob of TextureAsset: {}",
				std::to_underlying(tag)
			) };
		}

		m_stream.seekg(static_cast<long>(m_pixel_blob_metadata.offset));
		switch (m_pixel_blob_metadata.compression_type)
		{
		case Assets::CompressionType::None:
			if (m_pixel_blob_metadata.uncompressed_size != m_pixel_blob_metadata.compressed_size)
			{
				throw std::runtime_error("Failed to unpack blob from TextureAsset: "
				                         "compressed/uncompressed size mismatch for no compression "
				                         "type");
			}

			if (m_pixel_blob_metadata.uncompressed_size > destination_capacity)
			{
				throw std::runtime_error("Failed to unpack blob from TextureAsset: "
				                         "uncompressed_size > destination_capacity, unpacking "
				                         "would result in segfault");
			}

			if (!m_stream.is_open())
			{
				throw std::runtime_error("Failed to unpack blob from TextureAsset: ifstream is "
				                         "closed");
			}

			m_stream.read(
			    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast)
			    (char *)destination,
			    static_cast<long>(m_pixel_blob_metadata.uncompressed_size)
			);

			return;

		default:
			throw std::runtime_error(std::format(
			    "Failed to unpack blob from TextureAsset: unsupported "
			    "compression type: {}",
			    std::to_underlying(m_pixel_blob_metadata.compression_type)
			));
		}
	}

	static void pack(const PackageData &data, const std::filesystem::path &out_path)
	{
		const auto &[metadata, texture_metadata, pixels] = data;

		auto stream = std::ofstream { out_path, std::ios::binary | std::ios::trunc };
		if (!stream.is_open())
		{
			throw std::runtime_error {
				std::format("Failed to open ofstream for packing texture at: {}", out_path.string())
			};
		}
		stream.seekp(0);

		// NOLINTBEGIN(cppcoreguidelines-pro-type-cstyle-cast)
		stream.write((char *)&current_version, sizeof(current_version));

		stream.write((char *)&metadata, sizeof(metadata));
		stream.write((char *)&texture_metadata, sizeof(texture_metadata));

		constexpr auto number_of_blobs = uint32_t { 1 };
		stream.write((char *)&number_of_blobs, sizeof(number_of_blobs));

		auto pixels_metadata = BlobMetadata {
			.tag = BlobMetadata::Tag::color,
			.offset = static_cast<size_t>(stream.tellp()),
			.compression_type = CompressionType::None,
			.compressed_size = pixels.size(),
			.uncompressed_size = pixels.size(),
		};

		stream.write((char *)&pixels_metadata, sizeof(pixels_metadata));
		stream.write((char *)&pixels[0], static_cast<long>(pixels.size()));
		// NOLINTEND(cppcoreguidelines-pro-type-cstyle-cast)
	}

	[[nodiscard]] auto get_asset_metadata() const -> const Asset::Metadata &
	{
		return m_asset_metadata;
	}

	[[nodiscard]] auto get_metadata() const -> const Metadata &
	{
		return m_metadata;
	}

	[[nodiscard]] auto get_blob_metadata(BlobMetadata::Tag tag) const -> const BlobMetadata &
	{
		if (tag != BlobMetadata::Tag::color)
		{
			throw std::runtime_error { std::format(
				"Invalid tag for get_blob_metadata of TextureAsset: {}",
				std::to_underlying(tag)
			) };
		}

		return m_pixel_blob_metadata;
	}

private:
	Asset::Metadata m_asset_metadata {};

	Metadata m_metadata {};

	BlobMetadata m_pixel_blob_metadata {};

	uint32_t version {};

	std::ifstream m_stream;
};

} // namespace Assets
