#pragma once

#include <array>
#include <cstdint>

namespace lt::math {

template<typename T = float>
struct vec4_impl
{
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

	[[nodiscard]] constexpr auto operator[](size_t idx) -> T &
	{
		return values[idx];
	}

	[[nodiscard]] constexpr auto operator[](size_t idx) const -> const T &
	{
		return values[idx];
	}

	friend auto operator<<(std::ostream &stream, vec4_impl<T> value) -> std::ostream &
	{
		stream << value.x << ", " << value.y << ", " << value.z << ", " << value.w;
		return stream;
	}

	// NOLINTNEXTLINE
	union
	{
		struct
		{
			T x;

			T y;

			T z;

			T w;
		};
		struct
		{
			T r;

			T g;

			T b;

			T a;
		};
		struct
		{
			std::array<T, 4> values;
		};
	};
};

using vec4 = vec4_impl<float>;

using ivec4 = vec4_impl<int32_t>;

using uvec4 = vec4_impl<uint32_t>;

} // namespace lt::math

template<typename T>
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
