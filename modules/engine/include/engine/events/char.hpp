#pragma once

#include <engine/base/base.hpp>
#include <engine/events/event.hpp>
#include <sstream>

namespace Light {

class SetCharEvent: public Event
{
private:
	const unsigned int m_character;

public:
	SetCharEvent(unsigned int character): m_character(character)
	{
	}

	inline int get_character() const
	{
		return m_character;
	}

	virtual std::string get_info_lt_log() const override
	{
		std::stringstream ss;
		ss << "CharSet: " << m_character;
		return ss.str();
	}
	event_type(SetChar)
	event_category(InputEventCategory | KeyboardEventCategory)
};

} // namespace Light
