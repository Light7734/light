export module math.vec4;

import preliminary;
import math.vec2;
import math.vec3;

export namespace lt::math {

/** A vector of THREE @a `T`s.
 *
 * @warn Does not defualt initialize to zero.
 */
template<typename T = f32>
    requires(std::is_arithmetic_v<T>)
struct vec4_impl
{
	using Underlying_T = T;

	constexpr vec4_impl() = default;

	constexpr explicit vec4_impl(T scalar): x(scalar), y(scalar), z(scalar), w(scalar)
	{
	}

	constexpr vec4_impl(T x, T y, T z, T w): x(x), y(y), z(z), w(w)
	{
	}

	constexpr vec4_impl(vec2_impl<T> xy, T z, T w): x(xy.x), y(xy.y), z(z), w(w)
	{
	}

	constexpr vec4_impl(T x, vec2_impl<T> yz, T w): x(x), y(yz.x), z(yz.y), w(w)
	{
	}

	constexpr vec4_impl(T x, T y, vec2_impl<T> zw): x(x), y(y), z(zw.x), w(zw.y)
	{
	}

	constexpr vec4_impl(vec2_impl<T> xy, vec2_impl<T> zw): x(xy.x), y(xy.y), z(zw.x), w(zw.y)
	{
	}

	constexpr vec4_impl(vec3_impl<T> xyz, T w): x(xyz.x), y(xyz.y), z(xyz.z), w(w)
	{
	}

	constexpr vec4_impl(T x, vec3_impl<T> yzw): x(x), y(yzw.x), z(yzw.y), w(yzw.z)
	{
	}

	[[nodiscard]] auto operator==(const vec4_impl<T> &other) const -> bool
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	[[nodiscard]] auto operator!=(const vec4_impl<T> &other) const -> bool
	{
		return !(*this == other);
	}

	[[nodiscard]] constexpr auto operator+(const vec4_impl<T> &other) const -> vec4_impl
	{
		return {
			x + other.x,
			y + other.y,
			z + other.z,
			w + other.w,
		};
	}

	[[nodiscard]] constexpr auto operator-(const vec4_impl<T> &other) const -> vec4_impl
	{
		return {
			x - other.x,
			y - other.y,
			z - other.z,
			w - other.w,
		};
	}

	[[nodiscard]] constexpr auto operator*(const vec4_impl<T> &other) const -> vec4_impl
	{
		return {
			x * other.x,
			y * other.y,
			z * other.z,
			w * other.w,
		};
	}

	[[nodiscard]] constexpr auto operator/(const vec4_impl<T> &other) const -> vec4_impl
	{
		return {
			x / other.x,
			y / other.y,
			z / other.z,
			w / other.w,
		};
	}

	T x;

	T y;

	T z;

	T w;
};

using vec4 = vec4_impl<f32>;

using vec4_f32 = vec4;
using vec4_f64 = vec4_impl<f64>;

using vec4_i8 = vec4_impl<i8>;
using vec4_i16 = vec4_impl<i16>;
using vec4_i32 = vec4_impl<i32>;
using vec4_i64 = vec4_impl<i64>;

using vec4_u8 = vec4_impl<u8>;
using vec4_u16 = vec4_impl<u16>;
using vec4_u32 = vec4_impl<u32>;
using vec4_u64 = vec4_impl<u64>;

} // namespace lt::math
