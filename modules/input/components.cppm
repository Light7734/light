export module input.system:components;

import preliminary;
import input.codes;

export namespace lt::input {

struct Trigger
{
	Key mapped_keycode;
};

struct InputAction
{
	enum class State : u8
	{
		inactive,
		active,
		triggered,
		cancelled,
	};

	std::string name;

	State state;

	Trigger trigger;
};

class InputComponent
{
public:
	InputComponent() = default;

	auto add_action(InputAction action) -> size_t
	{
		m_actions.emplace_back(std::move(action));
		return m_actions.size() - 1;
	}

	auto get_action(size_t idx) -> const InputAction &
	{
		return m_actions[idx];
	}

private:
	friend class System;

	void push_event()
	{
	}

	std::vector<InputAction> m_actions;
};

} // namespace lt::input
