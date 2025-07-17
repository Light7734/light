#pragma once

#include <math/vec3.hpp>
#include <math/vec4.hpp>

namespace lt::math {

template<typename T = float>
struct mat4_impl
{
	using Column_T = vec4_impl<T>;
	explicit mat4_impl(T scalar = 0)
	    : values(
	          {
	              Column_T { scalar },
	              Column_T { scalar },
	              Column_T { scalar },
	              Column_T { scalar },
	          }
	      )
	{
	}

	// clang-format off
    mat4_impl(
        const T&  x0, const T&  y0, const T&  z0, const T&  w0,
        const T&  x1, const T&  y1, const T&  z1, const T&  w1,
        const T&  x2, const T&  y2, const T&  z2, const T&  w2,
        const T&  x3, const T&  y3, const T&  z3, const T&  w3
    )
	    // clang-format on
	    : values({ { x0, x1, x2, x3 }, { y0, y1, y2, y3 }, { z0, z1, z2, z3 }, { w0, w1, w2, w3 } })
	{
	}

	mat4_impl(
	    const Column_T &column_x,
	    const Column_T &column_y,
	    const Column_T &column_z,
	    const Column_T &column_w
	)
	    : values({ column_x, column_y, column_z, column_w })
	{
	}

	[[nodiscard]] constexpr auto identity() -> mat4_impl<T>
	{
		return mat4_impl<T> {
			{ 1 }, {},    {},    {},    //
			{},    { 1 }, {},    {},    //
			{},    {},    { 1 }, {},    //
			{},    {},    {},    { 1 }, //
		};
	}

	[[nodiscard]] auto operator[](size_t idx) -> Column_T &
	{
		return values[idx];
	}

	[[nodiscard]] auto operator[](size_t idx) const -> const Column_T &
	{
		return values[idx];
	}

	[[nodiscard]] auto operator*(const mat4_impl<T> &other) const -> mat4_impl<T>
	{
		return mat4_impl<T> {};
	}

	[[nodiscard]] auto operator*(const vec4_impl<T> &other) const -> vec4_impl<T>
	{
		return vec4_impl<T> {};
	}

	std::array<Column_T, 4> values; // NOLINT
};

template<typename T>
[[nodiscard]] inline auto translate(const vec3_impl<T> &value) -> mat4_impl<T>
{
	return mat4_impl<T> {};
}

template<typename T>
[[nodiscard]] inline auto rotate(float value, const vec3_impl<T> &xyz) -> mat4_impl<T>
{
	return mat4_impl<T> {};
}

template<typename T>
[[nodiscard]] inline auto scale(const vec3_impl<T> &value) -> mat4_impl<T>
{
	return mat4_impl<T> {};
}

template<typename T>
[[nodiscard]] inline auto inverse(const mat4_impl<T> &value) -> mat4_impl<T>
{
	return mat4_impl<T> {};
}

using mat4 = mat4_impl<float>;

using imat4 = mat4_impl<int32_t>;

using umat4 = mat4_impl<uint32_t>;

} // namespace lt::math
