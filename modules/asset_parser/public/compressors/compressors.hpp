#pragma once

#include <cstdint>

namespace Assets {

enum class CompressionType : uint32_t // NOLINT(performance-enum-size)
{
	None,
	LZ4,
	LZ4HC,
};

}
