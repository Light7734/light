#pragma once

#include <engine/base/base.hpp>
#include <glm/glm.hpp>

namespace Light {

class OrthographicCamera
{
private:
	glm::vec2 m_position;
	float m_aspect_ratio;
	float m_zoom_level;

	const glm::vec3 m_up;

	glm::mat4 m_projection;
	glm::mat4 m_view;

	glm::vec4 m_clear_color;

public:
	OrthographicCamera(
	    const glm::vec2 &position,
	    float aspectRatio,
	    float zoomLevel,
	    const glm::vec4 &clearColor = glm::vec4(0.1f, 0.3f, 0.7f, 1.0f)
	);

	// CAMERA //
	void calculate_view();
	void calculate_projection();

	void on_resize(const glm::vec2 &size);

	inline const glm::mat4 &GetView() const
	{
		return m_view;
	}
	inline const glm::mat4 &GetProjection() const
	{
		return m_projection;
	}

	inline const glm::vec4 &GetClearColor() const
	{
		return m_clear_color;
	}

	// CAMERA_CONTROLLER //
	void move(const glm::vec2 &position);
};

} // namespace Light
