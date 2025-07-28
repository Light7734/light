#pragma once

#include <math/vec2.hpp>
#include <surface/events/keyboard.hpp>
#include <surface/events/mouse.hpp>
#include <surface/events/surface.hpp>
#include <variant>

struct GLFWwindow;

namespace lt::surface {

/** Represents a platform's surface (eg. a Window).
 *
 * @note Read-only component, should only be modified through a system.
 */
class SurfaceComponent
{
public:
	friend class System;

	using Event = std::variant<
	    // surface events
	    ClosedEvent,
	    MovedEvent,
	    ResizedEvent,
	    LostFocusEvent,
	    GainFocusEvent,

	    // keyboard events
	    KeyPressedEvent,
	    KeyRepeatEvent,
	    KeyReleasedEvent,
	    KeySetCharEvent,

	    // mouse events
	    MouseMovedEvent,
	    WheelScrolledEvent,
	    ButtonPressedEvent,
	    ButtonReleasedEvent>;

	using EventCallback = std::function<bool(const Event &)>;

	using WindowsNativeHandle = void *;

	using X11NativeHandle = unsigned long;

	using NativeHandle = std::variant<WindowsNativeHandle, X11NativeHandle>;

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

	[[nodiscard]] auto get_native_handle() const -> NativeHandle
	{
		return m_native_handle;
	}

private:
	[[nodiscard]] auto get_glfw_handle() const -> GLFWwindow *
	{
		return m_glfw_handle;
	}

	std::string_view m_title;

	math::uvec2 m_size;

	bool m_vsync;

	bool m_visible;

	NativeHandle m_native_handle;

	GLFWwindow *m_glfw_handle {};

	std::vector<EventCallback> m_event_callbacks;
};

} // namespace lt::surface
