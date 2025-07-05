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

	const std::string &GetName() const
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

	bool on_event(const Event &event);

protected:
	std::string m_layer_name;

	virtual bool on_mouse_moved(const MouseMovedEvent &event)
	{
		return false;
	}

	virtual bool on_button_pressed(const ButtonPressedEvent &event)
	{
		return false;
	}

	virtual bool on_button_released(const ButtonReleasedEvent &event)
	{
		return false;
	}

	virtual bool on_wheel_scrolled(const WheelScrolledEvent &event)
	{
		return false;
	}

	virtual bool on_key_pressed(const KeyPressedEvent &event)
	{
		return false;
	}

	virtual bool on_key_repeat(const KeyRepeatEvent &event)
	{
		return false;
	}

	virtual bool on_key_released(const KeyReleasedEvent &event)
	{
		return false;
	}

	virtual bool on_set_char(const SetCharEvent &event)
	{
		return false;
	}

	virtual bool on_window_closed(const WindowClosedEvent &event)
	{
		return false;
	}

	virtual bool on_window_resized(const WindowResizedEvent &event)
	{
		return false;
	}

	virtual bool on_window_moved(const WindowMovedEvent &event)
	{
		return false;
	}

	virtual bool on_window_lost_focus(const WindowLostFocusEvent &event)
	{
		return false;
	}

	virtual bool on_window_gain_focus(const WindowGainFocusEvent &event)
	{
		return false;
	}
};

} // namespace Light
