export module lsd.math.vec3;

import lsd.math.vec2;
import lsd.primitives;
import lsd.str;

export namespace lt::lsd {

template<typename T>
struct vec3_impl
{
	constexpr vec3_impl() = default;


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

	// friend auto operator<<(std::ostream &stream, vec3_impl<T> value) -> std::ostream &
	// {
	// 	stream << value.x << ", " << value.y << ", " << value.z;
	// 	return stream;
	// }

	T x; // NOLINT

	T y; // NOLINT

	T z; // NOLINT
};

using vec3 = vec3_impl<f32>;

using dvec3 = vec3_impl<f32>;

using ivec3 = vec3_impl<i32>;

using uvec3 = vec3_impl<u32>;

} // namespace lt::lsd

template<typename T>
struct lt::lsd::formatter<lt::lsd::vec3_impl<T>>
{
	constexpr auto parse(lt::lsd::format_parse_context &context)
	{
		return context.begin();
	}

	auto format(const lt::lsd::vec3_impl<T> &val, lt::lsd::format_context &context) const
	{
		return lt::lsd::format_to(context.out(), "{}, {}, {}", val.x, val.y, val.z);
	}
};
