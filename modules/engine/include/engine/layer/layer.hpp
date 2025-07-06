#pragma once

#include <engine/base/base.hpp>

namespace Light {

class Event;

// mouse
class MouseMovedEvent;
class ButtonPressedEvent;
class ButtonReleasedEvent;
class WheelScrolledEvent;
class KeyPressedEvent;
class KeyRepeatEvent;
class KeyReleasedEvent;
class SetCharEvent;
class WindowClosedEvent;
class WindowResizedEvent;
class WindowMovedEvent;
class WindowLostFocusEvent;
class WindowGainFocusEvent;

class Layer
{
public:
	Layer(const std::string &name);

	virtual ~Layer() = default;

	auto get_name() const -> const std::string &
	{
		return m_layer_name;
	}

	virtual void on_update(float deltaTime)
	{
	}
	virtual void on_user_interface_update()
	{
	}

	virtual void on_render()
	{
	}

	auto on_event(const Event &event) -> bool;

protected:
	std::string m_layer_name;

	virtual auto on_mouse_moved(const MouseMovedEvent &event) -> bool
	{
		return false;
	}

	virtual auto on_button_pressed(const ButtonPressedEvent &event) -> bool
	{
		return false;
	}

	virtual auto on_button_released(const ButtonReleasedEvent &event) -> bool
	{
		return false;
	}

	virtual auto on_wheel_scrolled(const WheelScrolledEvent &event) -> bool
	{
		return false;
	}

	virtual auto on_key_pressed(const KeyPressedEvent &event) -> bool
	{
		return false;
	}

	virtual auto on_key_repeat(const KeyRepeatEvent &event) -> bool
	{
		return false;
	}

	virtual auto on_key_released(const KeyReleasedEvent &event) -> bool
	{
		return false;
	}

	virtual auto on_set_char(const SetCharEvent &event) -> bool
	{
		return false;
	}

	virtual auto on_window_closed(const WindowClosedEvent &event) -> bool
	{
		return false;
	}

	virtual auto on_window_resized(const WindowResizedEvent &event) -> bool
	{
		return false;
	}

	virtual auto on_window_moved(const WindowMovedEvent &event) -> bool
	{
		return false;
	}

	virtual auto on_window_lost_focus(const WindowLostFocusEvent &event) -> bool
	{
		return false;
	}

	virtual auto on_window_gain_focus(const WindowGainFocusEvent &event) -> bool
	{
		return false;
	}
};

} // namespace Light
