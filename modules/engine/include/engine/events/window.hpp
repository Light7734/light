#pragma once

#include <engine/base/base.hpp>
#include <engine/events/event.hpp>
#include <glm/glm.hpp>
#include <sstream>

namespace Light {

class WindowClosedEvent: public Event
{
public:
	virtual std::string GetInfoLog() const override
	{
		return "WindowClosedEvent";
	}
	EVENT_TYPE(WindowClosed)
	EVENT_CATEGORY(WindowEventCategory)
};

class WindowMovedEvent: public Event
{
private:
	const glm::ivec2 m_position;

public:
	WindowMovedEvent(int x, int y): m_position(x, y)
	{
	}

	const glm::ivec2 &GetPosition() const
	{
		return m_position;
	}

	virtual std::string GetInfoLog() const override
	{
		std::stringstream ss;
		ss << "WindwoMoved: " << m_position.x << ", " << m_position.y;
		return ss.str();
		;
	}
	EVENT_TYPE(WindowMoved)
	EVENT_CATEGORY(WindowEventCategory)
};

class WindowResizedEvent: public Event
{
private:
	const glm::uvec2 m_size;

public:
	WindowResizedEvent(unsigned int width, unsigned int height): m_size(width, height)
	{
	}

	const glm::uvec2 &GetSize() const
	{
		return m_size;
	}

	virtual std::string GetInfoLog() const override
	{
		std::stringstream ss;
		ss << "WindowResized: " << m_size.x << ", " << m_size.y;
		return ss.str();
	}
	EVENT_TYPE(WindowResized)
	EVENT_CATEGORY(WindowEventCategory)
};

class WindowLostFocusEvent: public Event
{
public:
	virtual std::string GetInfoLog() const override
	{
		return "WindowLostFocus";
	}
	EVENT_TYPE(WindowLostFocus)
	EVENT_CATEGORY(WindowEventCategory)
};

class WindowGainFocusEvent: public Event
{
public:
	virtual std::string GetInfoLog() const override
	{
		return "WindowGainFocus";
	}
	EVENT_TYPE(WindowGainFocus)
	EVENT_CATEGORY(WindowEventCategory)
};

} // namespace Light
