export module renderer.vk.surface;

import preliminary;
import ecs.entity;
import ecs.registry;
import memory.null_on_move;
import math.vec2;
import surface.system;
import renderer.frontend;
import renderer.vk.instance;
import renderer.vk.api_wrapper;

export namespace lt::renderer::vkb {

class Surface: public ISurface
{
public:
	Surface(IInstance *instance, const ecs::Entity &surface_entity);

	[[nodiscard]] auto vk() -> vk::Surface &
	{
		return m_surface;
	}

	[[nodiscard]] auto get_framebuffer_size() const -> math::vec2_u32 override;

private:
	vk::Surface m_surface;

	ecs::Entity m_surface_entity;
};

} // namespace lt::renderer::vkb

module :private;
namespace lt::renderer::vkb {

Surface::Surface(IInstance *instance, const ecs::Entity &surface_entity)
    : m_surface_entity(surface_entity)
{
	const auto &component = surface_entity.get<surface::SurfaceComponent>();


#if defined(LIGHT_PLATFORM_LINUX)
	ensure(
	    component.get_native_data().display,
	    "Failed to initialize vk::Surface: null Wayland display"
	);
	ensure(
	    component.get_native_data().surface,
	    "Failed to initialize vk::Surface: null Wayland surface"
	);

	m_surface = vk::Surface(
	    static_cast<Instance *>(instance)->vk(),
	    vk::Surface::CreateInfo {
	        .display = component.get_native_data().display,
	        .surface = component.get_native_data().surface,
	    }
	);

#elif defined(LIGHT_PLATFORM_WINDOWS)
	ensure(
	    component.get_native_data().window,
	    "Failed to initialize vk::Surface: null win32 window handle"
	);

	m_surface = vk::Surface(
	    static_cast<Instance *>(instance)->vk(),
	    vk::Surface::CreateInfo {
	        .window = component.get_native_data().window,
	    }
	);

#else
	#error "Unsupported platform"

#endif
}

[[nodiscard]] auto Surface::get_framebuffer_size() const -> math::vec2_u32
{
	return m_surface_entity.get<surface::SurfaceComponent>().get_resolution();
}

} // namespace lt::renderer::vkb
