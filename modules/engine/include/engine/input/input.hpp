#pragma once

#include <array>
#include <engine/base/base.hpp>
#include <glm/glm.hpp>

namespace Light {

class Event;

class Input
{
public:
	static auto create() -> Scope<Input>;

	static void receive_user_interface_events(bool receive, bool toggle = false)
	{
		s_context->receive_user_interface_events_impl(receive, toggle);
	}
	static void receive_game_events(bool receive, bool toggle = false)
	{
		s_context->receieve_game_events_impl(receive, toggle);
	}

	static auto get_keyboard_key(int code) -> bool
	{
		return s_context->m_keyboad_keys[code];
	}
	static auto get_mouse_button(int code) -> bool
	{
		return s_context->m_mouse_buttons[code];
	}

	static auto get_mouse_position(int code) -> const glm::vec2 &
	{
		return s_context->m_mouse_position;
	}

	void on_event(const Event &inputEvent);

	auto is_receiving_input_events() const -> bool
	{
		return m_user_interface_events;
	}

	auto is_receiving_game_events() const -> bool
	{
		return m_game_events;
	}

private:
	static Input *s_context;

	std::array<bool, 348> m_keyboad_keys;

	std::array<bool, 8> m_mouse_buttons;

	glm::vec2 m_mouse_position;

	glm::vec2 m_mouse_delta;

	float m_mouse_wheel_delta;

	bool m_user_interface_events;

	bool m_game_events;

	Input();

	void receive_user_interface_events_impl(bool receive, bool toggle = false);

	void receieve_game_events_impl(bool receive, bool toggle = false);

	void restart_input_state();
};

} // namespace Light
