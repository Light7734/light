export module lsd.math.mat4;
import lsd.math.vec2;
import lsd.math.vec3;
import lsd.math.vec4;
import lsd.primitives;
import lsd.arr;
import lsd.str;

export namespace lt::lsd {

template<typename T>
struct mat4_impl
{
	using Column_T = vec4_impl<T>;

	constexpr mat4_impl() = default;

	constexpr explicit mat4_impl(T scalar = 0)
	    : values({
	          Column_T { scalar },
	          Column_T { scalar },
	          Column_T { scalar },
	          Column_T { scalar },
	      })
	{
	}

	// clang-format off
    constexpr mat4_impl(
        const T&  x0, const T&  y0, const T&  z0, const T&  w0,
        const T&  x1, const T&  y1, const T&  z1, const T&  w1,
        const T&  x2, const T&  y2, const T&  z2, const T&  w2,
        const T&  x3, const T&  y3, const T&  z3, const T&  w3
    )
	    // clang-format on
	    : values({ { x0, x1, x2, x3 }, { y0, y1, y2, y3 }, { z0, z1, z2, z3 }, { w0, w1, w2, w3 } })
	{
	}

	constexpr mat4_impl(
	    const Column_T &column_x,
	    const Column_T &column_y,
	    const Column_T &column_z,
	    const Column_T &column_w
	)
	    : values({ column_x, column_y, column_z, column_w })
	{
	}

	[[nodiscard]] static constexpr auto identity() -> mat4_impl<T>
	{
		return mat4_impl<T> {
			{ 1 }, {},    {},    {},    //
			{},    { 1 }, {},    {},    //
			{},    {},    { 1 }, {},    //
			{},    {},    {},    { 1 }, //
		};
	}

	[[nodiscard]] constexpr auto operator[](size_t idx) -> Column_T &
	{
		return values[idx];
	}

	[[nodiscard]] constexpr auto operator[](size_t idx) const -> const Column_T &
	{
		return values[idx];
	}

	[[nodiscard]] constexpr auto operator*(const mat4_impl<T> &other) const -> mat4_impl<T>
	{
		return mat4_impl<T> {};
	}

	[[nodiscard]] constexpr auto operator*(const vec4_impl<T> &other) const -> vec4_impl<T>
	{
		return vec4_impl<T> {};
	}

	lsd::arr<Column_T, 4uz> values; // NOLINT
};

template<typename T>
[[nodiscard]] auto translate(const vec3_impl<T> &value) -> mat4_impl<T>
{
	return mat4_impl<T> {};
}

template<typename T>
[[nodiscard]] auto rotate(f32 value, const vec3_impl<T> &xyz) -> mat4_impl<T>
{
	return mat4_impl<T> {};
}

template<typename T>
[[nodiscard]] auto scale(const vec3_impl<T> &value) -> mat4_impl<T>
{
	return mat4_impl<T> {};
}

template<typename T>
[[nodiscard]] auto inverse(const mat4_impl<T> &value) -> mat4_impl<T>
{
	return mat4_impl<T> {};
}

using mat4 = mat4_impl<f32>;

using imat4 = mat4_impl<i32>;

using umat4 = mat4_impl<u32>;

} // namespace lt::lsd
