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

private:
	// made protected for custom free():
	uint8_t *m_data;

	uint32_t m_size;

	const std::string m_path;

	const std::string m_name;

	const std::string m_extension;
};

class FileManager
{
public:
	static auto read_text_file(const std::string &path) -> BasicFileHandle;
};

} // namespace Light
