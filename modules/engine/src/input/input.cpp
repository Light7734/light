#include <engine/events/char.hpp>
#include <engine/events/event.hpp>
#include <engine/events/keyboard.hpp>
#include <engine/events/mouse.hpp>
#include <engine/input/input.hpp>
#include <engine/input/key_codes.hpp>
#include <imgui.h>

namespace Light {

Input *Input::s_Context = nullptr;

Scope<Input> Input::Create()
{
	return MakeScope(new Input);
}

Input::Input()
    : m_KeyboadKeys {}
    , m_MouseButtons {}
    , m_MousePosition {}
    , m_MouseDelta {}
    , m_MouseWheelDelta {}
    , m_UserInterfaceEvents(true)
    , m_GameEvents(true)
{
	ASSERT(
	    !s_Context,
	    "Input::Input: an instance of 'Input' already exists, do not construct this class!"
	);
	s_Context = this;

	RestartInputState();
}

void Input::ReceiveUserInterfaceEventsImpl(bool receive, bool toggle /* = false */)
{
	m_UserInterfaceEvents = toggle ? !m_UserInterfaceEvents : receive;
}

void Input::ReceieveGameEventsImpl(bool receive, bool toggle /*= false*/)
{
	bool prev = m_GameEvents;
	m_GameEvents = toggle ? !m_UserInterfaceEvents : receive;

	if (m_GameEvents != prev)
		RestartInputState();
}

void Input::RestartInputState()
{
	m_KeyboadKeys.fill(false);
	m_MouseButtons.fill(false);

	m_MousePosition = glm::vec2(0.0f);
	m_MouseDelta = glm::vec2(0.0f);
	m_MouseWheelDelta = 0.0f;
}

void Input::OnEvent(const Event &inputEvent)
{
	ImGuiIO &io = ImGui::GetIO();
	switch (inputEvent.GetEventType())
	{
		//** MOUSE_EVENTS **//
	case EventType::MouseMoved:
	{
		const MouseMovedEvent &event = (const MouseMovedEvent &)inputEvent;

		if (m_GameEvents)
		{
			m_MouseDelta = event.GetPosition() - m_MousePosition;
			m_MousePosition = event.GetPosition();
		}

		if (m_UserInterfaceEvents)
			io.MousePos = ImVec2(event.GetX(), event.GetY());

		return;
	}
	case EventType::ButtonPressed:
	{
		const ButtonPressedEvent &event = (const ButtonPressedEvent &)inputEvent;

		if (m_GameEvents)
			m_MouseButtons[event.GetButton()] = true;

		if (m_UserInterfaceEvents)
			io.MouseDown[event.GetButton()] = true;

		return;
	}
	case EventType::ButtonReleased:
	{
		const ButtonReleasedEvent &event = (const ButtonReleasedEvent &)inputEvent;

		if (m_GameEvents)
			m_MouseButtons[event.GetButton()] = false;

		if (m_UserInterfaceEvents)
			io.MouseDown[event.GetButton()] = false;

		return;
	}
	case EventType::WheelScrolled:
	{
		const WheelScrolledEvent &event = (const WheelScrolledEvent &)inputEvent;

		if (m_GameEvents)
			m_MouseWheelDelta = event.GetOffset();

		if (m_UserInterfaceEvents)
			io.MouseWheel = event.GetOffset();

		return;
	}
	//** KEYBOARD_EVENTS **//
	case EventType::KeyPressed:
	{
		const KeyPressedEvent &event = (const KeyPressedEvent &)inputEvent;

		if (m_GameEvents)
			m_KeyboadKeys[event.GetKey()] = true;

		if (m_UserInterfaceEvents)
		{
			io.KeysDown[event.GetKey()] = true;
			// if (event.GetKey() == Key::BackSpace)
			//	io.AddInputCharacter(Key::BackSpace);
		}

		return;
	}
	case EventType::KeyReleased:
	{
		const KeyReleasedEvent &event = (const KeyReleasedEvent &)inputEvent;

		if (m_GameEvents)
			m_KeyboadKeys[event.GetKey()] = false;

		if (m_UserInterfaceEvents)
			io.KeysDown[event.GetKey()] = false;

		return;
	}
	case EventType::SetChar:
	{
		if (m_UserInterfaceEvents)
		{
			const SetCharEvent &event = (const SetCharEvent &)inputEvent;
			io.AddInputCharacter(event.GetCharacter());
		}

		return;
	}
	}
}

} // namespace Light
