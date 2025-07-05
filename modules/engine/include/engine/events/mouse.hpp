#pragma once

#include <engine/base/base.hpp>
#include <engine/events/event.hpp>
#include <glm/glm.hpp>
#include <sstream>

namespace Light {

class MouseMovedEvent: public Event
{
private:
	const glm::vec2 m_position;

public:
	MouseMovedEvent(float x, float y): m_position(x, y)
	{
	}

	inline const glm::vec2 &GetPosition() const
	{
		return m_position;
	}

	inline float get_x() const
	{
		return m_position.x;
	}
	inline float get_y() const
	{
		return m_position.y;
	}

	virtual std::string get_info_lt_log() const override
	{
		std::stringstream ss;
		ss << "MouseMoved: " << m_position.x << ", " << m_position.y;
		return ss.str();
	}
	event_type(MouseMoved)
	event_category(InputEventCategory | MouseEventCategory)
};

class WheelScrolledEvent: public Event
{
private:
	const float m_offset;

public:
	WheelScrolledEvent(float offset): m_offset(offset)
	{
	}

	inline float get_offset() const
	{
		return m_offset;
	}

	virtual std::string get_info_lt_log() const override
	{
		std::stringstream ss;
		ss << "WheelScrolled: " << m_offset;
		return ss.str();
	}
	event_type(WheelScrolled)
	event_category(InputEventCategory | MouseEventCategory)
};

class ButtonPressedEvent: public Event
{
private:
	const int m_button;

public:
	ButtonPressedEvent(int button): m_button(button)
	{
	}

	inline int get_button() const
	{
		return m_button;
	}

	virtual std::string get_info_lt_log() const override
	{
		std::stringstream ss;
		ss << "ButtonPressed: " << m_button;
		return ss.str();
	}
	event_type(ButtonPressed)
	event_category(InputEventCategory | MouseEventCategory)
};

class ButtonReleasedEvent: public Event
{
private:
	const int m_button;

public:
	ButtonReleasedEvent(int button): m_button(button)
	{
	}

	inline int get_button() const
	{
		return m_button;
	}

	virtual std::string get_info_lt_log() const override
	{
		std::stringstream ss;
		ss << "ButtonReleased: " << m_button;
		return ss.str();
	}
	event_type(ButtonReleased)
	event_category(InputEventCategory | MouseEventCategory)
};

} // namespace Light
