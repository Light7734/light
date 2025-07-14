#pragma once

namespace lt {

enum class EventType : uint8_t
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

enum EventCategory : uint8_t
{
	None = 0,

	WindowEventCategory = bit(0),
	InputEventCategory = bit(1),
	KeyboardEventCategory = bit(2),
	MouseEventCategory = bit(3),
};

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

} // namespace lt
