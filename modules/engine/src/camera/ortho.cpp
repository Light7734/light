#include <engine/camera/ortho.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>

namespace Light {

OrthographicCamera::OrthographicCamera(
    const glm::vec2 &position,
    float aspectRatio,
    float zoomLevel,
    const glm::vec4 &clearColor /* = glm::vec4(0.1f, 0.3f, 0.7f, 1.0f) */
)
    : m_Up(0.0f, 1.0f, 0.0f)
    , m_Position(position)
    , m_AspectRatio(aspectRatio)
    , m_ZoomLevel(zoomLevel)
    , m_ClearColor(clearColor)
{
}

void OrthographicCamera::CalculateView()
{
	m_View = glm::lookAt(glm::vec3(m_Position, 100.0f), glm::vec3(m_Position, 0.0f), m_Up);
}

void OrthographicCamera::CalculateProjection()
{
	m_Projection = glm::ortho(
	    -m_ZoomLevel * m_AspectRatio,
	    +m_ZoomLevel * m_AspectRatio,
	    -m_ZoomLevel,
	    +m_ZoomLevel,
	    FLT_MAX,
	    FLT_MIN
	);
}

void OrthographicCamera::OnResize(const glm::vec2 &size)
{
	m_AspectRatio = size.x / size.y;
	CalculateProjection();
}

void OrthographicCamera::Move(const glm::vec2 &position)
{
	m_Position += position;
}

} // namespace Light
