#pragma once

#include <array>
#include <glm/glm.hpp>

namespace lt {

class Event;

class Input
{
public:
	static auto instance() -> Input &
	{
		static auto instance = Input {};
		return instance;
	}

	static void receive_user_interface_events(bool receive, bool toggle = false)
	{
		instance().receive_user_interface_events_impl(receive, toggle);
	}

	static void receive_game_events(bool receive, bool toggle = false)
	{
		instance().receieve_game_events_impl(receive, toggle);
	}

	static auto get_keyboard_key(int code) -> bool
	{
		return instance().m_keyboad_keys[code];
	}

	static auto get_mouse_button(int code) -> bool
	{
		return instance().m_mouse_buttons[code];
	}

	static auto get_mouse_position(int /*code*/) -> const glm::vec2 &
	{
		return instance().m_mouse_position;
	}

	void on_event(const Event &inputEvent);

	[[nodiscard]] auto is_receiving_input_events() const -> bool
	{
		return m_user_interface_events;
	}

	[[nodiscard]] auto is_receiving_game_events() const -> bool
	{
		return m_game_events;
	}

private:
	Input();

	void receive_user_interface_events_impl(bool receive, bool toggle = false);

	void receieve_game_events_impl(bool receive, bool toggle = false);

	void restart_input_state();

	std::array<bool, 348> m_keyboad_keys {};

	std::array<bool, 8> m_mouse_buttons {};

	glm::vec2 m_mouse_position;

	glm::vec2 m_mouse_delta;

	float m_mouse_wheel_delta {};

	bool m_user_interface_events { true };

	bool m_game_events { true };
};

} // namespace lt
