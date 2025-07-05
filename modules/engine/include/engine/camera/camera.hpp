#pragma once

#include <engine/base/base.hpp>
#include <glm/glm.hpp>

namespace Light {

class Camera
{
private:
	glm::vec4 m_BackgroundColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

protected:
	glm::mat4 m_Projection;

public:
	Camera() = default;

	inline const glm::mat4 &GetProjection() const
	{
		return m_Projection;
	}

	inline const glm::vec4 &GetBackgroundColor() const
	{
		return m_BackgroundColor;
	}

	inline void SetBackgroundColor(const glm::vec4 &color)
	{
		m_BackgroundColor = color;
	}
};

} // namespace Light
