#pragma once

namespace lt::math {

template<typename T = float>
struct vec2_impl
{
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

	[[nodiscard]] auto operator*(float scalar) const -> vec2_impl
	{
		return {
			x * scalar,
			y * scalar,
		};
	}


	T x; // NOLINT

	T y; // NOLINT
};


using vec2 = vec2_impl<float>;

using ivec2 = vec2_impl<int32_t>;

using uvec2 = vec2_impl<uint32_t>;

} // namespace lt::math
