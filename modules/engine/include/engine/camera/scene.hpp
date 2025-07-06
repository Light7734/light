#pragma once

#include <engine/base/base.hpp>
#include <engine/camera/camera.hpp>

namespace Light {

class SceneCamera: public Camera
{
public:
	enum class ProjectionType
	{
		Orthographic = 0,
		Perspetcive = 1
	};

	struct OrthographicSpecification
	{
		float size;

		float near_plane;

		float far_plane;
	};

	struct PerspectiveSpecification
	{
		float vertical_fov;

		float near_plane;

		float far_plane;
	};

	SceneCamera();

	void set_viewport_size(unsigned int width, unsigned int height);

	void set_projection_type(ProjectionType projectionType);

	void set_orthographic_size(float size);

	void set_orthographic_far_plane(float farPlane);

	void set_orthographic_near_plane(float nearPlane);

	void set_perspective_vertical_fov(float verticalFov);

	void set_perspective_far_plane(float farPlane);

	void set_perspective_near_plane(float nearPlane);

	auto get_orthographic_size() const -> float
	{
		return m_orthographic_specification.size;
	}

	auto get_orthographic_far_plane() const -> float
	{
		return m_orthographic_specification.far_plane;
	}

	auto get_orthographic_near_plane() const -> float
	{
		return m_orthographic_specification.near_plane;
	}

	auto get_perspective_vertical_fov() const -> float
	{
		return m_perspective_specification.vertical_fov;
	}

	auto get_perspective_far_plane() const -> float
	{
		return m_perspective_specification.far_plane;
	}

	auto get_perspective_near_plane() const -> float
	{
		return m_perspective_specification.near_plane;
	}

	auto get_projection_type() const -> ProjectionType
	{
		return m_projection_type;
	}


private:
	OrthographicSpecification m_orthographic_specification;

	PerspectiveSpecification m_perspective_specification;

	float m_aspect_ratio;

	ProjectionType m_projection_type;

	void calculate_projection();
};

} // namespace Light
