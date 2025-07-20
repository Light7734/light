#pragma once

#include <input/events/event.hpp>
#include <math/vec2.hpp>
#include <sstream>

namespace lt {

class WindowClosedEvent: public Event
{
public:
	[[nodiscard]] auto get_info_lt_log() const -> std::string override
	{
		return "WindowClosedEvent";
	}

	[[nodiscard]] auto get_event_type() const -> EventType override
	{
		return ::lt::EventType::WindowClosed;
	}

	[[nodiscard]] auto has_category(EventCategory category) const -> bool override
	{
		return static_cast<uint8_t>(WindowEventCategory) & category;
	}
};

class WindowMovedEvent: public Event
{
public:
	WindowMovedEvent(int x, int y): m_position(x, y)
	{
	}

	[[nodiscard]] auto get_position() const -> const math::ivec2 &
	{
		return m_position;
	}

	[[nodiscard]] auto get_info_lt_log() const -> std::string override
	{
		std::stringstream ss;
		ss << "WindwoMoved: " << m_position.x << ", " << m_position.y;
		return ss.str();
		;
	}

	[[nodiscard]] auto get_event_type() const -> EventType override
	{
		return ::lt::EventType::WindowMoved;
	}

	[[nodiscard]] auto has_category(EventCategory category) const -> bool override
	{
		return static_cast<uint8_t>(WindowEventCategory) & category;
	}

private:
	const math::ivec2 m_position;
};

class WindowResizedEvent: public Event
{
public:
	WindowResizedEvent(unsigned int width, unsigned int height): m_size(width, height)
	{
	}

	[[nodiscard]] auto get_size() const -> const math::uvec2 &
	{
		return m_size;
	}

	[[nodiscard]] auto get_info_lt_log() const -> std::string override
	{
		std::stringstream ss;
		ss << "WindowResized: " << m_size.x << ", " << m_size.y;
		return ss.str();
	}

	[[nodiscard]] auto get_event_type() const -> EventType override
	{
		return ::lt::EventType::WindowResized;
	}

	[[nodiscard]] auto has_category(EventCategory category) const -> bool override
	{
		return static_cast<uint8_t>(WindowEventCategory) & category;
	}

private:
	const math::uvec2 m_size;
};

class WindowLostFocusEvent: public Event
{
public:
	[[nodiscard]] auto get_info_lt_log() const -> std::string override
	{
		return "WindowLostFocus";
	}

	[[nodiscard]] auto get_event_type() const -> EventType override
	{
		return ::lt::EventType::WindowLostFocus;
	}

	[[nodiscard]] auto has_category(EventCategory category) const -> bool override
	{
		return static_cast<uint8_t>(WindowEventCategory) & category;
	}
};

class WindowGainFocusEvent: public Event
{
public:
	[[nodiscard]] auto get_info_lt_log() const -> std::string override
	{
		return "WindowGainFocus";
	}

	[[nodiscard]] auto get_event_type() const -> EventType override
	{
		return ::lt::EventType::WindowGainFocus;
	}

	[[nodiscard]] auto has_category(EventCategory category) const -> bool override
	{
		return static_cast<uint8_t>(WindowEventCategory) & category;
	}
};

} // namespace lt
