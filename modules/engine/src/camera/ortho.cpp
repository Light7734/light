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
    : m_up(0.0f, 1.0f, 0.0f)
    , m_position(position)
    , m_aspect_ratio(aspectRatio)
    , m_zoom_level(zoomLevel)
    , m_clear_color(clearColor)
{
}

void OrthographicCamera::CalculateView()
{
	m_view = glm::lookAt(glm::vec3(m_position, 100.0f), glm::vec3(m_position, 0.0f), m_up);
}

void OrthographicCamera::CalculateProjection()
{
	m_projection = glm::ortho(
	    -m_zoom_level * m_aspect_ratio,
	    +m_zoom_level * m_aspect_ratio,
	    -m_zoom_level,
	    +m_zoom_level,
	    FLT_MAX,
	    FLT_MIN
	);
}

void OrthographicCamera::OnResize(const glm::vec2 &size)
{
	m_aspect_ratio = size.x / size.y;
	CalculateProjection();
}

void OrthographicCamera::Move(const glm::vec2 &position)
{
	m_position += position;
}

} // namespace Light
