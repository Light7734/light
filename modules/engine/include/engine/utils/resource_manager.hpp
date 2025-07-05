#pragma once

#include <engine/base/base.hpp>

namespace Light {

class Shader;
class Texture;

class SharedContext;

class ResourceManager /* singleton */
{
private:
	static ResourceManager *s_Context;

private:
	std::unordered_map<std::string, Ref<Shader>> m_shaders;
	std::unordered_map<std::string, Ref<Texture>> m_textures;

public:
	static Scope<ResourceManager> Create();

	// #todo: add geometry shader support
	static inline void LoadShader(
	    const std::string &name,
	    const std::string &vertexPath,
	    const std::string &pixelPath
	)
	{
		s_Context->LoadShaderImpl(name, vertexPath, pixelPath);
	}

	static inline void LoadTexture(
	    const std::string &name,
	    const std::string &path,
	    unsigned int desiredComponents = 4u
	)
	{
		s_Context->LoadTextureImpl(name, path, desiredComponents);
	}

	static inline void ReleaseTexture(const std::string &name)
	{
		s_Context->ReleaseTextureImpl(name);
	}

	static inline Ref<Shader> GetShader(const std::string &name)
	{
		return s_Context->m_shaders[name];
	}
	static inline Ref<Texture> GetTexture(const std::string &name)
	{
		return s_Context->m_textures[name];
	}

private:
	ResourceManager();

	void LoadShaderImpl(
	    const std::string &name,
	    const std::string &vertexPath,
	    const std::string &pixelPath
	);

	void LoadTextureImpl(
	    const std::string &name,
	    const std::string &path,
	    unsigned int desiredComponents = 4u
	);

	void ReleaseTextureImpl(const std::string &name);
};

} // namespace Light
