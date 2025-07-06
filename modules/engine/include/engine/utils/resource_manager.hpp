#pragma once

#include <engine/base/base.hpp>

namespace Light {

class Shader;
class Texture;
class SharedContext;

class ResourceManager
{
public:
	static auto create() -> Scope<ResourceManager>;

	static void load_shader(
	    const std::string &name,
	    const std::string &vertexPath,
	    const std::string &pixelPath
	)
	{
		s_context->load_shader_impl(name, vertexPath, pixelPath);
	}

	static void load_texture(
	    const std::string &name,
	    const std::string &path,
	    unsigned int desiredComponents = 4u
	)
	{
		s_context->load_texture_impl(name, path, desiredComponents);
	}

	static void release_texture(const std::string &name)
	{
		s_context->release_texture_impl(name);
	}

	static auto get_shader(const std::string &name) -> Ref<Shader>
	{
		return s_context->m_shaders[name];
	}

	static auto get_texture(const std::string &name) -> Ref<Texture>
	{
		return s_context->m_textures[name];
	}

private:
	static ResourceManager *s_context;

	std::unordered_map<std::string, Ref<Shader>> m_shaders;

	std::unordered_map<std::string, Ref<Texture>> m_textures;

	ResourceManager();

	void load_shader_impl(
	    const std::string &name,
	    const std::string &vertexPath,
	    const std::string &pixelPath
	);

	void load_texture_impl(
	    const std::string &name,
	    const std::string &path,
	    unsigned int desiredComponents = 4u
	);

	void release_texture_impl(const std::string &name);
};

} // namespace Light
