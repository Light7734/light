export module renderer.backend.vk.surface;
import debug.assertions;
import ecs.entity;
import ecs.registry;
import memory.null_on_move;
import math.vec2;
import surface.system;
import renderer.frontend.instance;
import renderer.backend.vk.instance;
import renderer.frontend.surface;
import renderer.backend.vk.library_wrapper;

namespace lt::renderer::vkb {

export class Surface: public ISurface
{
public:
	Surface(IInstance *instance, const ecs::Entity &surface_entity);

	[[nodiscard]] auto vk() -> vk::Surface &
	{
		return m_surface;
	}

	[[nodiscard]] auto get_framebuffer_size() const -> math::uvec2 override;

private:
	vk::Surface m_surface;

	ecs::Entity m_surface_entity;
};

} // namespace lt::renderer::vkb

module :private;
using namespace lt::renderer::vkb;

Surface::Surface(IInstance *instance, const ecs::Entity &surface_entity)
    : m_surface_entity(surface_entity)
{
	const auto &component = surface_entity.get<surface::SurfaceComponent>();

	debug::ensure(
	    component.get_native_data().display,
	    "Failed to initialize vk::Surface: null x-display"
	);
	debug::ensure(
	    component.get_native_data().window,
	    "Failed to initialize vk::Surface: null x-window"
	);

	m_surface = vk::Surface(
	    static_cast<Instance *>(instance)->vk(),
	    vk::Surface::XlibCreateInfo {
	        .display = component.get_native_data().display,
	        .window = component.get_native_data().window,
	    }
	);
}

[[nodiscard]] auto Surface::get_framebuffer_size() const -> math::uvec2
{
	return m_surface_entity.get<surface::SurfaceComponent>().get_resolution();
}
