export module input.components;

#include <vector>

namespace lt::input {

struct Trigger
{
	uint32_t mapped_keycode;
};

struct InputAction
{
	using Key = size_t;

	enum class State : uint8_t
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

	auto get_action(auto idx) -> const InputAction &
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
