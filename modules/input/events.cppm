export module input.events;

import input.codes;
import math.vec2;

import std;

namespace lt::input {

export class AnalogEvent
{
public:
	AnalogEvent(Key key, math::uvec2 pointer_position)
	    : m_key(key)
	    , m_pointer_position(pointer_position)
	{
	}

	[[nodiscard]] auto get_key() const -> Key
	{
		return m_key;
	};

	[[nodiscard]] auto get_pointer_position() const -> math::uvec2
	{
		return m_pointer_position;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		const auto &[x, y] = m_pointer_position;
		return std::format("input::AnalogEvent: {} @ {}, {}", std::to_underlying(m_key), x, y);
	}

private:
	Key m_key;

	math::uvec2 m_pointer_position;
};

} // namespace lt::input
