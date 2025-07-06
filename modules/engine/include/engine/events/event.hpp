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

#define event_type(type)                      \
	EventType get_event_type() const override \
	{                                         \
		return ::Light::EventType::type;      \
	}

#define event_category(eCategory)                                   \
	inline bool has_category(EventCategory category) const override \
	{                                                               \
		return (eCategory) & category;                              \
	}

class Event
{
public:
	Event() = default;

	virtual ~Event() = default;

	[[nodiscard]] virtual auto get_event_type() const -> EventType = 0;

	[[nodiscard]] virtual auto get_info_lt_log() const -> std::string = 0;

	[[nodiscard]] virtual auto has_category(EventCategory category) const -> bool = 0;

	friend auto operator<<(std::ostream &os, const Event &e) -> std::ostream &
	{
		return os << e.get_info_lt_log();
	}
};

} // namespace Light
