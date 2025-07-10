#include <camera/ortho.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>

namespace Light {

OrthographicCamera::OrthographicCamera(
    const glm::vec2 &position,
    float aspect_ratio,
    float zoom_level,
    const glm::vec4 &clear_color /* = glm::vec4(0.1f, 0.3f, 0.7f, 1.0f) */
)
    : m_up(0.0f, 1.0f, 0.0f)
    , m_position(position)
    , m_aspect_ratio(aspect_ratio)
    , m_zoom_level(zoom_level)
    , m_clear_color(clear_color)
{
}

void OrthographicCamera::calculate_view()
{
	m_view = glm::lookAt(glm::vec3(m_position, 100.0f), glm::vec3(m_position, 0.0f), m_up);
}

void OrthographicCamera::calculate_projection()
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

void OrthographicCamera::on_resize(const glm::vec2 &size)
{
	m_aspect_ratio = size.x / size.y;
	calculate_projection();
}

void OrthographicCamera::move(const glm::vec2 &position)
{
	m_position += position;
}

} // namespace Light
