#pragma once

#include <math/vec2.hpp>
#include <sstream>

namespace lt::surface {

class ClosedEvent
{
public:
	[[nodiscard]] auto to_string() const -> std::string_view
	{
		return "SurfaceClosedEvent";
	}
};

class MovedEvent
{
public:
	MovedEvent(int x, int y): m_position(x, y)
	{
	}

	[[nodiscard]] auto get_position() const -> const math::ivec2 &
	{
		return m_position;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		auto stream = std::stringstream {};
		stream << "WindwoMoved: " << m_position.x << ", " << m_position.y;
		return stream.str();
	}

private:
	math::ivec2 m_position;
};

class ResizedEvent
{
public:
	ResizedEvent(unsigned int width, unsigned int height): m_size(width, height)
	{
	}

	[[nodiscard]] auto get_size() const -> const math::uvec2 &
	{
		return m_size;
	}

	[[nodiscard]] auto to_string() const -> std::string
	{
		auto stream = std::stringstream {};
		stream << "SurfaceResized: " << m_size.x << ", " << m_size.y;
		return stream.str();
	}

private:
	math::uvec2 m_size;
};

class LostFocusEvent
{
public:
	[[nodiscard]] auto to_string() const -> std::string_view
	{
		return "SurfaceLostFocus";
	}
};

class GainFocusEvent
{
public:
	[[nodiscard]] auto to_string() const -> std::string_view
	{
		return "SurfaceGainFocus";
	}
};

} // namespace lt::surface
