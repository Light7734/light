export module assets.shader;
import assets.metadata;
import debug.assertions;

import lsd;

export namespace lt::assets {

class ShaderAsset
{
public:
	static constexpr auto asset_type_identifier = Type_T { "SHADER_________" };

	enum class BlobTag : Tag_T
	{
		code,
	};

	enum class Type : u8
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
	    const lsd::file::path &destination,
	    AssetMetadata asset_metadata,
	    Metadata metadata,
	    Blob code_blob
	);

	ShaderAsset(const lsd::file::path &path);

	void unpack_to(BlobTag tag, lsd::span<byte> destination) const;

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
		debug::ensure(
		    tag == BlobTag::code,
		    "Invalid blob tag for shader asset: {}",
		    lsd::to_underlying(tag)
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

ShaderAsset::ShaderAsset(const lsd::file::path &path): m_stream(path)
{
	debug::ensure(m_stream.is_open(), "Failed to open shader asset at: {}", path.string());
	const auto read = [this](auto &field) {
		m_stream.read(bit_cast<char *>(&field), sizeof(field));
	};

	m_stream.seekg(0, std::ifstream::end);
	const auto file_size = static_cast<size_t>(m_stream.tellg());
	debug::ensure(
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

	debug::ensure(
	    m_asset_metadata.type == asset_type_identifier,
	    "Failed to open shader asset at: {}, incorrect asset type: {} != {}",
	    path.string(),
	    m_asset_metadata.type,
	    asset_type_identifier
	);

	debug::ensure(
	    m_asset_metadata.version == current_version,
	    "Failed to open shader asset at: {}, version mismatch: {} != {}",
	    path.string(),
	    m_asset_metadata.version,
	    current_version
	);

	debug::ensure(
	    lsd::to_underlying(m_metadata.type) <= std::to_underlying(Type::compute),
	    "Failed to open shader asset at: {}, invalid shader type: {}",
	    path.string(),
	    lsd::to_underlying(m_metadata.type)
	);

	debug::ensure(
	    m_code_blob_metadata.tag == lsd::to_underlying(BlobTag::code),
	    "Failed to open shader asset at: {}, invalid blob tag: {}",
	    path.string(),
	    m_code_blob_metadata.tag
	);

	debug::ensure(
	    m_code_blob_metadata.offset + m_code_blob_metadata.compressed_size <= file_size,
	    "Failed to open shader asset at: {}, file smaller than blob: {} > {} + {}",
	    path.string(),
	    file_size,
	    m_code_blob_metadata.offset,
	    m_code_blob_metadata.compressed_size
	);
}

/* static */ void ShaderAsset::pack(
    const lsd::file::path &destination,
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
		.tag = lsd::to_underlying(BlobTag::code),
		.offset = total_metadata_size,
		.compression_type = CompressionType::none,
		.compressed_size = code_blob.size(),
		.uncompressed_size = code_blob.size(),
	};

	debug::ensure(stream.is_open(), "Failed to pack shader asset to {}", destination.string());
	const auto write = [&stream](auto &field) {
		stream.write(bit_cast<char *>(&field), sizeof(field));
	};
	write(asset_metadata.type);
	write(asset_metadata.version);
	write(metadata.type);
	write(code_blob_metadata.tag);
	write(code_blob_metadata.offset);
	write(code_blob_metadata.compression_type);
	write(code_blob_metadata.compressed_size);
	write(code_blob_metadata.uncompressed_size);
	stream.write(bit_cast<char *>(code_blob.data()), static_cast<stream_size>(code_blob.size()));
}

void ShaderAsset::unpack_to(BlobTag tag, lsd::span<byte> destination) const
{
	debug::ensure(
	    tag == BlobTag::code,
	    "Invalid blob tag for shader asset: {}",
	    lsd::to_underlying(tag)
	);

	debug::ensure(
	    destination.size() >= m_code_blob_metadata.uncompressed_size,
	    "Failed to unpack shader blob {} to destination ({}) of size {} since it's smaller "
	    "than the blobl's uncompressed size: {}",
	    lsd::to_underlying(tag),
	    bit_cast<size_t>(destination.data()),
	    destination.size(),
	    m_code_blob_metadata.uncompressed_size
	);

	m_stream.seekg(static_cast<stream_size>(m_code_blob_metadata.offset));
	m_stream.read(
	    bit_cast<char *>(destination.data()),
	    static_cast<stream_size>(m_code_blob_metadata.uncompressed_size)
	);
}

[[nodiscard]] auto ShaderAsset::unpack(BlobTag tag) const -> Blob
{
	debug::ensure(
	    tag == BlobTag::code,
	    "Invalid blob tag for shader asset: {}",
	    lsd::to_underlying(tag)
	);

	auto blob = Blob(m_code_blob_metadata.uncompressed_size);
	unpack_to(tag, blob);

	return blob;
}

} // namespace lt::assets
