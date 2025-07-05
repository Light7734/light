#include <engine/camera/scene.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Light {

SceneCamera::SceneCamera()
    : m_orthographic_specification { 1000.0f, -1.0f, 10000.0f }
    , m_perspective_specification { glm::radians(45.0f), 0.01f, 10000.0f }
    , m_aspect_ratio(16.0f / 9.0f)
    , m_projection_type(ProjectionType::Orthographic)
{
	CalculateProjection();
}

void SceneCamera::SetViewportSize(unsigned int width, unsigned int height)
{
	m_aspect_ratio = width / (float)height;
	CalculateProjection();
}

void SceneCamera::SetProjectionType(ProjectionType projectionType)
{
	m_projection_type = projectionType;
	CalculateProjection();
}

void SceneCamera::SetOrthographicSize(float size)
{
	m_orthographic_specification.size = size;
	CalculateProjection();
}

void SceneCamera::SetOrthographicFarPlane(float farPlane)
{
	m_orthographic_specification.farPlane = farPlane;
	CalculateProjection();
}

void SceneCamera::SetOrthographicNearPlane(float nearPlane)
{
	m_orthographic_specification.nearPlane = nearPlane;
	CalculateProjection();
}

void SceneCamera::SetPerspectiveVerticalFOV(float verticalFOV)
{
	m_perspective_specification.verticalFOV = verticalFOV;
	CalculateProjection();
}

void SceneCamera::SetPerspectiveFarPlane(float farPlane)
{
	m_perspective_specification.farPlane = farPlane;
	CalculateProjection();
}

void SceneCamera::SetPerspectiveNearPlane(float nearPlane)
{
	m_perspective_specification.nearPlane = nearPlane;
	CalculateProjection();
}

void SceneCamera::CalculateProjection()
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
