export module math.vec3;

import preliminary;
import math.vec2;

namespace lt::math {

export template<typename T = f32>
struct vec3_impl
{
	constexpr vec3_impl(): x(), y(), z()
	{
	}

	constexpr explicit vec3_impl(T scalar): x(scalar), y(scalar), z(scalar)
	{
	}

	constexpr vec3_impl(T x, T y, T z): x(x), y(y), z(z)
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

	friend auto operator<<(std::ostream &stream, vec3_impl<T> value) -> std::ostream &
	{
		stream << value.x << ", " << value.y << ", " << value.z;
		return stream;
	}

	T x; // NOLINT

	T y; // NOLINT

	T z; // NOLINT
};

export using vec3 = vec3_impl<f32>;

export using ivec3 = vec3_impl<i32>;

export using uvec3 = vec3_impl<u32>;

} // namespace lt::math

template<typename T>
struct std::formatter<lt::math::vec3_impl<T>>
{
	constexpr auto parse(std::format_parse_context &context)
	{
		return context.begin();
	}

	auto format(const lt::math::vec3_impl<T> &val, std::format_context &context) const
	{
		return std::format_to(context.out(), "{}, {}, {}", val.x, val.y, val.z);
	}
};
