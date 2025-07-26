#pragma once

#include <math/vec2.hpp>

struct GLFWwindow;

namespace lt::surface {

class SurfaceComponent
{
public:
	friend class System;

	struct CreateInfo
	{
		std::string_view title;

		math::uvec2 size;

		bool vsync;

		bool visible;
	};

	SurfaceComponent(const CreateInfo &info)
	    : m_title(info.title)
	    , m_size(info.size)
	    , m_vsync(info.vsync)
	    , m_visible(info.visible)
	{
	}

	[[nodiscard]] auto get_title() const -> const std::string_view &
	{
		return m_title;
	}

	[[nodiscard]] auto get_size() const -> const math::uvec2 &
	{
		return m_size;
	}

	[[nodiscard]] auto is_vsync() const -> bool
	{
		return m_vsync;
	}

	[[nodiscard]] auto is_visible() const -> bool
	{
		return m_visible;
	}

	[[nodiscard]] auto get_native_handle() const -> void *
	{
		return m_native_handle;
	}

	[[nodiscard]] auto get_glfw_handle() const -> GLFWwindow *
	{
		return m_glfw_handle;
	}

private:
	std::string_view m_title;

	math::uvec2 m_size;

	bool m_vsync;

	bool m_visible;

	void *m_native_handle {};

	GLFWwindow *m_glfw_handle {};
};

} // namespace lt::surface
