#pragma once

#include <math/mat4.hpp>
#include <math/vec4.hpp>

namespace lt {

class Camera
{
public:
	Camera() = default;

	[[nodiscard]] auto get_projection() const -> const math::mat4 &
	{
		return m_projection;
	}

	[[nodiscard]] auto get_background_color() const -> const math::vec4 &
	{
		return m_background_color;
	}

	void set_background_color(const math::vec4 &color)
	{
		m_background_color = color;
	}

protected:
	math::mat4 m_projection;

private:
	math::vec4 m_background_color = math::vec4(1.0f, 0.0f, 0.0f, 1.0f);
};

} // namespace lt
