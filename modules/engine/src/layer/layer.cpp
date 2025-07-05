#include <engine/events/char.hpp>
#include <engine/events/event.hpp>
#include <engine/events/keyboard.hpp>
#include <engine/events/mouse.hpp>
#include <engine/events/window.hpp>
#include <engine/layer/layer.hpp>

namespace Light {

Layer::Layer(const std::string &name): m_layer_name(name)
{
}

bool Layer::on_event(const Event &event)
{
	switch (event.get_event_type())
	{
	/* mouse */
	// cursor
	case EventType::MouseMoved: return on_mouse_moved((MouseMovedEvent &)event);
	// button
	case EventType::ButtonPressed: return on_button_pressed((ButtonPressedEvent &)event);
	case EventType::ButtonReleased: return on_button_released((ButtonReleasedEvent &)event);
	// wheel
	case EventType::WheelScrolled: return on_wheel_scrolled((WheelScrolledEvent &)event);

	/* keyboard */
	// key
	case EventType::KeyPressed: return on_key_pressed((KeyPressedEvent &)event);
	case EventType::KeyRepeated: return on_key_repeat((KeyRepeatEvent &)event);
	case EventType::KeyReleased: return on_key_released((KeyReleasedEvent &)event);
	// char
	case EventType::SetChar: return on_set_char((SetCharEvent &)event);

	/* window */
	// termination
	case EventType::WindowClosed: return on_window_closed((WindowClosedEvent &)event);
	// size/position
	case EventType::WindowResized: return on_window_resized((WindowResizedEvent &)event);
	case EventType::WindowMoved: return on_window_moved((WindowMovedEvent &)event);
	// focus
	case EventType::WindowLostFocus: return on_window_lost_focus((WindowLostFocusEvent &)event);
	case EventType::WindowGainFocus: return on_window_gain_focus((WindowGainFocusEvent &)event);
	}
}

} // namespace Light
