#pragma once

#include <array>
#include <engine/base/base.hpp>
#include <glm/glm.hpp>

namespace Light {

class Event;

class Input /* singleton */
{
private:
	static Input *s_Context;

private:
	std::array<bool, 348> m_keyboad_keys;
	std::array<bool, 8> m_mouse_buttons;

	glm::vec2 m_mouse_position;
	glm::vec2 m_mouse_delta;
	float m_mouse_wheel_delta;

	bool m_user_interface_events;
	bool m_game_events;

public:
	static Scope<Input> create();

	static inline void receive_user_interface_events(bool receive, bool toggle = false)
	{
		s_Context->receive_user_interface_events_impl(receive, toggle);
	}
	static inline void receive_game_events(bool receive, bool toggle = false)
	{
		s_Context->receieve_game_events_impl(receive, toggle);
	}

	static inline bool get_keyboard_key(int code)
	{
		return s_Context->m_keyboad_keys[code];
	}
	static inline bool get_mouse_button(int code)
	{
		return s_Context->m_mouse_buttons[code];
	}

	static inline const glm::vec2 &GetMousePosition(int code)
	{
		return s_Context->m_mouse_position;
	}

	void on_event(const Event &inputEvent);

	inline bool is_receiving_input_events() const
	{
		return m_user_interface_events;
	}
	inline bool is_receiving_game_events() const
	{
		return m_game_events;
	}

private:
	Input();

	void receive_user_interface_events_impl(bool receive, bool toggle = false);
	void receieve_game_events_impl(bool receive, bool toggle = false);

	void restart_input_state();
};

} // namespace Light
