export module renderer.api;
import std;

namespace lt::renderer {

export enum class Api: std::uint8_t {
	none = 0u,

	vulkan,
	direct_x,
	metal,
};

}
