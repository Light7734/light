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

	WindowEventCategory = BIT(0),
	InputEventCategory = BIT(1),
	KeyboardEventCategory = BIT(2),
	MouseEventCategory = BIT(3),
};

#define EVENT_TYPE(type)                    \
	EventType GetEventType() const override \
	{                                       \
		return ::Light::EventType::type;    \
	}
#define EVENT_CATEGORY(eCategory)                                  \
	inline bool HasCategory(EventCategory category) const override \
	{                                                              \
		return (eCategory) & category;                             \
	}

class Event
{
public:
	virtual EventType GetEventType() const = 0;
	virtual std::string GetInfoLog() const = 0;
	virtual bool HasCategory(EventCategory category) const = 0;

	friend std::ostream &operator<<(std::ostream &os, const Event &e)
	{
		return os << e.GetInfoLog();
	}
};

} // namespace Light
