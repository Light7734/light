export module renderer.backend.factory;
import memory.scope;
import renderer.frontend.device;
import renderer.backend.vk.device;
import debug.assertions;
import ecs.entity;
import renderer.backend.vk.instance;
import renderer.backend.vk.gpu;
import renderer.backend.vk.surface;
import renderer.frontend.instance;
import renderer.frontend.surface;
import renderer.frontend.gpu;
import renderer.api;
import std;

export namespace lt::renderer {

[[nodiscard]] auto get_instance(Api target_api) -> IInstance *;

[[nodiscard]] auto create_surface(
    Api target_api,
    IInstance *instance,
    const ecs::Entity &surface_entity
);

[[nodiscard]] auto create_gpu(Api target_api, IInstance *instance) -> memory::Scope<IGpu>;

} // namespace lt::renderer

module :private;
using namespace lt;
using namespace lt::renderer;

[[nodiscard]] auto get_instance(Api target_api) -> IInstance *
{
	switch (target_api)
	{
	case Api::vulkan: return vkb::Instance::get();
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}
}

[[nodiscard]] auto create_surface(
    Api target_api,
    class IInstance *instance,
    const lt::ecs::Entity &surface_entity
) -> memory::Scope<ISurface>
{
	debug::ensure(instance, "Failed to create renderer::ISurface: null instance");

	switch (target_api)
	{
	case Api::vulkan: return memory::create_scope<vkb::Surface>(instance, surface_entity);
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}
}

[[nodiscard]] auto create_gpu(Api target_api, IInstance *instance) -> memory::Scope<IGpu>
{
	switch (target_api)
	{
	case Api::vulkan: return memory::create_scope<vkb::Gpu>(instance);
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}
}

[[nodiscard]] auto create_device(Api target_api, IGpu *gpu, ISurface *surface)
    -> memory::Scope<IDevice>
{
	debug::ensure(gpu, "Failed to create renderer::IDevice: null gpu");
	debug::ensure(surface, "Failed to create renderer::IDevice: null surface");

	switch (target_api)
	{
	case Api::vulkan: return memory::create_scope<vkb::Device>(gpu, surface);
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}
