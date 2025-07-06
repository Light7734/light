#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <engine/base/base.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace Light {

struct TransformComponent
{
	TransformComponent(const TransformComponent &) = default;

	TransformComponent(
	    const glm::vec3 &_translation = glm::vec3(0.0f, 0.0f, 0.0f),
	    const glm::vec3 &_scale = glm::vec3(1.0f, 1.0f, 1.0f),
	    const glm::vec3 &_rotation = glm::vec3(0.0f, 0.0f, 0.0f)
	)

	    : translation(_translation)
	    , scale(_scale)
	    , rotation(_rotation)
	{
	}

	[[nodiscard]] auto get_transform() const -> glm::mat4
	{
		return glm::translate(translation) * glm::rotate(rotation.z, glm::vec3(0.0f, 0.0f, 1.0f))
		       * glm::scale(scale);
	}

	operator const glm::mat4() const
	{
		return get_transform();
	}

	glm::vec3 translation;

	glm::vec3 scale;

	glm::vec3 rotation;
};

} // namespace Light
