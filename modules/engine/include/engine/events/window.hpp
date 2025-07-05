#pragma once

#include <engine/base/base.hpp>
#include <engine/events/event.hpp>
#include <glm/glm.hpp>
#include <sstream>

namespace Light {

class WindowClosedEvent: public Event
{
public:
	virtual std::string get_info_lt_log() const override
	{
		return "WindowClosedEvent";
	}

	event_type(WindowClosed);

	event_category(WindowEventCategory);
};

class WindowMovedEvent: public Event
{
public:
	WindowMovedEvent(int x, int y): m_position(x, y)
	{
	}

	const glm::ivec2 &GetPosition() const
	{
		return m_position;
	}

	virtual std::string get_info_lt_log() const override
	{
		std::stringstream ss;
		ss << "WindwoMoved: " << m_position.x << ", " << m_position.y;
		return ss.str();
		;
	}

	event_type(WindowMoved);

	event_category(WindowEventCategory);

private:
	const glm::ivec2 m_position;
};

class WindowResizedEvent: public Event
{
public:
	WindowResizedEvent(unsigned int width, unsigned int height): m_size(width, height)
	{
	}

	const glm::uvec2 &get_size() const
	{
		return m_size;
	}

	virtual std::string get_info_lt_log() const override
	{
		std::stringstream ss;
		ss << "WindowResized: " << m_size.x << ", " << m_size.y;
		return ss.str();
	}

	event_type(WindowResized);

	event_category(WindowEventCategory);

private:
	const glm::uvec2 m_size;
};

class WindowLostFocusEvent: public Event
{
public:
	virtual std::string get_info_lt_log() const override
	{
		return "WindowLostFocus";
	}

	event_type(WindowLostFocus);
	event_category(WindowEventCategory);
};

class WindowGainFocusEvent: public Event
{
public:
	virtual std::string get_info_lt_log() const override
	{
		return "WindowGainFocus";
	}

	event_type(WindowGainFocus);
	event_category(WindowEventCategory);
};

} // namespace Light
