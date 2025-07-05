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

	void SetViewportSize(unsigned int width, unsigned int height);

	void SetProjectionType(ProjectionType projectionType);

	void SetOrthographicSize(float size);
	void SetOrthographicFarPlane(float farPlane);
	void SetOrthographicNearPlane(float nearPlane);

	void SetPerspectiveVerticalFOV(float verticalFov);
	void SetPerspectiveFarPlane(float farPlane);
	void SetPerspectiveNearPlane(float nearPlane);

	inline float GetOrthographicSize() const
	{
		return m_orthographic_specification.size;
	}
	inline float GetOrthographicFarPlane() const
	{
		return m_orthographic_specification.farPlane;
	}
	inline float GetOrthographicNearPlane() const
	{
		return m_orthographic_specification.nearPlane;
	}

	inline float GetPerspectiveVerticalFOV() const
	{
		return m_perspective_specification.verticalFOV;
	}
	inline float GetPerspectiveFarPlane() const
	{
		return m_perspective_specification.farPlane;
	}
	inline float GetPerspectiveNearPlane() const
	{
		return m_perspective_specification.nearPlane;
	}

	inline ProjectionType GetProjectionType() const
	{
		return m_projection_type;
	}

private:
	void CalculateProjection();
};

} // namespace Light
