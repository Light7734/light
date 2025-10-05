#pragma once

#include <cstdint>

namespace lt::bitwise {

/* bit-wise */
constexpr auto bit(uint32_t x) -> uint32_t
{
	return 1u << x;
}

} // namespace lt::bitwise
