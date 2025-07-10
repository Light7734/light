#pragma once

#include <glm/glm.hpp>

namespace Light {

class Camera
{
public:
	Camera() = default;

	[[nodiscard]] auto get_projection() const -> const glm::mat4 &
	{
		return m_projection;
	}

	[[nodiscard]] auto get_background_color() const -> const glm::vec4 &
	{
		return m_background_color;
	}

	void set_background_color(const glm::vec4 &color)
	{
		m_background_color = color;
	}

protected:
	glm::mat4 m_projection {};

private:
	glm::vec4 m_background_color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
};

} // namespace Light
