#include <engine/events/char.hpp>
#include <engine/events/event.hpp>
#include <engine/events/keyboard.hpp>
#include <engine/events/mouse.hpp>
#include <engine/input/input.hpp>
#include <engine/input/key_codes.hpp>
#include <imgui.h>

namespace Light {

Input::Input(): m_mouse_position {}, m_mouse_delta {}

{
	restart_input_state();
}

void Input::receive_user_interface_events_impl(bool receive, bool toggle /* = false */)
{
	m_user_interface_events = toggle ? !m_user_interface_events : receive;
}

void Input::receieve_game_events_impl(bool receive, bool toggle /*= false*/)
{
	auto prev = m_game_events;
	m_game_events = toggle ? !m_user_interface_events : receive;

	if (m_game_events != prev)
	{
		restart_input_state();
	}
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
	auto &io = ImGui::GetIO();
	switch (inputEvent.get_event_type())
	{
		//** MOUSE_EVENTS **//
	case EventType::MouseMoved:
	{
		const auto &event = dynamic_cast<const MouseMovedEvent &>(inputEvent);

		if (m_game_events)
		{
			m_mouse_delta = event.get_position() - m_mouse_position;
			m_mouse_position = event.get_position();
		}

		if (m_user_interface_events)
		{
			io.MousePos = ImVec2(event.get_x(), event.get_y());
		}

		return;
	}
	case EventType::ButtonPressed:
	{
		const auto &event = dynamic_cast<const ButtonPressedEvent &>(inputEvent);

		if (m_game_events)
		{
			m_mouse_buttons[event.get_button()] = true;
		}

		if (m_user_interface_events)
		{
			io.MouseDown[event.get_button()] = true;
		}

		return;
	}
	case EventType::ButtonReleased:
	{
		const auto &event = dynamic_cast<const ButtonReleasedEvent &>(inputEvent);

		if (m_game_events)
		{
			m_mouse_buttons[event.get_button()] = false;
		}

		if (m_user_interface_events)
		{
			io.MouseDown[event.get_button()] = false;
		}

		return;
	}
	case EventType::WheelScrolled:
	{
		const auto &event = dynamic_cast<const WheelScrolledEvent &>(inputEvent);

		if (m_game_events)
		{
			m_mouse_wheel_delta = event.get_offset();
		}

		if (m_user_interface_events)
		{
			io.MouseWheel = event.get_offset();
		}

		return;
	}
	//** KEYBOARD_EVENTS **//
	case EventType::KeyPressed:
	{
		const auto &event = dynamic_cast<const KeyPressedEvent &>(inputEvent);

		if (m_game_events)
		{
			m_keyboad_keys[event.get_key()] = true;
		}

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
		const auto &event = dynamic_cast<const KeyReleasedEvent &>(inputEvent);

		if (m_game_events)
		{
			m_keyboad_keys[event.get_key()] = false;
		}

		if (m_user_interface_events)
		{
			io.KeysDown[event.get_key()] = false;
		}

		return;
	}
	case EventType::SetChar:
	{
		if (m_user_interface_events)
		{
			const auto &event = dynamic_cast<const SetCharEvent &>(inputEvent);
			io.AddInputCharacter(event.get_character());
		}

		return;
	}
	}
}

} // namespace Light
