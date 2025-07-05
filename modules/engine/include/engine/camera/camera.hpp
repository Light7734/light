#pragma once

#include <engine/base/base.hpp>
#include <glm/glm.hpp>

namespace Light {

class Camera
{
private:
	glm::vec4 m_background_color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

protected:
	glm::mat4 m_projection;

public:
	Camera() = default;

	inline const glm::mat4 &GetProjection() const
	{
		return m_projection;
	}

	inline const glm::vec4 &GetBackgroundColor() const
	{
		return m_background_color;
	}

	inline void SetBackgroundColor(const glm::vec4 &color)
	{
		m_background_color = color;
	}
};

} // namespace Light
