#pragma once

#include <engine/base/base.hpp>
#include <filesystem>

namespace Light {

class Shader;
class Texture;
class SharedContext;

class ResourceManager
{
public:
	static auto instance() -> ResourceManager &
	{
		static auto instance = ResourceManager {};
		return instance;
	}

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
	ResourceManager() = default;

	void load_shader_impl(
	    const std::string &name,
	    const std::filesystem::path &vertex_path,
	    const std::filesystem::path &pixel_path
	);

	void load_texture_impl(const std::string &name, const std::filesystem::path &path);

	std::unordered_map<std::string, Ref<Shader>> m_shaders;

	std::unordered_map<std::string, Ref<Texture>> m_textures;
};

} // namespace Light
