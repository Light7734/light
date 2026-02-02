export module math.vec2;

import preliminary;

export namespace lt::math {

template<typename T = f32>
    requires(std::is_arithmetic_v<T>)
struct vec2_impl
{
	using Underlying_T = T;

	static constexpr auto num_elements = 2u;

	constexpr vec2_impl(): x(), y()
	{
	}

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

	[[nodiscard]] constexpr auto operator[](u8 idx) -> T &
	{
		debug_check(idx < num_elements, "vec2 out of bound access: {}", idx);
		return ((T *)this)[idx];
	}

	[[nodiscard]] constexpr auto operator[](u8 idx) const -> const T &
	{
		debug_check(idx < num_elements, "vec2 out of bound access: {}", idx);
		return ((T *)this)[idx];
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

export template<typename T>
struct std::formatter<lt::math::vec2_impl<T>>
{
	constexpr auto parse(std::format_parse_context &context)
	{
		return context.begin();
	}

	auto format(const lt::math::vec2_impl<T> &val, std::format_context &context) const
	{
		return std::format_to(context.out(), "{}, {}", val.x, val.y);
	}
};
