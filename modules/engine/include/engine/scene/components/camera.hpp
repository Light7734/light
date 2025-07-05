#pragma once

#include <engine/base/base.hpp>
#include <engine/camera/scene.hpp>
#include <glm/glm.hpp>

namespace Light {

struct CameraComponent
{
	CameraComponent() = default;

	CameraComponent(const CameraComponent &) = default;

	CameraComponent(SceneCamera _camera, bool _isPrimary = false)
	    : camera(_camera)
	    , isPrimary(_isPrimary)
	{
	}

	operator SceneCamera()
	{
		return camera;
	}

	SceneCamera camera;

	bool isPrimary;
};

} // namespace Light
