#pragma once

#include <input/events/event.hpp>
#include <sstream>

namespace lt {

class KeyPressedEvent: public Event
{
public:
	KeyPressedEvent(int key): m_key(key)
	{
	}

	[[nodiscard]] auto get_key() const -> int
	{
		return m_key;
	}

	[[nodiscard]] auto get_info_lt_log() const -> std::string override
	{
		std::stringstream ss;
		ss << "KeyPressed: " << m_key;
		return ss.str();
	}

	event_type(KeyPressed);

	event_category(InputEventCategory | KeyboardEventCategory);

private:
	const int m_key;
};

class KeyRepeatEvent: public Event
{
public:
	KeyRepeatEvent(int key): m_key(key)
	{
	}

	[[nodiscard]] auto get_key() const -> int
	{
		return m_key;
	}

	[[nodiscard]] auto get_info_lt_log() const -> std::string override
	{
		std::stringstream ss;
		ss << "KeyRepeated: " << m_key;
		return ss.str();
	}

	event_type(KeyRepeated);

	event_category(InputEventCategory | KeyboardEventCategory);

private:
	const int m_key;
};

class KeyReleasedEvent: public Event
{
public:
	KeyReleasedEvent(int key): m_key(key)
	{
	}

	[[nodiscard]] auto get_key() const -> int
	{
		return m_key;
	}

	[[nodiscard]] auto get_info_lt_log() const -> std::string override
	{
		std::stringstream ss;
		ss << "KeyReleased: " << m_key;
		return ss.str();
	}

	event_type(KeyReleased);

	event_category(InputEventCategory | KeyboardEventCategory);

private:
	const int m_key;
};

} // namespace lt
