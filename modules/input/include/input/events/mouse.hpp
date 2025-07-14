#pragma once

#include <glm/glm.hpp>
#include <input/events/event.hpp>
#include <sstream>

namespace lt {

class MouseMovedEvent: public Event
{
public:
	MouseMovedEvent(float x, float y): m_position(x, y)
	{
	}

	[[nodiscard]] auto get_position() const -> const glm::vec2 &
	{
		return m_position;
	}

	[[nodiscard]] auto get_x() const -> float
	{
		return m_position.x;
	}

	[[nodiscard]] auto get_y() const -> float
	{
		return m_position.y;
	}

	[[nodiscard]] auto get_info_lt_log() const -> std::string override
	{
		std::stringstream ss;
		ss << "MouseMoved: " << m_position.x << ", " << m_position.y;
		return ss.str();
	}

	[[nodiscard]] auto get_event_type() const -> EventType override
	{
		return ::lt::EventType::MouseMoved;
	}

	[[nodiscard]] auto has_category(EventCategory category) const -> bool override
	{
		return static_cast<uint8_t>(InputEventCategory | MouseEventCategory) & category;
	}

private:
	const glm::vec2 m_position;
};

class WheelScrolledEvent: public Event
{
public:
	WheelScrolledEvent(float offset): m_offset(offset)
	{
	}

	[[nodiscard]] auto get_offset() const -> float
	{
		return m_offset;
	}

	[[nodiscard]] auto get_info_lt_log() const -> std::string override
	{
		std::stringstream ss;
		ss << "WheelScrolled: " << m_offset;
		return ss.str();
	}

	[[nodiscard]] auto get_event_type() const -> EventType override
	{
		return ::lt::EventType::WheelScrolled;
	}

	[[nodiscard]] auto has_category(EventCategory category) const -> bool override
	{
		return static_cast<uint8_t>(InputEventCategory | MouseEventCategory) & category;
	}

private:
	const float m_offset;
};

class ButtonPressedEvent: public Event
{
public:
	ButtonPressedEvent(int button): m_button(button)
	{
	}

	[[nodiscard]] auto get_button() const -> int
	{
		return m_button;
	}

	[[nodiscard]] auto get_info_lt_log() const -> std::string override
	{
		std::stringstream ss;
		ss << "ButtonPressed: " << m_button;
		return ss.str();
	}

	[[nodiscard]] auto get_event_type() const -> EventType override
	{
		return ::lt::EventType::ButtonPressed;
	}

	[[nodiscard]] auto has_category(EventCategory category) const -> bool override
	{
		return static_cast<uint8_t>(InputEventCategory | MouseEventCategory) & category;
	}

private:
	const int m_button;
};

class ButtonReleasedEvent: public Event
{
public:
	ButtonReleasedEvent(int button): m_button(button)
	{
	}

	[[nodiscard]] auto get_button() const -> int
	{
		return m_button;
	}

	[[nodiscard]] auto get_info_lt_log() const -> std::string override
	{
		std::stringstream ss;
		ss << "ButtonReleased: " << m_button;
		return ss.str();
	}

	[[nodiscard]] auto get_event_type() const -> EventType override
	{
		return ::lt::EventType::ButtonReleased;
	}

	[[nodiscard]] auto has_category(EventCategory category) const -> bool override
	{
		return static_cast<uint8_t>(InputEventCategory | MouseEventCategory) & category;
	}

private:
	const int m_button;
};

} // namespace lt
