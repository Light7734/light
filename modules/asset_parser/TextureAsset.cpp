#include "TextureAsset.hpp"

#include <lz4.h>
#include <nlohmann/json.hpp>

namespace Assets {

using namespace nlohmann;

TextureInfo read_texture_info(AssetFile* file)
{
	json texture_meta_data = json::parse(file->json);

	return TextureInfo {
		.size            = texture_meta_data["bufferSize"],
		.compression_mode = texture_meta_data["compression"],
		.format          = texture_meta_data["format"],
		.pixel_size      = {
		         texture_meta_data["width"],
		         texture_meta_data["height"],
		         0,
        },
		.original_file = texture_meta_data["originalFile"],
	};
}

void unpack_texture(
  TextureInfo* info,
  const void* source_buffer,
  size_t source_size,
  void* destination
)
{
	if (info->compression_mode == CompressionMode::LZ4)
	{
		LZ4_decompress_safe(
		  (const char*)source_buffer,
		  (char*)destination,
		  source_size,
		  info->size
		);
	}
	else
	{
		memcpy(destination, source_buffer, source_size);
	}
}

AssetFile pack_texture(TextureInfo* info, void* pixel_data)
{
	json metadata;
	metadata["format"]       = info->format;
	metadata["width"]        = info->pixel_size[0];
	metadata["height"]       = info->pixel_size[1];
	metadata["bufferSize"]   = info->size;
	metadata["originalFile"] = info->original_file;
	metadata["compression"]  = CompressionMode::LZ4;

	AssetFile file;
	file.type    = AssetFile::Type::Texture;
	file.version = 1u;

	const int compress_staging = LZ4_compressBound(info->size);
	file.blob.resize(compress_staging);
	const int compression_size = LZ4_compress_default(
	  (const char*)pixel_data,
	  (char*)file.blob.data(),
	  info->size,
	  compress_staging
	);
	file.blob.resize(compression_size);


	metadata["compression"] = CompressionMode::LZ4;

	file.json = metadata.dump();

	return file;
}

} // namespace Assets
