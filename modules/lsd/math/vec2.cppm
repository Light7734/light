export module lsd.math.vec2;
import lsd.primitives;
import lsd.str;

export namespace lt::lsd {

template<typename T>
struct vec2_impl
{
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

	[[nodiscard]] auto operator*(const vec2_impl<T> &other) const -> vec2_impl
	{
		return {
			x * other.x,
			y * other.y,
		};
	}

	[[nodiscard]] auto operator-(const vec2_impl<T> &other) const -> vec2_impl
	{
		return {
			x - other.x,
			y - other.y,
		};
	}

	[[nodiscard]] auto operator*(f32 scalar) const -> vec2_impl
	{
		return {
			x * scalar,
			y * scalar,
		};
	}

	T x; // NOLINT

	T y; // NOLINT
};


using vec2 = vec2_impl<f32>;

using dvec2 = vec2_impl<f64>;

using ivec2 = vec2_impl<i32>;

using uvec2 = vec2_impl<u32>;

} // namespace lt::lsd

export template<typename T>
struct lt::lsd::formatter<lt::lsd::vec2_impl<T>>
{
	constexpr auto parse(lt::lsd::format_parse_context &context)
	{
		return context.begin();
	}

	auto format(const lt::lsd::vec2_impl<T> &val, lt::lsd::format_context &context) const
	{
		return lt::lsd::format_to(context.out(), "{}, {}", val.x, val.y);
	}
};
