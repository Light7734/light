export module math.vec2;

import preliminary;

namespace lt::math {

export template<typename T = f32>
    requires(std::is_arithmetic_v<T>)
struct vec2_impl
{
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
		debug_check(idx <= num_elements, "vec2 out of bound: {}", idx);
		return ((T *)this)[idx];
	}

	[[nodiscard]] constexpr auto operator[](u8 idx) const -> const T &
	{
		debug_check(idx < num_elements, "vec2 out of bound: {}", idx);
		return ((T *)this)[idx];
	}

	friend auto operator<<(std::ostream &stream, vec2_impl<T> value) -> std::ostream &
	{
		stream << value.x << ", " << value.y;
		return stream;
	}

	T x;

	T y;
};


export using vec2 = vec2_impl<f32>;

export using ivec2 = vec2_impl<i32>;

export using uvec2 = vec2_impl<u32>;

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
