#pragma once

#include <engine/base/base.hpp>

namespace Light {

class BasicFileHandle
{
public:
	BasicFileHandle(
	    uint8_t *data = nullptr,
	    uint32_t size = 0ull,
	    const std::string &path = "",
	    const std::string &name = "",
	    const std::string &extension = ""
	);

	virtual void Release();

	// getters
	inline uint8_t *GetData()
	{
		return m_data;
	}
	inline uint32_t GetSize()
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

	inline bool IsValid() const
	{
		return !!m_data;
	}

	// operators
	inline operator bool() const
	{
		return IsValid();
	}

protected:
	// made protected for custom Free():
	uint8_t *m_data;
	uint32_t m_size;

private:
	const std::string m_path, m_name, m_extension;
};

class ImageFileHandle: public BasicFileHandle
{
public:
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

	void Release() override;

	// getters
	inline uint32_t GetWidth() const
	{
		return m_width;
	}
	inline uint32_t GetHeight() const
	{
		return m_height;
	}
	inline uint32_t GetComponents() const
	{
		return m_components;
	}
	inline uint32_t GetDesiredComponents() const
	{
		return m_desired_components;
	}

private:
	uint32_t m_width, m_height, m_components, m_desired_components;
};

class FileManager
{
public:
	static BasicFileHandle ReadTextFile(const std::string &path);
	static ImageFileHandle ReadImageFile(const std::string &path, int32_t desiredComponents);
};

} // namespace Light
