export module math.vec2;

import preliminary;

export namespace lt::math {


/** A vector of TWO @a `T`s.
 *
 * @warn Does not defualt initialize to zero.
 */
template<typename T = f32>
    requires(std::is_arithmetic_v<T>)
struct vec2_impl
{
	using Underlying_T = T;

	constexpr vec2_impl() = default;

	constexpr explicit vec2_impl(T scalar): x(scalar), y(scalar)
	{
	}

	constexpr vec2_impl(T x, T y): x(x), y(y)
	{
	}

	[[nodiscard]] auto operator==(const vec2_impl<T> &other) const -> bool
	{
		return x == other.x && y == other.y;
	}

	[[nodiscard]] auto operator!=(const vec2_impl<T> &other) const -> bool
	{
		return !(*this == other);
	}

	[[nodiscard]] constexpr auto operator+(const vec2_impl<T> &other) const -> vec2_impl
	{
		return {
			x + other.x,
			y + other.y,
		};
	}

	[[nodiscard]] constexpr auto operator-(const vec2_impl<T> &other) const -> vec2_impl
	{
		return {
			x - other.x,
			y - other.y,
		};
	}

	[[nodiscard]] constexpr auto operator*(const vec2_impl<T> &other) const -> vec2_impl
	{
		return {
			x * other.x,
			y * other.y,
		};
	}

	[[nodiscard]] constexpr auto operator/(const vec2_impl<T> &other) const -> vec2_impl
	{
		return {
			x / other.x,
			y / other.y,
		};
	}

	T x;

	T y;
};

using vec2 = vec2_impl<f32>;

using vec2_f32 = vec2;
using vec2_f64 = vec2_impl<f64>;

using vec2_i8 = vec2_impl<i8>;
using vec2_i16 = vec2_impl<i16>;
using vec2_i32 = vec2_impl<i32>;
using vec2_i64 = vec2_impl<i64>;

using vec2_u8 = vec2_impl<u8>;
using vec2_u16 = vec2_impl<u16>;
using vec2_u32 = vec2_impl<u32>;
using vec2_u64 = vec2_impl<u64>;

} // namespace lt::math
