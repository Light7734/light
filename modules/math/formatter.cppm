export module math.formatter;

import preliminary;
import math.vec2;
import math.vec3;
import math.vec4;

export template<typename T>
struct std::formatter<lt::math::vec2_impl<T>>
{
	constexpr auto parse(std::format_parse_context &context)
	{
		return context.begin();
	}

	auto format(const lt::math::vec2_impl<T> &val, std::format_context &context) const
	{
		return std::format_to(context.out(), "{}, {}", val.x, val.y);
	}
};

export template<typename T>
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
