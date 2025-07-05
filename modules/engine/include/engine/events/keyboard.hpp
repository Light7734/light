#pragma once

#include <engine/base/base.hpp>
#include <engine/events/event.hpp>
#include <sstream>

namespace Light {

class KeyPressedEvent: public Event
{
private:
	const int m_key;

public:
	KeyPressedEvent(int key): m_key(key)
	{
	}

	inline int get_key() const
	{
		return m_key;
	}

	virtual std::string get_info_lt_log() const override
	{
		std::stringstream ss;
		ss << "KeyPressed: " << m_key;
		return ss.str();
	}
	event_type(KeyPressed)
	event_category(InputEventCategory | KeyboardEventCategory)
};

class KeyRepeatEvent: public Event
{
private:
	const int m_key;

public:
	KeyRepeatEvent(int key): m_key(key)
	{
	}

	inline int get_key() const
	{
		return m_key;
	}

	virtual std::string get_info_lt_log() const override
	{
		std::stringstream ss;
		ss << "KeyRepeated: " << m_key;
		return ss.str();
	}
	event_type(KeyRepeated)
	event_category(InputEventCategory | KeyboardEventCategory)
};

class KeyReleasedEvent: public Event
{
private:
	const int m_key;

public:
	KeyReleasedEvent(int key): m_key(key)
	{
	}

	inline int get_key() const
	{
		return m_key;
	}

	virtual std::string get_info_lt_log() const override
	{
		std::stringstream ss;
		ss << "KeyReleased: " << m_key;
		return ss.str();
	}
	event_type(KeyReleased)
	event_category(InputEventCategory | KeyboardEventCategory)
};

} // namespace Light
