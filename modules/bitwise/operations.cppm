export module bitwise;
import preliminary;

namespace lt::bitwise {

/* bit-wise */
export constexpr auto bit(u32 x) -> u32
{
	return u32 { 1u } << x;
}

} // namespace lt::bitwise
