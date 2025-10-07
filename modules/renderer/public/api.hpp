#pragma once

namespace lt::renderer {

enum class Api : uint8_t
{
	none = 0,

	vulkan,
	direct_x,
	metal,
};

}
