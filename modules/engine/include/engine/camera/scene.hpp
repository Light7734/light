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
	OrthographicSpecification m_OrthographicSpecification;
	PerspectiveSpecification m_PerspectiveSpecification;
	float m_AspectRatio;

	ProjectionType m_ProjectionType;

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
		return m_OrthographicSpecification.size;
	}
	inline float GetOrthographicFarPlane() const
	{
		return m_OrthographicSpecification.farPlane;
	}
	inline float GetOrthographicNearPlane() const
	{
		return m_OrthographicSpecification.nearPlane;
	}

	inline float GetPerspectiveVerticalFOV() const
	{
		return m_PerspectiveSpecification.verticalFOV;
	}
	inline float GetPerspectiveFarPlane() const
	{
		return m_PerspectiveSpecification.farPlane;
	}
	inline float GetPerspectiveNearPlane() const
	{
		return m_PerspectiveSpecification.nearPlane;
	}

	inline ProjectionType GetProjectionType() const
	{
		return m_ProjectionType;
	}

private:
	void CalculateProjection();
};

} // namespace Light
