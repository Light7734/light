#pragma once

#include <math/mat4.hpp>
#include <math/vec3.hpp>

namespace lt {

struct TransformComponent
{
	TransformComponent(const TransformComponent &) = default;

	TransformComponent(
	    const math::vec3 &_translation = math::vec3(0.0f, 0.0f, 0.0f),
	    const math::vec3 &_scale = math::vec3(1.0f, 1.0f, 1.0f),
	    const math::vec3 &_rotation = math::vec3(0.0f, 0.0f, 0.0f)
	)

	    : translation(_translation)
	    , scale(_scale)
	    , rotation(_rotation)
	{
	}

	[[nodiscard]] auto get_transform() const -> math::mat4
	{
		return math::translate(translation)
		       * math::rotate(rotation.z, math::vec3 { 0.0f, 0.0f, 1.0f }) //
		       * math::scale(scale);
	}

	operator const math::mat4() const
	{
		return get_transform();
	}

	math::vec3 translation;

	math::vec3 scale;

	math::vec3 rotation;
};

} // namespace lt
