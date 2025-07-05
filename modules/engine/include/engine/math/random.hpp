#pragma once

// #todo: make proper math stuff

// this is a temporary header file to extend the glm math
// light engine will either have it's own math library or extend upon the glm

#include <glm/glm.hpp>

namespace Light { namespace Math {

	float rand(int min, int max, int decimals = 0);
	glm::vec2 rand_vec2(int min, int max, int decimals = 0);
	glm::vec3 rand_vec3(int min, int max, int decimals = 0);

}}