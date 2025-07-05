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
	std::array<bool, 348> m_KeyboadKeys;
	std::array<bool, 8> m_MouseButtons;

	glm::vec2 m_MousePosition;
	glm::vec2 m_MouseDelta;
	float m_MouseWheelDelta;

	bool m_UserInterfaceEvents;
	bool m_GameEvents;

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
		return s_Context->m_KeyboadKeys[code];
	}
	static inline bool GetMouseButton(int code)
	{
		return s_Context->m_MouseButtons[code];
	}

	static inline const glm::vec2 &GetMousePosition(int code)
	{
		return s_Context->m_MousePosition;
	}

	void OnEvent(const Event &inputEvent);

	inline bool IsReceivingInputEvents() const
	{
		return m_UserInterfaceEvents;
	}
	inline bool IsReceivingGameEvents() const
	{
		return m_GameEvents;
	}

private:
	Input();

	void ReceiveUserInterfaceEventsImpl(bool receive, bool toggle = false);
	void ReceieveGameEventsImpl(bool receive, bool toggle = false);

	void RestartInputState();
};

} // namespace Light
