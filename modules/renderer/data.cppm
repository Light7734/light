export module renderer.data;

#include <math/mat4.hpp>

namespace lt::renderer {

export struct FrameConstants
{
	math::mat4 view_projection;
};

} // namespace lt::renderer
