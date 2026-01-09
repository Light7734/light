export module math.vec4;
import math.vec2;
import debug.assertions;
import math.vec3;
import std;

namespace lt::math {

export template<typename T = float>
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

	[[nodiscard]] constexpr auto operator[](std::uint8_t idx) -> T &
	{
		// TODO(Light): Use contract
		debug::ensure(idx <= num_elements, "vec4 out of bound: {}", idx);
		return ((T *)this)[idx];
	}

	[[nodiscard]] constexpr auto operator[](std::uint8_t idx) const -> const T &
	{
		// TODO(Light): Use contract
		debug::ensure(idx < num_elements, "vec4 out of bound: {}", idx);
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

export using vec4 = vec4_impl<float>;

export using ivec4 = vec4_impl<std::int32_t>;

export using uvec4 = vec4_impl<std::uint32_t>;

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
