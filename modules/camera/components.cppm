export module camera.components;
import lsd;

export namespace lt::camera::components {

struct PerspectiveCamera
{
	f32 vertical_fov {};

	f32 near_plane {};

	f32 far_plane {};

	f32 aspect_ratio {};

	lsd::vec4 background_color;

	bool is_primary {};
};

} // namespace lt::camera::components
