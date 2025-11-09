export module math.components;

import math.vec3;

namespace lt::math::components {

export struct Transform
{
	math::vec3 translation;

	math::vec3 scale;

	math::vec3 rotation;
};

} // namespace lt::math::components
