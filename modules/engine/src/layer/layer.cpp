#include <engine/events/char.hpp>
#include <engine/events/event.hpp>
#include <engine/events/keyboard.hpp>
#include <engine/events/mouse.hpp>
#include <engine/events/window.hpp>
#include <engine/layer/layer.hpp>

namespace Light {

Layer::Layer(std::string name): m_layer_name(std::move(name))
{
}

auto Layer::on_event(const Event &event) -> bool
{
	switch (event.get_event_type())
	{
	case EventType::MouseMoved: return on_mouse_moved(dynamic_cast<const MouseMovedEvent &>(event));
	case EventType::ButtonPressed:
		return on_button_pressed(dynamic_cast<const ButtonPressedEvent &>(event));
	case EventType::ButtonReleased:
		return on_button_released(dynamic_cast<const ButtonReleasedEvent &>(event));
	case EventType::WheelScrolled:
		return on_wheel_scrolled(dynamic_cast<const WheelScrolledEvent &>(event));

	case EventType::KeyPressed: return on_key_pressed(dynamic_cast<const KeyPressedEvent &>(event));
	case EventType::KeyRepeated: return on_key_repeat(dynamic_cast<const KeyRepeatEvent &>(event));
	case EventType::KeyReleased:
		return on_key_released(dynamic_cast<const KeyReleasedEvent &>(event));
	case EventType::SetChar: return on_set_char(dynamic_cast<const SetCharEvent &>(event));

	case EventType::WindowClosed:
		return on_window_closed(dynamic_cast<const WindowClosedEvent &>(event));
	case EventType::WindowResized:
		return on_window_resized(dynamic_cast<const WindowResizedEvent &>(event));
	case EventType::WindowMoved:
		return on_window_moved(dynamic_cast<const WindowMovedEvent &>(event));
	case EventType::WindowLostFocus:
		return on_window_lost_focus(dynamic_cast<const WindowLostFocusEvent &>(event));
	case EventType::WindowGainFocus:
		return on_window_gain_focus(dynamic_cast<const WindowGainFocusEvent &>(event));

	default: lt_assert(false, "Invalid event: {}", event.get_info_lt_log());
	}
}

} // namespace Light
