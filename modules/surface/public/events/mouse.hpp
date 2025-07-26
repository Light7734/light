#pragma once

#include <math/vec2.hpp>

namespace lt::surface {

class MouseMovedEvent
{
public:
	MouseMovedEvent(float x, float y): m_position(x, y)
	{
	}

	[[nodiscard]] auto get_position() const -> const math::vec2 &
	{
		return m_position;
	}

	[[nodiscard]] auto get_x() const -> float
	{
		return m_position.x;
	}

	[[nodiscard]] auto get_y() const -> float
	{
		return m_position.y;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("MouseMoved: {}, {}", m_position.x, m_position.y);
	}

private:
	math::vec2 m_position;
};

class WheelScrolledEvent
{
public:
	WheelScrolledEvent(float offset): m_offset(offset)
	{
	}

	[[nodiscard]] auto get_offset() const -> float
	{
		return m_offset;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		std::stringstream ss;
		ss << "WheelScrolled: " << m_offset;
		return ss.str();
	}

private:
	float m_offset;
};

class ButtonPressedEvent
{
public:
	ButtonPressedEvent(int button): m_button(button)
	{
	}

	[[nodiscard]] auto get_button() const -> int
	{
		return m_button;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("ButtonPressed: {}", m_button);
	}

private:
	int m_button;
};

class ButtonReleasedEvent
{
public:
	ButtonReleasedEvent(int button): m_button(button)
	{
	}

	[[nodiscard]] auto get_button() const -> int
	{
		return m_button;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		return std::format("ButtonReleased: {}", m_button);
	}

private:
	int m_button;
};

} // namespace lt::surface
