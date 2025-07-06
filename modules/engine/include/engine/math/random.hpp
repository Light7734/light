#pragma once

// #todo: make proper math stuff

// this is a temporary header file to extend the glm math
// light engine will either have it's own math library or extend upon the glm

#include <glm/glm.hpp>

namespace Light {
namespace Math {

auto rand(int min, int max, int decimals = 0) -> float;

auto rand_vec2(int min, int max, int decimals = 0) -> glm::vec2;

auto rand_vec3(int min, int max, int decimals = 0) -> glm::vec3;

} // namespace Math
} // namespace Light
