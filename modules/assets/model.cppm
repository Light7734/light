export module assets.model;

import preliminary;
import assets.metadata;
import logger;
import math.vec3;
import math.vec2;

export namespace lt::assets {

class ModelAsset
{
public:
	struct Vertex
	{
		math::vec3 position;

		math::vec2 uv;

		math::vec3 normal;
	};

	static constexpr auto asset_magic_bytes = Type_T { "MODEL__________" };

	enum class BlobTag : Tag_T
	{
		vertices,
		indices,
	};

	struct PackData
	{
		AssetMetadata asset_metadata;

		Blob vertices;

		Blob indices;
	};

	ModelAsset(const std::filesystem::path &path);

	static void pack(std::filesystem::path destination, const PackData &data);

	ModelAsset();

	void unpack_to(BlobTag tag, std::span<byte> destination) const;

	[[nodiscard]] auto unpack(BlobTag tag) const -> Blob;

	[[nodiscard]] auto get_asset_metadata() const -> const AssetMetadata &
	{
		return m_asset_metadata;
	}

	[[nodiscard]] auto get_blob_metadata(BlobTag tag) const -> const BlobMetadata &
	{
		if (tag == BlobTag::vertices)
		{
			return m_vertices_blob_metadata;
		}

		return m_indices_blob_metadata;
	}

private:
	AssetMetadata m_asset_metadata {};

	BlobMetadata m_vertices_blob_metadata {};

	BlobMetadata m_indices_blob_metadata {};

	mutable std::ifstream m_stream {};
};

} // namespace lt::assets


namespace lt::assets {

// NOLINTNEXTLINE(bugprone-sizeof-container)
constexpr auto asset_metadata_size = sizeof(AssetMetadata::type) //
                                     + sizeof(AssetMetadata::version);

constexpr auto blob_metadata_size = sizeof(BlobMetadata::tag)                //
                                    + sizeof(BlobMetadata::offset)           //
                                    + sizeof(BlobMetadata::compression_type) //
                                    + sizeof(BlobMetadata::compressed_size)  //
                                    + sizeof(BlobMetadata::uncompressed_size);

constexpr auto total_metadata_size = asset_metadata_size   //
                                     + blob_metadata_size  // vertices_blob_metadata
                                     + blob_metadata_size; // indices_blob_metadata

ModelAsset::ModelAsset(const std::filesystem::path &path): m_stream(path, std::ios::binary)
{
	ensure(m_stream.is_open(), "Failed to open model asset at: {}", path.string());
	const auto read = [this](auto &field) {
		m_stream.read(std::bit_cast<char *>(&field), sizeof(field));
	};

	m_stream.seekg(0, std::ifstream::end);
	const auto file_size = static_cast<size_t>(m_stream.tellg());
	ensure(
	    file_size > total_metadata_size,
	    "Failed to open model asset at: {}, file smaller than metadata: {} < {}",
	    path.string(),
	    total_metadata_size,
	    file_size
	);
	m_stream.seekg(0, std::ifstream::beg);

	read(m_asset_metadata.type);
	read(m_asset_metadata.version);

	read(m_vertices_blob_metadata.tag);
	read(m_vertices_blob_metadata.offset);
	read(m_vertices_blob_metadata.compression_type);
	read(m_vertices_blob_metadata.compressed_size);
	read(m_vertices_blob_metadata.uncompressed_size);

	read(m_indices_blob_metadata.tag);
	read(m_indices_blob_metadata.offset);
	read(m_indices_blob_metadata.compression_type);
	read(m_indices_blob_metadata.compressed_size);
	read(m_indices_blob_metadata.uncompressed_size);

	ensure(
	    m_asset_metadata.type == asset_magic_bytes,
	    "Failed to open model asset at: {}, magic bytes mismatch: {} != {}",
	    path.string(),
	    m_asset_metadata.type,
	    asset_magic_bytes
	);

	ensure(
	    m_asset_metadata.version == current_version,
	    "Failed to open model asset at: {}, version mismatch: {} != {}",
	    path.string(),
	    m_asset_metadata.version,
	    current_version
	);

	ensure(
	    m_vertices_blob_metadata.tag == std::to_underlying(BlobTag::vertices),
	    "Failed to open model asset at: {}, invalid blob tag: {}",
	    path.string(),
	    m_vertices_blob_metadata.tag
	);

	ensure(
	    m_vertices_blob_metadata.offset + m_vertices_blob_metadata.compressed_size <= file_size,
	    "Failed to open model asset at: {}, file smaller than blob: {} > {} + {}",
	    path.string(),
	    file_size,
	    m_vertices_blob_metadata.offset,
	    m_vertices_blob_metadata.compressed_size
	);

	ensure(
	    m_indices_blob_metadata.tag == std::to_underlying(BlobTag::indices),
	    "Failed to open model asset at: {}, invalid blob tag: {}",
	    path.string(),
	    m_indices_blob_metadata.tag
	);

	ensure(
	    m_indices_blob_metadata.offset + m_indices_blob_metadata.compressed_size <= file_size,
	    "Failed to open model asset at: {}, file smaller than blob: {} > {} + {}",
	    path.string(),
	    file_size,
	    m_indices_blob_metadata.offset,
	    m_indices_blob_metadata.compressed_size
	);
}

/* static */ void ModelAsset::pack(std::filesystem::path destination, const PackData &data)
{
	auto stream = std::ofstream {
		destination,
		std::ios::binary | std::ios::trunc,
	};

	const auto vertices_metadata = BlobMetadata {
		.tag = std::to_underlying(BlobTag::vertices),
		.offset = total_metadata_size,
		.compression_type = CompressionType::none,
		.compressed_size = data.vertices.size(),
		.uncompressed_size = data.vertices.size(),
	};

	const auto indices_metadata = BlobMetadata {
		.tag = std::to_underlying(BlobTag::indices),
		.offset = total_metadata_size + vertices_metadata.compressed_size,
		.compression_type = CompressionType::none,
		.compressed_size = data.indices.size(),
		.uncompressed_size = data.indices.size(),
	};

	ensure(stream.is_open(), "Failed to pack model asset to {}", destination.string());
	const auto write = [&stream](auto &field) {
		stream.write(std::bit_cast<char *>(&field), sizeof(field));
	};

	write(data.asset_metadata.type);
	write(data.asset_metadata.version);

	write(vertices_metadata.tag);
	write(vertices_metadata.offset);
	write(vertices_metadata.compression_type);
	write(vertices_metadata.compressed_size);
	write(vertices_metadata.uncompressed_size);
	stream.write(
	    std::bit_cast<char *>(data.vertices.data()),
	    static_cast<long long>(data.vertices.size())
	);

	write(indices_metadata.tag);
	write(indices_metadata.offset);
	write(indices_metadata.compression_type);
	write(indices_metadata.compressed_size);
	write(indices_metadata.uncompressed_size);
	stream.write(
	    std::bit_cast<char *>(data.indices.data()),
	    static_cast<long long>(data.indices.size())
	);
}

void ModelAsset::unpack_to(BlobTag tag, std::span<byte> destination) const
{
	auto metadata = tag == BlobTag::vertices ? m_vertices_blob_metadata : m_indices_blob_metadata;

	ensure(
	    destination.size() >= metadata.uncompressed_size,
	    "Failed to unpack model blob {} to destination ({}) of size {} since it's smaller "
	    "than the blob's uncompressed size: {}",
	    std::to_underlying(tag),
	    std::bit_cast<size_t>(destination.data()),
	    destination.size(),
	    metadata.uncompressed_size
	);

	m_stream.seekg(static_cast<long long>(metadata.offset), std::ifstream::beg);
	m_stream.read(
	    std::bit_cast<char *>(destination.data()),
	    std::bit_cast<std::streamsize>(metadata.uncompressed_size)
	);
}

[[nodiscard]] auto ModelAsset::unpack(BlobTag tag) const -> Blob
{
	auto metadata = tag == BlobTag::vertices ? m_vertices_blob_metadata : m_indices_blob_metadata;

	auto blob = Blob(metadata.uncompressed_size);
	unpack_to(tag, blob);

	return blob;
}

}; // namespace lt::assets
