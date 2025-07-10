#include <asset_manager/asset_manager.hpp>
#include <asset_parser/assets/text.hpp>
#include <asset_parser/assets/texture.hpp>
#include <logger/logger.hpp>
#include <renderer/graphics_context.hpp>
#include <renderer/shader.hpp>
#include <renderer/texture.hpp>

namespace Light {

/* static */ auto AssetManager::instance() -> AssetManager &
{
	static auto instance = AssetManager {};
	return instance;
}

void AssetManager::load_shader_impl(
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

		m_shaders[name] = Ref<Shader>(Shader::create(
		    get_or_load_text_asset(vertex_path.string()),
		    get_or_load_text_asset(pixel_path),
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

void AssetManager::load_texture_impl(const std::string &name, const std::filesystem::path &path)
{
	try
	{
		log_trc("Loading texture:");
		log_trc("\tname: {}", name);
		log_trc("\tpath: {}", path.string());

		m_textures[name] = Ref<Texture>(
		    Texture::create(get_or_load_texture_asset(path), GraphicsContext::get_shared_context())
		);
	}
	catch (const std::exception &exp)
	{
		log_err("Failed to load texture:");
		log_err("\tname     : {}", name);
		log_err("\tpath     : {}", path.string());
		log_err("\texception: {}", exp.what());
	}
}

auto AssetManager::get_or_load_text_asset(const std::filesystem::path &path)
    -> Ref<Assets::TextAsset>
{
	const auto key = std::filesystem::canonical(path).string();
	if (!m_text_assets.contains(key))
	{
		m_text_assets.emplace(key, create_ref<Assets::TextAsset>(path));
	}

	return m_text_assets[key];
}

auto AssetManager::get_or_load_texture_asset(const std::filesystem::path &path)
    -> Ref<Assets::TextureAsset>
{
	const auto key = std::filesystem::canonical(path).string();
	if (!m_texture_assets.contains(key))
	{
		m_texture_assets.emplace(key, create_ref<Assets::TextureAsset>(path));
	}

	return m_texture_assets[key];
}


} // namespace Light
