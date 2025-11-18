export module lsd.math.vec4;
import lsd.math.vec2;
import lsd.math.vec3;
import lsd.primitives;
import lsd.arr;
import lsd.str;

export namespace lt::lsd {

template<typename T>
struct vec4_impl
{
	constexpr vec4_impl() = default;

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
			lsd::arr<T, 4uz> values;
		};
	};
};

using vec4 = vec4_impl<f32>;

using ivec4 = vec4_impl<i32>;

using uvec4 = vec4_impl<u32>;

} // namespace lt::lsd

export template<typename T>
struct lt::lsd::formatter<lt::lsd::vec4_impl<T>>
{
	constexpr auto parse(lt::lsd::format_parse_context &context)
	{
		return context.begin();
	}

	auto format(const lt::lsd::vec4_impl<T> &val, lt::lsd::format_context &context) const
	{
		return lt::lsd::format_to(context.out(), "{}, {}, {}, {}", val.x, val.y, val.z, val.w);
	}
};
