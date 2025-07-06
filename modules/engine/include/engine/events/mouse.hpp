#pragma once

#include <engine/base/base.hpp>
#include <engine/events/event.hpp>
#include <glm/glm.hpp>
#include <sstream>

namespace Light {

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

	event_type(MouseMoved);

	event_category(InputEventCategory | MouseEventCategory);

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

	event_type(WheelScrolled);

	event_category(InputEventCategory | MouseEventCategory);

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

	event_type(ButtonPressed);

	event_category(InputEventCategory | MouseEventCategory);

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

	event_type(ButtonReleased);

	event_category(InputEventCategory | MouseEventCategory);

private:
	const int m_button;
};

} // namespace Light
