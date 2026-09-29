// @note: "Camera" is not in the renderer since camera logic can get extremely complex once we add
// all the bells and whistles.

export module camera.components;

import preliminary;
import math.vec4;

export namespace lt::camera::components {

/** A component holding perspective camera information */
struct PerspectiveCamera
{
	f32 vertical_fov;

	f32 near_plane;

	f32 far_plane;

	f32 aspect_ratio;

	math::vec4 background_color;

	bool is_primary;
};

} // namespace lt::camera::components
