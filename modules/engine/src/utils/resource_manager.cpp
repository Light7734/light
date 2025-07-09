#include <asset_parser/assets/text.hpp>
#include <asset_parser/assets/texture.hpp>
#include <engine/graphics/graphics_context.hpp>
#include <engine/graphics/shader.hpp>
#include <engine/graphics/texture.hpp>
#include <engine/utils/resource_manager.hpp>
#include <logger/logger.hpp>

namespace Light {

void ResourceManager::load_shader_impl(
    const std::string &name,
    const std::filesystem::path &vertex_path,
    const std::filesystem::path &pixel_path
)
{
	try
	{
		log_trc("Loading shader:");
		log_trc("\tname       : {}", name);
		log_trc("\tvertex path: {}", vertex_path.string());
		log_trc("\tpixel path : {}", pixel_path.string());

		auto vertex_asset = Assets::TextAsset { vertex_path };
		auto pixel_asset = Assets::TextAsset { pixel_path };

		auto vertex_blob_metadata = vertex_asset.get_blob_metadata(Assets::BlobMetadata::Tag::text);
		auto pixel_blob_metadata = pixel_asset.get_blob_metadata(Assets::BlobMetadata::Tag::text);

		auto vertex_blob = Assets::Blob(vertex_blob_metadata.uncompressed_size);
		auto pixel_blob = Assets::Blob(pixel_blob_metadata.uncompressed_size);

		vertex_asset.unpack_blob(vertex_blob_metadata.tag, vertex_blob.data(), vertex_blob.size());
		pixel_asset.unpack_blob(pixel_blob_metadata.tag, pixel_blob.data(), pixel_blob.size());

		m_shaders[name] = Ref<Shader>(Shader::create(
		    std::move(vertex_blob),
		    std::move(pixel_blob),
		    GraphicsContext::get_shared_context()
		));
	}
	catch (const std::exception &exp)
	{
		log_err("Failed to load shader:");
		log_err("\tname       : {}", name);
		log_err("\tvertex path: {}", vertex_path.string());
		log_err("\tpixel path : {}", pixel_path.string());
		log_err("\texception  : {}", exp.what());
	}
}

void ResourceManager::load_texture_impl(const std::string &name, const std::filesystem::path &path)
{
	try
	{
		log_trc("Loading texture:");
		log_trc("\tname: {}", name);
		log_trc("\tpath: {}", path.string());

		auto asset = Assets::TextureAsset { path };
		const auto metadata = asset.get_metadata();
		const auto blob_metadata = asset.get_blob_metadata(Assets::BlobMetadata::Tag::color);

		auto blob = std::vector<std::byte>(blob_metadata.uncompressed_size);
		asset.unpack_blob(blob_metadata.tag, blob.data(), blob.size());

		m_textures[name] = Ref<Texture>(Texture::create(
		    metadata.pixel_size[0],
		    metadata.pixel_size[1],
		    metadata.num_components,
		    std::bit_cast<unsigned char *>(blob.data()),
		    GraphicsContext::get_shared_context(),
		    path
		));
	}
	catch (const std::exception &exp)
	{
		log_err("Failed to load texture:");
		log_err("\tname     : {}", name);
		log_err("\tpath     : {}", path.string());
		log_err("\texception: {}", exp.what());
	}
}

} // namespace Light
