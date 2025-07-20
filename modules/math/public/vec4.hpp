#pragma once

#include <array>

namespace lt::math {

template<typename T = float>
struct vec4_impl
{
	vec4_impl(): x(), y(), z(), w()
	{
	}

	explicit vec4_impl(T scalar): x(scalar), y(scalar), z(scalar), w(scalar)
	{
	}

	vec4_impl(T x, T y, T z, T w): x(x), y(y), z(z), w(w)
	{
	}

	[[nodiscard]] auto operator-(const vec4_impl<T> &other) const -> vec4_impl
	{
		return {
			x - other.x,
			y - other.y,
			z - other.z,
			w - other.w,
		};
	}

	[[nodiscard]] auto operator[](size_t idx) -> T &
	{
		return values[idx];
	}

	[[nodiscard]] auto operator[](size_t idx) const -> const T &
	{
		return values[idx];
	}

	// NOLINTNEXTLINE
	union
	{
		struct
		{
			T x;

			T y;

			T z;

			T w;
		};
		struct
		{
			T r;

			T g;

			T b;

			T a;
		};
		struct
		{
			std::array<T, 4> values;
		};
	};
};

using vec4 = vec4_impl<float>;

using ivec4 = vec4_impl<int32_t>;

using uvec4 = vec4_impl<uint32_t>;

} // namespace lt::math
