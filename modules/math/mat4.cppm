export module math.mat4;

import preliminary;
import math.vec2;
import math.vec3;
import math.vec4;

export namespace lt::math {

/** A 4 by 4 matrix, column major order
 *
 * @todo(Light): Use std::simd when it's implemented. */
template<typename T = f32>
    requires(std::is_arithmetic_v<T>)
struct mat4_impl
{
	using Column_T = vec4_impl<T>;

	using Underlying_T = Column_T::Underlying_T;

	static constexpr auto num_elements = 4u * 4u;

	constexpr mat4_impl() = default;

	constexpr explicit mat4_impl(T scalar)
	    : values(
	          {
	              Column_T { scalar },
	              Column_T { scalar },
	              Column_T { scalar },
	              Column_T { scalar },
	          }
	      )
	{
	}

	constexpr mat4_impl(
	    // clang-format off
        const T& x0, const T& x1, const T& x2, const T& x3,
        const T& y0, const T& y1, const T& y2, const T& y3,
        const T& z0, const T& z1, const T& z2, const T& z3,
        const T& w0, const T& w1, const T& w2, const T& w3)
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

	[[nodiscard]] constexpr auto operator*(const mat4_impl<T> &other) const -> mat4_impl<T>
	{
		const auto &[a_x, a_y, a_z, a_w] = values;
		const auto &[b_x, b_y, b_z, b_w] = other.values;

		return mat4_impl<T>(
		    // X column
		    a_x.x * b_x.x + a_y.x * b_x.y + a_z.x * b_x.z + a_w.x * b_x.w,
		    a_x.y * b_x.x + a_y.y * b_x.y + a_z.y * b_x.z + a_w.y * b_x.w,
		    a_x.z * b_x.x + a_y.z * b_x.y + a_z.z * b_x.z + a_w.z * b_x.w,
		    a_x.w * b_x.x + a_y.w * b_x.y + a_z.w * b_x.z + a_w.w * b_x.w,

		    // Y column
		    a_x.x * b_y.x + a_y.x * b_y.y + a_z.x * b_y.z + a_w.x * b_y.w,
		    a_x.y * b_y.x + a_y.y * b_y.y + a_z.y * b_y.z + a_w.y * b_y.w,
		    a_x.z * b_y.x + a_y.z * b_y.y + a_z.z * b_y.z + a_w.z * b_y.w,
		    a_x.w * b_y.x + a_y.w * b_y.y + a_z.w * b_y.z + a_w.w * b_y.w,

		    // Z column
		    a_x.x * b_z.x + a_y.x * b_z.y + a_z.x * b_z.z + a_w.x * b_z.w,
		    a_x.y * b_z.x + a_y.y * b_z.y + a_z.y * b_z.z + a_w.y * b_z.w,
		    a_x.z * b_z.x + a_y.z * b_z.y + a_z.z * b_z.z + a_w.z * b_z.w,
		    a_x.w * b_z.x + a_y.w * b_z.y + a_z.w * b_z.z + a_w.w * b_z.w,

		    // W column
		    a_x.x * b_w.x + a_y.x * b_w.y + a_z.x * b_w.z + a_w.x * b_w.w,
		    a_x.y * b_w.x + a_y.y * b_w.y + a_z.y * b_w.z + a_w.y * b_w.w,
		    a_x.z * b_w.x + a_y.z * b_w.y + a_z.z * b_w.z + a_w.z * b_w.w,
		    a_x.w * b_w.x + a_y.w * b_w.y + a_z.w * b_w.z + a_w.w * b_w.w
		);
	}

	[[nodiscard]] constexpr auto operator[](size_t idx) -> Column_T &
	{
		debug_check(idx < num_elements, "mat4 out of bound access: {}", idx);
		return values[idx];
	}

	[[nodiscard]] constexpr auto operator[](size_t idx) const -> const Column_T &
	{
		return values[idx];
	}

	[[nodiscard]] static constexpr auto transpose(const mat4_impl<T> &mat) -> mat4_impl<T>
	{
		const auto &[x, y, z, w] = mat.values;
		return mat4_impl<T> {
			x.x, y.x, z.x, w.x, x.y, y.y, z.y, w.y, x.z, y.z, z.z, w.z, x.w, y.w, z.w, w.w,
		};
	}

	[[nodiscard]] static constexpr auto translate(const vec3_impl<T> &vec) -> mat4_impl<T>
	{
		return mat4_impl<T>(
		    T { 1 },
		    T { 0 },
		    T { 0 },
		    T { 0 },

		    T { 0 },
		    T { 1 },
		    T { 0 },
		    T { 0 },

		    T { 0 },
		    T { 0 },
		    T { 1 },
		    T { 0 },

		    vec.x,
		    vec.y,
		    vec.z,
		    T { 1 }
		);
	}

	[[nodiscard]] static constexpr auto scale(const vec3_impl<T> &vec) -> mat4_impl<T>
	{
		return mat4_impl<T>(
		    vec.x,
		    T { 0 },
		    T { 0 },
		    T { 0 },

		    T { 0 },
		    vec.y,
		    T { 0 },
		    T { 0 },

		    T { 0 },
		    T { 0 },
		    vec.z,
		    T { 0 },

		    T { 0 },
		    T { 0 },
		    T { 0 },
		    T { 1 }
		);
	}

	std::array<Column_T, 4u> values;
};

using mat4 = mat4_impl<f32>;

using mat4_f32 = mat4;
using mat4_f64 = mat4_impl<f64>;

using mat4_i8 = mat4_impl<i8>;
using mat4_i16 = mat4_impl<i16>;
using mat4_i32 = mat4_impl<i32>;
using mat4_i64 = mat4_impl<i64>;

using mat4_u8 = mat4_impl<u8>;
using mat4_u16 = mat4_impl<u16>;
using mat4_u32 = mat4_impl<u32>;
using mat4_u64 = mat4_impl<u64>;

} // namespace lt::math
