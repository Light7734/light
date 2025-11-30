export module bitwise;
import std;

namespace lt::bitwise {

/* bit-wise */
export constexpr auto bit(std::uint32_t x) -> std::uint32_t
{
	return 1u << x;
}

} // namespace lt::bitwise
