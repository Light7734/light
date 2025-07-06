#pragma once

#include <engine/base/base.hpp>

namespace Light {

class BasicFileHandle
{
public:
virtual ~BasicFileHandle() = default;
	BasicFileHandle(
	    uint8_t *data = nullptr,
	    uint32_t size = 0ull,
	    std::string path = "",
	    std::string name = "",
	    std::string extension = ""
	);

	virtual void release();

	auto get_data() -> uint8_t *
	{
		return m_data;
	}

	auto get_size() const -> uint32_t
	{
		return m_size;
	}

	auto get_path() -> const std::string &
	{
		return m_path;
	}

	auto get_name() -> const std::string &
	{
		return m_name;
	}

	auto get_extension() -> const std::string &
	{
		return m_extension;
	}

	auto get_name_with_extention() -> const std::string &
	{
		return m_name + '.' + m_extension;
	}

	[[nodiscard]] auto is_valid() const -> bool
	{
		return !!m_data;
	}

	operator bool() const
	{
		return is_valid();
	}

protected:
	// made protected for custom free():
	uint8_t *m_data;

	uint32_t m_size;

private:
	const std::string m_path;

	const std::string m_name;

	const std::string m_extension;
};

class ImageFileHandle: public BasicFileHandle
{
public:
virtual ~ImageFileHandle() = default;
	ImageFileHandle(
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
	    : BasicFileHandle(data, size, path, name, extension)
	    , m_width(width)
	    , m_height(height)
	    , m_components(components)
	    , m_desired_components(desiredComponents)
	{
	}

	void release() override;

	[[nodiscard]] auto get_width() const -> uint32_t
	{
		return m_width;
	}

	[[nodiscard]] auto get_height() const -> uint32_t
	{
		return m_height;
	}

	[[nodiscard]] auto get_components() const -> uint32_t
	{
		return m_components;
	}

	[[nodiscard]] auto get_desired_components() const -> uint32_t
	{
		return m_desired_components;
	}

private:
	uint32_t m_width;

	uint32_t m_height;

	uint32_t m_components;

	uint32_t m_desired_components;
};

class FileManager
{
public:
	static auto read_text_file(const std::string &path) -> BasicFileHandle;

	static auto read_image_file(const std::string &path, int32_t desiredComponents)
	    -> ImageFileHandle;
};

} // namespace Light
