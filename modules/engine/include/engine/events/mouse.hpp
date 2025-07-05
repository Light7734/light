#pragma once

#include <engine/base/base.hpp>
#include <engine/events/event.hpp>
#include <glm/glm.hpp>
#include <sstream>

namespace Light {

class MouseMovedEvent: public Event
{
private:
	const glm::vec2 m_Position;

public:
	MouseMovedEvent(float x, float y): m_Position(x, y)
	{
	}

	inline const glm::vec2 &GetPosition() const
	{
		return m_Position;
	}

	inline float GetX() const
	{
		return m_Position.x;
	}
	inline float GetY() const
	{
		return m_Position.y;
	}

	virtual std::string GetInfoLog() const override
	{
		std::stringstream ss;
		ss << "MouseMoved: " << m_Position.x << ", " << m_Position.y;
		return ss.str();
	}
	EVENT_TYPE(MouseMoved)
	EVENT_CATEGORY(InputEventCategory | MouseEventCategory)
};

class WheelScrolledEvent: public Event
{
private:
	const float m_Offset;

public:
	WheelScrolledEvent(float offset): m_Offset(offset)
	{
	}

	inline float GetOffset() const
	{
		return m_Offset;
	}

	virtual std::string GetInfoLog() const override
	{
		std::stringstream ss;
		ss << "WheelScrolled: " << m_Offset;
		return ss.str();
	}
	EVENT_TYPE(WheelScrolled)
	EVENT_CATEGORY(InputEventCategory | MouseEventCategory)
};

class ButtonPressedEvent: public Event
{
private:
	const int m_Button;

public:
	ButtonPressedEvent(int button): m_Button(button)
	{
	}

	inline int GetButton() const
	{
		return m_Button;
	}

	virtual std::string GetInfoLog() const override
	{
		std::stringstream ss;
		ss << "ButtonPressed: " << m_Button;
		return ss.str();
	}
	EVENT_TYPE(ButtonPressed)
	EVENT_CATEGORY(InputEventCategory | MouseEventCategory)
};

class ButtonReleasedEvent: public Event
{
private:
	const int m_Button;

public:
	ButtonReleasedEvent(int button): m_Button(button)
	{
	}

	inline int GetButton() const
	{
		return m_Button;
	}

	virtual std::string GetInfoLog() const override
	{
		std::stringstream ss;
		ss << "ButtonReleased: " << m_Button;
		return ss.str();
	}
	EVENT_TYPE(ButtonReleased)
	EVENT_CATEGORY(InputEventCategory | MouseEventCategory)
};

} // namespace Light
