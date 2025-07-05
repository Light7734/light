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

	struct OrthographicSpecification // :#todo use this
	{
		float size;
		float nearPlane, farPlane;
	};

	struct PerspectiveSpecification
	{
		float verticalFOV;
		float nearPlane, farPlane;
	};

private:
	OrthographicSpecification m_orthographic_specification;
	PerspectiveSpecification m_perspective_specification;
	float m_aspect_ratio;

	ProjectionType m_projection_type;

public:
	SceneCamera();

	void set_viewport_size(unsigned int width, unsigned int height);

	void set_projection_type(ProjectionType projectionType);

	void set_orthographic_size(float size);
	void set_orthographic_far_plane(float farPlane);
	void set_orthographic_near_plane(float nearPlane);

	void set_perspective_vertical_fov(float verticalFov);
	void set_perspective_far_plane(float farPlane);
	void set_perspective_near_plane(float nearPlane);

	inline float get_orthographic_size() const
	{
		return m_orthographic_specification.size;
	}
	inline float get_orthographic_far_plane() const
	{
		return m_orthographic_specification.farPlane;
	}
	inline float get_orthographic_near_plane() const
	{
		return m_orthographic_specification.nearPlane;
	}

	inline float get_perspective_vertical_fov() const
	{
		return m_perspective_specification.verticalFOV;
	}
	inline float get_perspective_far_plane() const
	{
		return m_perspective_specification.farPlane;
	}
	inline float get_perspective_near_plane() const
	{
		return m_perspective_specification.nearPlane;
	}

	inline ProjectionType get_projection_type() const
	{
		return m_projection_type;
	}

private:
	void calculate_projection();
};

} // namespace Light
