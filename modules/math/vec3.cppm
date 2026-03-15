export module math.vec3;

import preliminary;
import math.vec2;

export namespace lt::math {

/** A vector of THREE @a `T`s.
 *
 * @warn Does not defualt initialize to zero.
 */
template<typename T = f32>
    requires(std::is_arithmetic_v<T>)
struct vec3_impl
{
	using Underlying_T = T;

	constexpr vec3_impl() = default;

	constexpr explicit vec3_impl(T scalar): x(scalar), y(scalar), z(scalar)
	{
	}

	constexpr vec3_impl(T x, T y, T z): x(x), y(y), z(z)
	{
	}

	constexpr vec3_impl(vec2_impl<T> xy, T z): x(xy.x), y(xy.y), z(z)
	{
	}

	constexpr vec3_impl(T x, vec2_impl<T> yz): x(x), y(yz.x), z(yz.y)
	{
	}

	[[nodiscard]] auto operator==(const vec3_impl<T> &other) const -> bool
	{
		return x == other.x && y == other.y && z == other.z;
	}

	[[nodiscard]] auto operator!=(const vec3_impl<T> &other) const -> bool
	{
		return !(*this == other);
	}

	[[nodiscard]] constexpr auto operator+(const vec3_impl<T> &other) const -> vec3_impl
	{
		return {
			x + other.x,
			y + other.y,
			z + other.z,
		};
	}

	[[nodiscard]] constexpr auto operator-(const vec3_impl<T> &other) const -> vec3_impl
	{
		return {
			x - other.x,
			y - other.y,
			z - other.z,
		};
	}

	[[nodiscard]] constexpr auto operator*(const vec3_impl<T> &other) const -> vec3_impl
	{
		return {
			x * other.x,
			y * other.y,
			z * other.z,
		};
	}

	[[nodiscard]] constexpr auto operator/(const vec3_impl<T> &other) const -> vec3_impl
	{
		return {
			x / other.x,
			y / other.y,
			z / other.z,
		};
	}

	T x;

	T y;

	T z;
};

using vec3 = vec3_impl<f32>;

using vec3_f32 = vec3;
using vec3_f64 = vec3_impl<f64>;

using vec3_i8 = vec3_impl<i8>;
using vec3_i16 = vec3_impl<i16>;
using vec3_i32 = vec3_impl<i32>;
using vec3_i64 = vec3_impl<i64>;

using vec3_u8 = vec3_impl<u8>;
using vec3_u16 = vec3_impl<u16>;
using vec3_u32 = vec3_impl<u32>;
using vec3_u64 = vec3_impl<u64>;

} // namespace lt::math
