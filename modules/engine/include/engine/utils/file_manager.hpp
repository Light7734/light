#pragma once

#include <engine/base/base.hpp>

namespace Light {

class basic_file_handle
{
public:
	basic_file_handle(
	    uint8_t *data = nullptr,
	    uint32_t size = 0ull,
	    const std::string &path = "",
	    const std::string &name = "",
	    const std::string &extension = ""
	);

	virtual void release();

	// getters
	inline uint8_t *GetData()
	{
		return m_data;
	}
	inline uint32_t get_size()
	{
		return m_size;
	}

	inline const std::string &GetPath()
	{
		return m_path;
	}
	inline const std::string &GetName()
	{
		return m_name;
	}
	inline const std::string &GetExtension()
	{
		return m_extension;
	}

	inline const std::string &GetNameWithExtension()
	{
		return m_name + '.' + m_extension;
	}

	inline bool is_valid() const
	{
		return !!m_data;
	}

	// operators
	inline operator bool() const
	{
		return is_valid();
	}

protected:
	// made protected for custom free():
	uint8_t *m_data;
	uint32_t m_size;

private:
	const std::string m_path, m_name, m_extension;
};

class image_file_handle: public basic_file_handle
{
public:
	image_file_handle(
	    uint8_t *data,
	    uint32_t size,
	    const std::string &path,
	    const std::string &name,
	    const std::string &extension,
	    uint32_t width,
	    uint32_t height,
	    uint32_t components,
	    uint32_t desiredComponents
	)
	    : basic_file_handle(data, size, path, name, extension)
	    , m_width(width)
	    , m_height(height)
	    , m_components(components)
	    , m_desired_components(desiredComponents)
	{
	}

	void release() override;

	// getters
	inline uint32_t get_width() const
	{
		return m_width;
	}
	inline uint32_t get_height() const
	{
		return m_height;
	}
	inline uint32_t get_components() const
	{
		return m_components;
	}
	inline uint32_t get_desired_components() const
	{
		return m_desired_components;
	}

private:
	uint32_t m_width, m_height, m_components, m_desired_components;
};

class FileManager
{
public:
	static basic_file_handle read_text_file(const std::string &path);
	static image_file_handle read_image_file(const std::string &path, int32_t desiredComponents);
};

} // namespace Light
