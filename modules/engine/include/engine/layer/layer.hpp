#pragma once

#include <engine/base/base.hpp>

namespace Light {

class Event;

// mouse
class MouseMovedEvent;
class ButtonPressedEvent;
class ButtonReleasedEvent;
class WheelScrolledEvent;

// keyboard
// key
class KeyPressedEvent;
class KeyRepeatEvent;
class KeyReleasedEvent;
// char
class SetCharEvent;

// window
class WindowClosedEvent;
class WindowResizedEvent;
class WindowMovedEvent;
class WindowLostFocusEvent;
class WindowGainFocusEvent;

class Layer
{
protected:
	std::string m_LayerName;

public:
	Layer(const std::string &name);
	virtual ~Layer() = default;

	inline const std::string &GetName() const
	{
		return m_LayerName;
	}

	/* update */
	virtual void OnUpdate(float deltaTime)
	{
	}
	virtual void OnUserInterfaceUpdate()
	{
	}

	virtual void OnRender()
	{
	}

	bool OnEvent(const Event &event);

protected:
	/* mouse */
	// cursor
	virtual bool OnMouseMoved(const MouseMovedEvent &event)
	{
		return false;
	}
	// button
	virtual bool OnButtonPressed(const ButtonPressedEvent &event)
	{
		return false;
	}
	virtual bool OnButtonReleased(const ButtonReleasedEvent &event)
	{
		return false;
	}
	// wheel
	virtual bool OnWheelScrolled(const WheelScrolledEvent &event)
	{
		return false;
	}

	/* keyboard */
	// key
	virtual bool OnKeyPressed(const KeyPressedEvent &event)
	{
		return false;
	}
	virtual bool OnKeyRepeat(const KeyRepeatEvent &event)
	{
		return false;
	}
	virtual bool OnKeyReleased(const KeyReleasedEvent &event)
	{
		return false;
	}
	// char
	virtual bool OnSetChar(const SetCharEvent &event)
	{
		return false;
	}

	/* window */
	// termination
	virtual bool OnWindowClosed(const WindowClosedEvent &event)
	{
		return false;
	}
	// size/position
	virtual bool OnWindowResized(const WindowResizedEvent &event)
	{
		return false;
	}
	virtual bool OnWindowMoved(const WindowMovedEvent &event)
	{
		return false;
	}
	// focus
	virtual bool OnWindowLostFocus(const WindowLostFocusEvent &event)
	{
		return false;
	}
	virtual bool OnWindowGainFocus(const WindowGainFocusEvent &event)
	{
		return false;
	}
};

} // namespace Light
