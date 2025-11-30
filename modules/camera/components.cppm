export module camera.components;
import math.vec4;

namespace lt::camera::components {

export struct PerspectiveCamera
{
	float vertical_fov {};

	float near_plane {};

	float far_plane {};

	float aspect_ratio {};

	math::vec4 background_color;

	bool is_primary {};
};

} // namespace lt::camera::components
