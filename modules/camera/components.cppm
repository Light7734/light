export module camera.components;

import preliminary;
import math.vec4;

export namespace lt::camera::components {

struct PerspectiveCamera
{
	f32 vertical_fov {};

	f32 near_plane {};

	f32 far_plane {};

	f32 aspect_ratio {};

	math::vec4 background_color;

	bool is_primary {};
};

} // namespace lt::camera::components
