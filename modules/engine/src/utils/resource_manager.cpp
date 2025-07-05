#include <engine/graphics/graphics_context.hpp>
#include <engine/graphics/shader.hpp>
#include <engine/graphics/texture.hpp>
#include <engine/utils/file_manager.hpp>
#include <engine/utils/resource_manager.hpp>

namespace Light {

ResourceManager *ResourceManager::s_Context = nullptr;

Scope<ResourceManager> ResourceManager::Create()
{
	return MakeScope(new ResourceManager());
}

ResourceManager::ResourceManager(): m_Shaders {}, m_Textures {}
{
	ASSERT(!s_Context, "Repeated singleton construction");
	s_Context = this;
}

void ResourceManager::LoadShaderImpl(
    const std::string &name,
    const std::string &vertexPath,
    const std::string &pixelPath
)
{
	// check
	ASSERT(s_Context, "Uninitliazed singleton");
	ASSERT(!vertexPath.empty(), "Empty 'vertexPath'");
	ASSERT(!pixelPath.empty(), "Empty 'pixelPath'");

	// load files
	BasicFileHandle vertexFile = FileManager::ReadTextFile(vertexPath);
	BasicFileHandle pixelFile = FileManager::ReadTextFile(pixelPath);

	// check
	ASSERT(vertexFile.IsValid(), "Failed to read vertex file: {}", vertexPath);
	ASSERT(pixelFile.IsValid(), "Failed to read vertex file: {}", pixelPath);

	// create shader
	m_Shaders[name] = Ref<Shader>(
	    Shader::Create(vertexFile, pixelFile, GraphicsContext::GetSharedContext())
	);

	// free file
	vertexFile.Release();
	pixelFile.Release();
}

void ResourceManager::LoadTextureImpl(
    const std::string &name,
    const std::string &path,
    unsigned int desiredComponents /* = 4u */
)
{
	ASSERT(s_Context, "Uninitliazed singleton");

	// load file
	ImageFileHandle imgFile = FileManager::ReadImageFile(path, desiredComponents);

	// create texture
	m_Textures[name] = Ref<Texture>(Texture::Create(
	    imgFile.GetWidth(),
	    imgFile.GetHeight(),
	    imgFile.GetComponents(),
	    imgFile.GetData(),
	    GraphicsContext::GetSharedContext(),
	    path
	));

	// free file
	imgFile.Release();
}

void ResourceManager::ReleaseTextureImpl(const std::string &name)
{
	if (!m_Textures[name])
	{
		LOG(warn, "Failed to find texture named: {}", name);
		return;
	}

	m_Textures[name] = nullptr;
}

} // namespace Light
