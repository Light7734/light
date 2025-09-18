#pragma once

#include <math/vec2.hpp>

namespace lt::input {

class AnalogEvent
{
public:
	AnalogEvent(uint32_t input_code, math::uvec2 pointer_position)
	    : m_input_code(input_code)
	    , m_pointer_position(pointer_position)
	{
	}

	[[nodiscard]] auto get_code() const -> uint32_t
	{
		return m_input_code;
	};

	[[nodiscard]] auto get_pointer_position() const -> math::uvec2
	{
		return m_pointer_position;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		auto stream = std::stringstream {};
		const auto &[x, y] = m_pointer_position;
		stream << "input::AnalogEvent: " << m_input_code << " @ " << x << ", " << y;
		return stream.str();
	}

private:
	uint32_t m_input_code;

	math::uvec2 m_pointer_position;
};

class AxisEvent
{
};

} // namespace lt::input
