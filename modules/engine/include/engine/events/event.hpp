#pragma once

#include <engine/base/base.hpp>

namespace Light {

enum class EventType
{
	None = 0,

	// input
	MouseMoved,
	WheelScrolled,
	ButtonPressed,
	ButtonReleased,
	KeyPressed,
	KeyRepeated,
	KeyReleased,
	SetChar,

	// window
	WindowMoved,
	WindowResized,
	WindowClosed,
	WindowLostFocus,
	WindowGainFocus,
};

enum EventCategory
{
	None = 0,

	WindowEventCategory = bit(0),
	InputEventCategory = bit(1),
	KeyboardEventCategory = bit(2),
	MouseEventCategory = bit(3),
};

#define event_type(type)                    \
	EventType get_event_type() const override \
	{                                       \
		return ::Light::EventType::type;    \
	}
#define event_category(eCategory)                                  \
	inline bool has_category(EventCategory category) const override \
	{                                                              \
		return (eCategory) & category;                             \
	}

class Event
{
public:
	virtual EventType get_event_type() const = 0;
	virtual std::string get_info_lt_log() const = 0;
	virtual bool has_category(EventCategory category) const = 0;

	friend std::ostream &operator<<(std::ostream &os, const Event &e)
	{
		return os << e.get_info_lt_log();
	}
};

} // namespace Light
