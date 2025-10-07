// template<>
// struct std::formatter<VkExtent2D>
// {
// 	constexpr auto parse(std::format_parse_context &context)
// 	{
// 		return context.begin();
// 	}
//
// 	auto format(const VkExtent2D &val, std::format_context &context) const
// 	{
// 		return std::format_to(context.out(), "{}, {}", val.width, val.height);
// 	}
// };
//
// inline auto operator==(VkExtent2D lhs, VkExtent2D rhs) -> bool
// {
// 	return lhs.width == rhs.width && lhs.height == rhs.height;
// }
