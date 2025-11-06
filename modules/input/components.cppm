export module input.system:components;
import input.codes;
import std;

namespace lt::input {

export struct Trigger
{
	Key mapped_keycode;
};

export struct InputAction
{
	enum class State : std::uint8_t
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

export class InputComponent
{
public:
	InputComponent() = default;

	auto add_action(InputAction action) -> std::size_t
	{
		m_actions.emplace_back(std::move(action));
		return m_actions.size() - 1;
	}

	auto get_action(std::size_t idx) -> const InputAction &
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
