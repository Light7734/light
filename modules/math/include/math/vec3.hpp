#pragma once

#include <math/vec2.hpp>

namespace lt::math {

template<typename T = float>
struct vec3_impl
{
	vec3_impl(): x(), y(), z()
	{
	}

	explicit vec3_impl(T scalar): x(scalar), y(scalar), z(scalar)
	{
	}

	vec3_impl(T x, T y, T z): x(x), y(y), z(z)
	{
	}

	[[nodiscard]] auto operator-(const vec3_impl<T> &other) const -> vec3_impl
	{
		return {
			x - other.x,
			y - other.y,
			z - other.z,
		};
	}

	[[nodiscard]] auto operator*(const vec3_impl<T> &other) const -> vec3_impl
	{
		return {
			x * other.x,
			y * other.y,
			z * other.z,
		};
	}

	T x; // NOLINT

	T y; // NOLINT

	T z; // NOLINT
};

using vec3 = vec3_impl<float>;

using ivec3 = vec3_impl<int32_t>;

using uvec3 = vec3_impl<uint32_t>;

} // namespace lt::math
