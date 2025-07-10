#pragma once

#include <glm/glm.hpp>

namespace Light {

class OrthographicCamera
{
public:
	OrthographicCamera(
	    const glm::vec2 &position,
	    float aspectRatio,
	    float zoomLevel,
	    const glm::vec4 &clearColor = glm::vec4(0.1f, 0.3f, 0.7f, 1.0f)
	);

	void calculate_view();

	void calculate_projection();

	void on_resize(const glm::vec2 &size);

	[[nodiscard]] auto get_view() const -> const glm::mat4 &
	{
		return m_view;
	}

	[[nodiscard]] auto get_projection() const -> const glm::mat4 &
	{
		return m_projection;
	}

	[[nodiscard]] auto get_clear_color() const -> const glm::vec4 &
	{
		return m_clear_color;
	}

	void move(const glm::vec2 &position);

private:
	glm::vec2 m_position;

	float m_aspect_ratio;

	float m_zoom_level;

	const glm::vec3 m_up;

	glm::mat4 m_projection {};

	glm::mat4 m_view {};

	glm::vec4 m_clear_color;
};

} // namespace Light
