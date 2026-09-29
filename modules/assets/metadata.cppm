export module assets.metadata;

import preliminary;

export namespace lt::assets {

/** Asset type identifier is 16 characters after the first 1 byte which refers to the version.
 * | 1 byte  | 16 bytes              | ... |
 *   version   asset type identifier
 */
using Type_T = std::array<const char, 16>;

/** Tag type */
using Tag_T = u8;

/** Version type */
using Version = u8;

/** A blob is simply a bunch of bytes. */
using Blob = std::vector<byte>;

/** The current version of the assets module, gets baked into the asset's metadata. */
constexpr auto current_version = Version { 1u };

/** The comrpession used in a blob of data. */
enum class CompressionType : u8
{
	none,
	lz4,
	lz4_hc,
};

/** The asset's metadata, containing a 16 character long type identifier and an asset version. */
struct AssetMetadata
{
	Version version;

	Type_T type;
};

/** The metadata of a blob of data, eg. the pixels of an image, or the normals of a model. */
struct BlobMetadata
{
	Tag_T tag;

	size_t offset;

	CompressionType compression_type;

	size_t compressed_size;

	size_t uncompressed_size;
};

} // namespace lt::assets
