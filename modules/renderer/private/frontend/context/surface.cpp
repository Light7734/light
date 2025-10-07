
#include <renderer/backend/vk/context/surface.hpp>
#include <renderer/frontend/context/surface.hpp>

namespace lt::renderer {

[[nodiscard]] /* static */ auto ISurface::create(
    Api target_api,
    IInstance *instance,
    const ecs::Entity &surface_entity
) -> memory::Scope<ISurface>
{
	ensure(instance, "Failed to create renderer::ISurface: null instance");

	switch (target_api)
	{
	case Api::vulkan: return memory::create_scope<vk::Surface>(instance, surface_entity);
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}
}

} // namespace lt::renderer
