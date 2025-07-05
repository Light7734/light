#include <engine/graphics/graphics_context.hpp>
#include <engine/graphics/shader.hpp>
#include <engine/graphics/texture.hpp>
#include <engine/utils/file_manager.hpp>
#include <engine/utils/resource_manager.hpp>

namespace Light {

ResourceManager *ResourceManager::s_Context = nullptr;

Scope<ResourceManager> ResourceManager::create()
{
	return make_scope(new ResourceManager());
}

ResourceManager::ResourceManager(): m_shaders {}, m_textures {}
{
	lt_assert(!s_Context, "Repeated singleton construction");
	s_Context = this;
}

void ResourceManager::load_shader_impl(
    const std::string &name,
    const std::string &vertexPath,
    const std::string &pixelPath
)
{
	// check
	lt_assert(s_Context, "Uninitliazed singleton");
	lt_assert(!vertexPath.empty(), "Empty 'vertexPath'");
	lt_assert(!pixelPath.empty(), "Empty 'pixelPath'");

	// load files
	basic_file_handle vertexFile = FileManager::read_text_file(vertexPath);
	basic_file_handle pixelFile = FileManager::read_text_file(pixelPath);

	// check
	lt_assert(vertexFile.is_valid(), "Failed to read vertex file: {}", vertexPath);
	lt_assert(pixelFile.is_valid(), "Failed to read vertex file: {}", pixelPath);

	// create shader
	m_shaders[name] = Ref<Shader>(
	    Shader::create(vertexFile, pixelFile, GraphicsContext::get_shared_context())
	);

	// free file
	vertexFile.release();
	pixelFile.release();
}

void ResourceManager::load_texture_impl(
    const std::string &name,
    const std::string &path,
    unsigned int desiredComponents /* = 4u */
)
{
	lt_assert(s_Context, "Uninitliazed singleton");

	// load file
	image_file_handle imgFile = FileManager::read_image_file(path, desiredComponents);

	// create texture
	m_textures[name] = Ref<Texture>(Texture::create(
	    imgFile.get_width(),
	    imgFile.get_height(),
	    imgFile.get_components(),
	    imgFile.GetData(),
	    GraphicsContext::get_shared_context(),
	    path
	));

	// free file
	imgFile.release();
}

void ResourceManager::release_texture_impl(const std::string &name)
{
	if (!m_textures[name])
	{
		lt_log(warn, "Failed to find texture named: {}", name);
		return;
	}

	m_textures[name] = nullptr;
}

} // namespace Light
