#pragma once

#include <filesystem>

namespace Assets {

class TextAsset;

class TextureAsset;

} // namespace Assets

namespace lt {

class Shader;
class Texture;

/**
 * Asset is the data on the disk.
 * Resource is the data on the gpu/cpu
 *
 * eg. TextureAsset is the file on the disk
 * eg. Texture is the representation of it in the GPU
 */
class AssetManager
{
public:
	static void load_shader(
	    const std::string &name,
	    const std::filesystem::path &vertex_path,
	    const std::filesystem::path &pixel_path
	)
	{
		instance().load_shader_impl(name, vertex_path, pixel_path);
	}

	static void load_texture(const std::string &name, const std::filesystem::path &path)
	{
		instance().load_texture_impl(name, path);
	}

	static auto get_shader(const std::string &name) -> Ref<Shader>
	{
		return instance().m_shaders[name];
	}

	static auto get_texture(const std::string &name) -> Ref<Texture>
	{
		return instance().m_textures[name];
	}

private:
	AssetManager() = default;

	static auto instance() -> AssetManager &;

	void load_shader_impl(
	    const std::string &name,
	    const std::filesystem::path &vertex_path,
	    const std::filesystem::path &pixel_path
	);

	void load_texture_impl(const std::string &name, const std::filesystem::path &path);

	auto get_or_load_text_asset(const std::filesystem::path &path) -> Ref<Assets::TextAsset>;

	auto get_or_load_texture_asset(const std::filesystem::path &path) -> Ref<Assets::TextureAsset>;

	std::unordered_map<std::string, Ref<Assets::TextAsset>> m_text_assets;

	std::unordered_map<std::string, Ref<Assets::TextureAsset>> m_texture_assets;

	std::unordered_map<std::string, Ref<Shader>> m_shaders;

	std::unordered_map<std::string, Ref<Texture>> m_textures;
};

} // namespace lt
