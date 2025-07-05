#include <engine/camera/scene.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Light {

SceneCamera::SceneCamera()
    : m_orthographic_specification { 1000.0f, -1.0f, 10000.0f }
    , m_perspective_specification { glm::radians(45.0f), 0.01f, 10000.0f }
    , m_aspect_ratio(16.0f / 9.0f)
    , m_projection_type(ProjectionType::Orthographic)
{
	calculate_projection();
}

void SceneCamera::set_viewport_size(unsigned int width, unsigned int height)
{
	m_aspect_ratio = width / (float)height;
	calculate_projection();
}

void SceneCamera::set_projection_type(ProjectionType projectionType)
{
	m_projection_type = projectionType;
	calculate_projection();
}

void SceneCamera::set_orthographic_size(float size)
{
	m_orthographic_specification.size = size;
	calculate_projection();
}

void SceneCamera::set_orthographic_far_plane(float farPlane)
{
	m_orthographic_specification.farPlane = farPlane;
	calculate_projection();
}

void SceneCamera::set_orthographic_near_plane(float nearPlane)
{
	m_orthographic_specification.nearPlane = nearPlane;
	calculate_projection();
}

void SceneCamera::set_perspective_vertical_fov(float verticalFOV)
{
	m_perspective_specification.verticalFOV = verticalFOV;
	calculate_projection();
}

void SceneCamera::set_perspective_far_plane(float farPlane)
{
	m_perspective_specification.farPlane = farPlane;
	calculate_projection();
}

void SceneCamera::set_perspective_near_plane(float nearPlane)
{
	m_perspective_specification.nearPlane = nearPlane;
	calculate_projection();
}

void SceneCamera::calculate_projection()
{
	if (m_projection_type == ProjectionType::Orthographic)
	{
		m_projection = glm::ortho(
		    -m_orthographic_specification.size * 0.5f * m_aspect_ratio,
		    m_orthographic_specification.size * 0.5f * m_aspect_ratio,
		    -m_orthographic_specification.size * 0.5f,
		    m_orthographic_specification.size * 0.5f,
		    m_orthographic_specification.farPlane,
		    m_orthographic_specification.nearPlane
		);
	}
	else // perspective
	{
		m_projection = glm::perspective(
		    m_perspective_specification.verticalFOV,
		    m_aspect_ratio,
		    m_perspective_specification.nearPlane,
		    m_perspective_specification.farPlane
		);
	}
}

} // namespace Light
