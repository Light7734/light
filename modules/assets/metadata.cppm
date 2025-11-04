export module assets.metadata;
import std;

export namespace lt::assets {

using Type_T = std::array<const char, 16>;

using Tag_T = std::uint8_t;

using Version = std::uint8_t;

using Blob = std::vector<std::byte>;

constexpr auto current_version = Version { 1u };

enum class CompressionType : std::uint8_t
{
	none,
	lz4,
	lz4_hc,
};

struct AssetMetadata
{
	Version version;

	Type_T type;
};

struct BlobMetadata
{
	Tag_T tag;

	std::size_t offset;

	CompressionType compression_type;

	std::size_t compressed_size;

	std::size_t uncompressed_size;
};

} // namespace lt::assets
