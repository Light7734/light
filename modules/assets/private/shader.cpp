#include <assets/shader.hpp>

namespace lt::assets {

ShaderAsset::ShaderAsset(const std::filesystem::path &path): m_stream(path)
{
	constexpr auto total_metadata_size = //
	    sizeof(AssetMetadata)            //
	    + sizeof(Metadata)               //
	    + sizeof(BlobMetadata);

	ensure(m_stream.is_open(), "Failed to open shader asset at: {}", path.string());

	m_stream.seekg(0, std::ifstream::end);
	const auto file_size = static_cast<size_t>(m_stream.tellg());

	ensure(
	    file_size > total_metadata_size,
	    "Failed to open shader asset at: {}, file smaller than metadata: {} < {}",
	    path.string(),
	    total_metadata_size,
	    file_size
	);

	// NOLINTBEGIN(cppcoreguidelines-pro-type-cstyle-cast)
	m_stream.seekg(0, std::ifstream::beg);
	m_stream.read((char *)&m_asset_metadata, sizeof(m_asset_metadata));
	m_stream.read((char *)&m_metadata, sizeof(m_metadata));
	m_stream.read((char *)&m_code_blob_metadata, sizeof(m_code_blob_metadata));
	// NOLINTEND(cppcoreguidelines-pro-type-cstyle-cast)

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

} // namespace lt::assets
