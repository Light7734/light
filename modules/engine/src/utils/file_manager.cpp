#include <engine/utils/file_manager.hpp>
#include <utility>

namespace Light {

BasicFileHandle::BasicFileHandle(
    uint8_t *data,
    uint32_t size,
    std::string path,
    std::string name,
    std::string extension
)
    : m_data(data)
    , m_size(size)
    , m_path(std::move(path))
    , m_name(std::move(name))
    , m_extension(std::move(extension))
{
}

void BasicFileHandle::release()
{
	delete m_data;
	m_data = nullptr;
	m_size = 0ull;
}

auto FileManager::read_text_file(const std::string &path) -> BasicFileHandle
{
	// parse path info
	auto name = path.substr(0, path.find('.') + -1);
	auto extension = path.substr(path.find('.') + 1);

	// open file
	auto file = std::ifstream { path.c_str(), std::ios_base::in | std::ios_base::binary };

	// check
	if (!file)
	{
		log_wrn("Failed to load text file: {}", path);
		file.close();
		return nullptr;
	}

	// fetch file size
	file.seekg(0, std::ios::end);
	auto size = file.tellg();
	file.seekg(0, std::ios::beg);

	if (!size)
	{
		log_wrn("Empty text file: {}", path);
	}

	// read file
	auto *data = new uint8_t[size];
	file.read(reinterpret_cast<char *>(data), size);

	file.close();
	return { data, static_cast<unsigned int>(size), path, name, extension };
}

} // namespace Light
