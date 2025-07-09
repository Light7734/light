#include <asset_parser/assets/texture.hpp>
#include <asset_parser/parser.hpp>
#include <engine/graphics/graphics_context.hpp>
#include <engine/graphics/shader.hpp>
#include <engine/graphics/texture.hpp>
#include <engine/utils/file_manager.hpp>
#include <engine/utils/resource_manager.hpp>

namespace Light {

void ResourceManager::load_shader_impl(
    const std::string &name,
    const std::string &vertexPath,
    const std::string &pixelPath
)
{
	lt_assert(!vertexPath.empty(), "Empty 'vertexPath'");
	lt_assert(!pixelPath.empty(), "Empty 'pixelPath'");

	auto vertexFile = FileManager::read_text_file(vertexPath);
	auto pixelFile = FileManager::read_text_file(pixelPath);

	lt_assert(vertexFile.is_valid(), "Failed to read vertex file: {}", vertexPath);
	lt_assert(pixelFile.is_valid(), "Failed to read vertex file: {}", pixelPath);

	m_shaders[name] = Ref<Shader>(
	    Shader::create(vertexFile, pixelFile, GraphicsContext::get_shared_context())
	);

	vertexFile.release();
	pixelFile.release();
}

void ResourceManager::load_texture_impl(const std::string &name, const std::filesystem::path &path)
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

void ResourceManager::release_texture_impl(const std::string &name)
{
	if (!m_textures[name])
	{
		log_wrn("Failed to find texture named: {}", name);
		return;
	}

	m_textures[name] = nullptr;
}

} // namespace Light
