#include <camera/scene.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace lt {

SceneCamera::SceneCamera()
    : m_orthographic_specification { .size = 1000.0f, .near_plane = -1.0f, .far_plane = 10000.0f }
    , m_perspective_specification { .vertical_fov = glm::radians(45.0f),
	                                .near_plane = 0.01f,
	                                .far_plane = 10000.0f }
    , m_aspect_ratio(16.0f / 9.0f)

{
	calculate_projection();
}

void SceneCamera::set_viewport_size(unsigned int width, unsigned int height)
{
	m_aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
	calculate_projection();
}

void SceneCamera::set_projection_type(ProjectionType projection_type)
{
	m_projection_type = projection_type;
	calculate_projection();
}

void SceneCamera::set_orthographic_size(float size)
{
	m_orthographic_specification.size = size;
	calculate_projection();
}

void SceneCamera::set_orthographic_far_plane(float far_plane)
{
	m_orthographic_specification.far_plane = far_plane;
	calculate_projection();
}

void SceneCamera::set_orthographic_near_plane(float near_plane)
{
	m_orthographic_specification.near_plane = near_plane;
	calculate_projection();
}

void SceneCamera::set_perspective_vertical_fov(float vertical_fov)
{
	m_perspective_specification.vertical_fov = vertical_fov;
	calculate_projection();
}

void SceneCamera::set_perspective_far_plane(float far_plane)
{
	m_perspective_specification.far_plane = far_plane;
	calculate_projection();
}

void SceneCamera::set_perspective_near_plane(float near_plane)
{
	m_perspective_specification.near_plane = near_plane;
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
		    m_orthographic_specification.far_plane,
		    m_orthographic_specification.near_plane
		);
	}
	else // perspective
	{
		m_projection = glm::perspective(
		    m_perspective_specification.vertical_fov,
		    m_aspect_ratio,
		    m_perspective_specification.near_plane,
		    m_perspective_specification.far_plane
		);
	}
}

} // namespace lt
