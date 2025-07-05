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
	static Scope<Input> Create();

	static inline void ReceiveUserInterfaceEvents(bool receive, bool toggle = false)
	{
		s_Context->ReceiveUserInterfaceEventsImpl(receive, toggle);
	}
	static inline void ReceiveGameEvents(bool receive, bool toggle = false)
	{
		s_Context->ReceieveGameEventsImpl(receive, toggle);
	}

	static inline bool GetKeyboardKey(int code)
	{
		return s_Context->m_keyboad_keys[code];
	}
	static inline bool GetMouseButton(int code)
	{
		return s_Context->m_mouse_buttons[code];
	}

	static inline const glm::vec2 &GetMousePosition(int code)
	{
		return s_Context->m_mouse_position;
	}

	void OnEvent(const Event &inputEvent);

	inline bool IsReceivingInputEvents() const
	{
		return m_user_interface_events;
	}
	inline bool IsReceivingGameEvents() const
	{
		return m_game_events;
	}

private:
	Input();

	void ReceiveUserInterfaceEventsImpl(bool receive, bool toggle = false);
	void ReceieveGameEventsImpl(bool receive, bool toggle = false);

	void RestartInputState();
};

} // namespace Light
