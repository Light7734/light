#include <assets/shader.hpp>

namespace lt::assets {

constexpr auto total_metadata_size =         //
    sizeof(AssetMetadata::type)              //
    + sizeof(AssetMetadata::version)         //
    + sizeof(ShaderAsset::Metadata::type)    //
    + sizeof(BlobMetadata::tag)              //
    + sizeof(BlobMetadata::offset)           //
    + sizeof(BlobMetadata::compression_type) //
    + sizeof(BlobMetadata::compressed_size)  //
    + sizeof(BlobMetadata::uncompressed_size);

ShaderAsset::ShaderAsset(const std::filesystem::path &path): m_stream(path)
{
	ensure(m_stream.is_open(), "Failed to open shader asset at: {}", path.string());
	const auto read = [this](auto &field) {
		m_stream.read(std::bit_cast<char *>(&field), sizeof(field));
	};

	m_stream.seekg(0, std::ifstream::end);
	const auto file_size = static_cast<size_t>(m_stream.tellg());
	ensure(
	    file_size > total_metadata_size,
	    "Failed to open shader asset at: {}, file smaller than metadata: {} < {}",
	    path.string(),
	    total_metadata_size,
	    file_size
	);

	m_stream.seekg(0, std::ifstream::beg);
	read(m_asset_metadata.type);
	read(m_asset_metadata.version);
	read(m_metadata.type);
	read(m_code_blob_metadata.tag);
	read(m_code_blob_metadata.offset);
	read(m_code_blob_metadata.compression_type);
	read(m_code_blob_metadata.compressed_size);
	read(m_code_blob_metadata.uncompressed_size);

	ensure(
	    m_asset_metadata.type == asset_type_identifier,
	    "Failed to open shader asset at: {}, incorrect asset type: {} != {}",
	    path.string(),
	    m_asset_metadata.type,
	    asset_type_identifier
	);

	ensure(
	    m_asset_metadata.version == current_version,
	    "Failed to open shader asset at: {}, version mismatch: {} != {}",
	    path.string(),
	    m_asset_metadata.version,
	    current_version
	);

	ensure(
	    std::to_underlying(m_metadata.type) <= std::to_underlying(Type::compute),
	    "Failed to open shader asset at: {}, invalid shader type: {}",
	    path.string(),
	    std::to_underlying(m_metadata.type)
	);

	ensure(
	    m_code_blob_metadata.tag == std::to_underlying(BlobTag::code),
	    "Failed to open shader asset at: {}, invalid blob tag: {}",
	    path.string(),
	    m_code_blob_metadata.tag
	);

	ensure(
	    m_code_blob_metadata.offset + m_code_blob_metadata.compressed_size <= file_size,
	    "Failed to open shader asset at: {}, file smaller than blob: {} > {} + {}",
	    path.string(),
	    file_size,
	    m_code_blob_metadata.offset,
	    m_code_blob_metadata.compressed_size
	);
}

/* static */ void ShaderAsset::pack(
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

	const auto code_blob_metadata = BlobMetadata {
		.tag = std::to_underlying(BlobTag::code),
		.offset = total_metadata_size,
		.compression_type = CompressionType::none,
		.compressed_size = code_blob.size(),
		.uncompressed_size = code_blob.size(),
	};

	ensure(stream.is_open(), "Failed to pack shader asset to {}", destination.string());
	const auto write = [&stream](auto &field) {
		stream.write(std::bit_cast<char *>(&field), sizeof(field));
	};
	write(asset_metadata.type);
	write(asset_metadata.version);
	write(metadata.type);
	write(code_blob_metadata.tag);
	write(code_blob_metadata.offset);
	write(code_blob_metadata.compression_type);
	write(code_blob_metadata.compressed_size);
	write(code_blob_metadata.uncompressed_size);
	stream.write(std::bit_cast<char *>(code_blob.data()), static_cast<long long>(code_blob.size()));
}

void ShaderAsset::unpack_to(BlobTag tag, std::span<std::byte> destination) const
{
	ensure(tag == BlobTag::code, "Invalid blob tag for shader asset: {}", std::to_underlying(tag));

	ensure(
	    destination.size() >= m_code_blob_metadata.uncompressed_size,
	    "Failed to unpack shader blob {} to destination ({}) of size {} since it's smaller "
	    "than the blobl's uncompressed size: {}",
	    std::to_underlying(tag),
	    std::bit_cast<size_t>(destination.data()),
	    destination.size(),
	    m_code_blob_metadata.uncompressed_size
	);

	m_stream.seekg(static_cast<long long>(m_code_blob_metadata.offset));
	m_stream.read(
	    std::bit_cast<char *>(destination.data()),
	    static_cast<long long>(m_code_blob_metadata.uncompressed_size)
	);
}

[[nodiscard]] auto ShaderAsset::unpack(BlobTag tag) const -> Blob
{
	ensure(tag == BlobTag::code, "Invalid blob tag for shader asset: {}", std::to_underlying(tag));

	auto blob = Blob(m_code_blob_metadata.uncompressed_size);
	unpack_to(tag, blob);

	return blob;
}

} // namespace lt::assets
