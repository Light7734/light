#define STB_IMAGE_IMPLEMENTATION
#include <engine/utils/file_manager.hpp>
#include <stb_image.h>

namespace Light {

basic_file_handle::basic_file_handle(
    uint8_t *data,
    uint32_t size,
    const std::string &path,
    const std::string &name,
    const std::string &extension
)
    : m_data(data)
    , m_size(size)
    , m_path(path)
    , m_name(name)
    , m_extension(extension)
{
}

void basic_file_handle::release()
{
	delete m_data;
	m_data = nullptr;
	m_size = 0ull;
}


basic_file_handle FileManager::read_text_file(const std::string &path)
{
	// parse path info
	std::string name = path.substr(0, path.find('.') + -1);
	std::string extension = path.substr(path.find('.') + 1);

	// open file
	std::ifstream file(path.c_str(), std::ios_base::in | std::ios_base::binary);

	// check
	if (!file)
	{
		lt_log(warn, "Failed to load text file: {}", path);
		file.close();
		return NULL;
	}

	// fetch file size
	file.seekg(0, std::ios::end);
	uint32_t size = file.tellg();
	file.seekg(0, std::ios::beg);

	if (!size)
		lt_log(warn, "Empty text file: {}", path);

	// read file
	uint8_t *data = new uint8_t[size];
	file.read(reinterpret_cast<char *>(data), size);

	file.close();
	return basic_file_handle(data, size, path, name, extension);
}

image_file_handle FileManager::read_image_file(const std::string &path, int32_t desiredComponents)
{
	// parse path info
	std::string name = path.substr(0, path.find('.') + -1);
	std::string extension = path.substr(path.find('.') + 1);

	// load image
	int32_t width = 0, height = 0, fetchedComponents = 0;
	uint8_t *pixels = stbi_load(
	    path.c_str(),
	    &width,
	    &height,
	    &fetchedComponents,
	    desiredComponents
	);

	// check
	if (!pixels)
		lt_log(warn, "Failed to load image file: <{}>", path);
	else if (fetchedComponents != desiredComponents)
		lt_log(warn,
		    "Mismatch of fetched/desired components: <{}> ({}/{})",
		    name + '.' + extension,
		    fetchedComponents,
		    desiredComponents);

	return image_file_handle(
	    pixels,
	    width * height,
	    path,
	    name,
	    extension,
	    width,
	    height,
	    fetchedComponents,
	    desiredComponents
	);
}

void image_file_handle::release()
{
	stbi_image_free(reinterpret_cast<void *>(m_data));
	m_data = nullptr;
	m_size = 0ull;
}


} // namespace Light
