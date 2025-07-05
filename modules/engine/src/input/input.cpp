#include <engine/events/char.hpp>
#include <engine/events/event.hpp>
#include <engine/events/keyboard.hpp>
#include <engine/events/mouse.hpp>
#include <engine/input/input.hpp>
#include <engine/input/key_codes.hpp>
#include <imgui.h>

namespace Light {

Input *Input::s_context = nullptr;

Scope<Input> Input::create()
{
	return make_scope(new Input);
}

Input::Input()
    : m_keyboad_keys {}
    , m_mouse_buttons {}
    , m_mouse_position {}
    , m_mouse_delta {}
    , m_mouse_wheel_delta {}
    , m_user_interface_events(true)
    , m_game_events(true)
{
	lt_assert(
	    !s_context,
	    "Input::Input: an instance of 'Input' already exists, do not construct this class!"
	);
	s_context = this;

	restart_input_state();
}

void Input::receive_user_interface_events_impl(bool receive, bool toggle /* = false */)
{
	m_user_interface_events = toggle ? !m_user_interface_events : receive;
}

void Input::receieve_game_events_impl(bool receive, bool toggle /*= false*/)
{
	bool prev = m_game_events;
	m_game_events = toggle ? !m_user_interface_events : receive;

	if (m_game_events != prev)
		restart_input_state();
}

void Input::restart_input_state()
{
	m_keyboad_keys.fill(false);
	m_mouse_buttons.fill(false);

	m_mouse_position = glm::vec2(0.0f);
	m_mouse_delta = glm::vec2(0.0f);
	m_mouse_wheel_delta = 0.0f;
}

void Input::on_event(const Event &inputEvent)
{
	ImGuiIO &io = ImGui::GetIO();
	switch (inputEvent.get_event_type())
	{
		//** MOUSE_EVENTS **//
	case EventType::MouseMoved:
	{
		const MouseMovedEvent &event = (const MouseMovedEvent &)inputEvent;

		if (m_game_events)
		{
			m_mouse_delta = event.GetPosition() - m_mouse_position;
			m_mouse_position = event.GetPosition();
		}

		if (m_user_interface_events)
			io.MousePos = ImVec2(event.get_x(), event.get_y());

		return;
	}
	case EventType::ButtonPressed:
	{
		const ButtonPressedEvent &event = (const ButtonPressedEvent &)inputEvent;

		if (m_game_events)
			m_mouse_buttons[event.get_button()] = true;

		if (m_user_interface_events)
			io.MouseDown[event.get_button()] = true;

		return;
	}
	case EventType::ButtonReleased:
	{
		const ButtonReleasedEvent &event = (const ButtonReleasedEvent &)inputEvent;

		if (m_game_events)
			m_mouse_buttons[event.get_button()] = false;

		if (m_user_interface_events)
			io.MouseDown[event.get_button()] = false;

		return;
	}
	case EventType::WheelScrolled:
	{
		const WheelScrolledEvent &event = (const WheelScrolledEvent &)inputEvent;

		if (m_game_events)
			m_mouse_wheel_delta = event.get_offset();

		if (m_user_interface_events)
			io.MouseWheel = event.get_offset();

		return;
	}
	//** KEYBOARD_EVENTS **//
	case EventType::KeyPressed:
	{
		const KeyPressedEvent &event = (const KeyPressedEvent &)inputEvent;

		if (m_game_events)
			m_keyboad_keys[event.get_key()] = true;

		if (m_user_interface_events)
		{
			io.KeysDown[event.get_key()] = true;
			// if (event.get_key() == Key::BackSpace)
			//	io.AddInputCharacter(Key::BackSpace);
		}

		return;
	}
	case EventType::KeyReleased:
	{
		const KeyReleasedEvent &event = (const KeyReleasedEvent &)inputEvent;

		if (m_game_events)
			m_keyboad_keys[event.get_key()] = false;

		if (m_user_interface_events)
			io.KeysDown[event.get_key()] = false;

		return;
	}
	case EventType::SetChar:
	{
		if (m_user_interface_events)
		{
			const SetCharEvent &event = (const SetCharEvent &)inputEvent;
			io.AddInputCharacter(event.get_character());
		}

		return;
	}
	}
}

} // namespace Light
