export module renderer.vk.surface;

import preliminary;
import ecs.entity;
import ecs.registry;
import memory.null_on_move;
import memory.not_null;
import math.vec2;
import surface.system;
import renderer.vk.instance;
import renderer.vk.api_wrapper;

using lt::memory::NotNull;

export namespace lt::renderer::vkb {

class Surface
{
public:
	Surface(NotNull<Instance *> instance, ecs::Entity &surface_entity);

	[[nodiscard]] auto vk() -> vk::Surface &
	{
		return m_surface;
	}

	[[nodiscard]] auto get_framebuffer_size() const -> math::vec2_u32;

private:
	vk::Surface m_surface;

	ecs::Entity m_surface_entity;
};

} // namespace lt::renderer::vkb

namespace lt::renderer::vkb {

Surface::Surface(NotNull<Instance *> instance, ecs::Entity &surface_entity)
    : m_surface_entity(surface_entity)
{
	auto &component = surface_entity.get<surface::SurfaceComponent>();

	ensure(component.get_wl_display(), "Failed to initialize vk::Surface: null Wayland display");
	ensure(component.get_wl_surface(), "Failed to initialize vk::Surface: null Wayland surface");

	m_surface = vk::Surface(
	    instance->vk(),
	    vk::Surface::CreateInfo {
	        .display = component.get_wl_display(),
	        .surface = component.get_wl_surface(),

	    }
	);
}

[[nodiscard]] auto Surface::get_framebuffer_size() const -> math::vec2_u32
{
	return m_surface_entity.get<surface::SurfaceComponent>().get_resolution();
}

} // namespace lt::renderer::vkb
