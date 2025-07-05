#pragma once

#include <engine/base/base.hpp>
#include <glm/glm.hpp>

namespace Light {

class OrthographicCamera
{
private:
	glm::vec2 m_Position;
	float m_AspectRatio;
	float m_ZoomLevel;

	const glm::vec3 m_Up;

	glm::mat4 m_Projection;
	glm::mat4 m_View;

	glm::vec4 m_ClearColor;

public:
	OrthographicCamera(
	    const glm::vec2 &position,
	    float aspectRatio,
	    float zoomLevel,
	    const glm::vec4 &clearColor = glm::vec4(0.1f, 0.3f, 0.7f, 1.0f)
	);

	// CAMERA //
	void CalculateView();
	void CalculateProjection();

	void OnResize(const glm::vec2 &size);

	inline const glm::mat4 &GetView() const
	{
		return m_View;
	}
	inline const glm::mat4 &GetProjection() const
	{
		return m_Projection;
	}

	inline const glm::vec4 &GetClearColor() const
	{
		return m_ClearColor;
	}

	// CAMERA_CONTROLLER //
	void Move(const glm::vec2 &position);
};

} // namespace Light
