#include <engine/camera/scene.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Light {

SceneCamera::SceneCamera()
    : m_OrthographicSpecification { 1000.0f, -1.0f, 10000.0f }
    , m_PerspectiveSpecification { glm::radians(45.0f), 0.01f, 10000.0f }
    , m_AspectRatio(16.0f / 9.0f)
    , m_ProjectionType(ProjectionType::Orthographic)
{
	CalculateProjection();
}

void SceneCamera::SetViewportSize(unsigned int width, unsigned int height)
{
	m_AspectRatio = width / (float)height;
	CalculateProjection();
}

void SceneCamera::SetProjectionType(ProjectionType projectionType)
{
	m_ProjectionType = projectionType;
	CalculateProjection();
}

void SceneCamera::SetOrthographicSize(float size)
{
	m_OrthographicSpecification.size = size;
	CalculateProjection();
}

void SceneCamera::SetOrthographicFarPlane(float farPlane)
{
	m_OrthographicSpecification.farPlane = farPlane;
	CalculateProjection();
}

void SceneCamera::SetOrthographicNearPlane(float nearPlane)
{
	m_OrthographicSpecification.nearPlane = nearPlane;
	CalculateProjection();
}

void SceneCamera::SetPerspectiveVerticalFOV(float verticalFOV)
{
	m_PerspectiveSpecification.verticalFOV = verticalFOV;
	CalculateProjection();
}

void SceneCamera::SetPerspectiveFarPlane(float farPlane)
{
	m_PerspectiveSpecification.farPlane = farPlane;
	CalculateProjection();
}

void SceneCamera::SetPerspectiveNearPlane(float nearPlane)
{
	m_PerspectiveSpecification.nearPlane = nearPlane;
	CalculateProjection();
}

void SceneCamera::CalculateProjection()
{
	if (m_ProjectionType == ProjectionType::Orthographic)
	{
		m_Projection = glm::ortho(
		    -m_OrthographicSpecification.size * 0.5f * m_AspectRatio,
		    m_OrthographicSpecification.size * 0.5f * m_AspectRatio,
		    -m_OrthographicSpecification.size * 0.5f,
		    m_OrthographicSpecification.size * 0.5f,
		    m_OrthographicSpecification.farPlane,
		    m_OrthographicSpecification.nearPlane
		);
	}
	else // perspective
	{
		m_Projection = glm::perspective(
		    m_PerspectiveSpecification.verticalFOV,
		    m_AspectRatio,
		    m_PerspectiveSpecification.nearPlane,
		    m_PerspectiveSpecification.farPlane
		);
	}
}

} // namespace Light
