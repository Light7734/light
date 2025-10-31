#pragma once

#include <math/vec3.hpp>

namespace lt::math::components {

struct Transform
{
	math::vec3 translation;

	math::vec3 scale;

	math::vec3 rotation;
};

} // namespace lt::math::components
