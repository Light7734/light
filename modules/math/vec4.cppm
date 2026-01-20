export module math.vec4;

import preliminary;
import math.vec2;
import math.vec3;

namespace lt::math {

export template<typename T = f32>
struct vec4_impl
{
	static constexpr auto num_elements = 4u;

	constexpr vec4_impl(): x(), y(), z(), w()
	{
	}

	constexpr explicit vec4_impl(T scalar): x(scalar), y(scalar), z(scalar), w(scalar)
	{
	}

	constexpr vec4_impl(T x, T y, T z, T w): x(x), y(y), z(z), w(w)
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

	[[nodiscard]] constexpr auto operator-(const vec4_impl<T> &other) const -> vec4_impl
	{
		return {
			x - other.x,
			y - other.y,
			z - other.z,
			w - other.w,
		};
	}

	[[nodiscard]] constexpr auto operator[](u8 idx) -> T &
	{
		// TODO(Light): Use contract
		ensure(idx <= num_elements, "vec4 out of bound: {}", idx);
		return ((T *)this)[idx];
	}

	[[nodiscard]] constexpr auto operator[](u8 idx) const -> const T &
	{
		// TODO(Light): Use contract
		ensure(idx < num_elements, "vec4 out of bound: {}", idx);
		return ((T *)this)[idx];
	}

	friend auto operator<<(std::ostream &stream, vec4_impl<T> value) -> std::ostream &
	{
		stream << value.x << ", " << value.y << ", " << value.z << ", " << value.w;
		return stream;
	}

	T x;

	T y;

	T z;

	T w;
};

export using vec4 = vec4_impl<f32>;

export using ivec4 = vec4_impl<i32>;

export using uvec4 = vec4_impl<u32>;

} // namespace lt::math

export template<typename T>
struct std::formatter<lt::math::vec4_impl<T>>
{
	constexpr auto parse(std::format_parse_context &context)
	{
		return context.begin();
	}

	auto format(const lt::math::vec4_impl<T> &val, std::format_context &context) const
	{
		return std::format_to(context.out(), "{}, {}, {}, {}", val.x, val.y, val.z, val.w);
	}
};
