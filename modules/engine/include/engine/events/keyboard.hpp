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

	inline int GetKey() const
	{
		return m_key;
	}

	virtual std::string GetInfoLog() const override
	{
		std::stringstream ss;
		ss << "KeyPressed: " << m_key;
		return ss.str();
	}
	EVENT_TYPE(KeyPressed)
	EVENT_CATEGORY(InputEventCategory | KeyboardEventCategory)
};

class KeyRepeatEvent: public Event
{
private:
	const int m_key;

public:
	KeyRepeatEvent(int key): m_key(key)
	{
	}

	inline int GetKey() const
	{
		return m_key;
	}

	virtual std::string GetInfoLog() const override
	{
		std::stringstream ss;
		ss << "KeyRepeated: " << m_key;
		return ss.str();
	}
	EVENT_TYPE(KeyRepeated)
	EVENT_CATEGORY(InputEventCategory | KeyboardEventCategory)
};

class KeyReleasedEvent: public Event
{
private:
	const int m_key;

public:
	KeyReleasedEvent(int key): m_key(key)
	{
	}

	inline int GetKey() const
	{
		return m_key;
	}

	virtual std::string GetInfoLog() const override
	{
		std::stringstream ss;
		ss << "KeyReleased: " << m_key;
		return ss.str();
	}
	EVENT_TYPE(KeyReleased)
	EVENT_CATEGORY(InputEventCategory | KeyboardEventCategory)
};

} // namespace Light
