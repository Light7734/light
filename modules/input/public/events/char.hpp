#pragma once

#include <input/events/event.hpp>
#include <sstream>

namespace lt {

class SetCharEvent: public Event
{
public:
	SetCharEvent(unsigned int character): m_character(character)
	{
	}

	[[nodiscard]] auto get_character() const -> int
	{
		return m_character;
	}

	[[nodiscard]] auto get_info_lt_log() const -> std::string override
	{
		std::stringstream ss;
		ss << "CharSet: " << m_character;
		return ss.str();
	}

	[[nodiscard]] auto get_event_type() const -> EventType override
	{
		return ::lt::EventType::SetChar;
	}

	[[nodiscard]] auto has_category(EventCategory category) const -> bool override
	{
		return static_cast<uint8_t>(InputEventCategory | KeyboardEventCategory) & category;
	}

private:
	const unsigned int m_character;
};

} // namespace lt
