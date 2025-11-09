export module renderer.factory;
import renderer.frontend;
import renderer.backend.vk.device;
import renderer.backend.vk.instance;
import renderer.backend.vk.swapchain;
import renderer.backend.vk.buffer;
import renderer.backend.vk.gpu;
import renderer.backend.vk.surface;
import memory.scope;
import debug.assertions;
import ecs.entity;
import std;

export namespace lt::renderer {

[[nodiscard]] auto get_instance(Api target_api) -> IInstance *;

[[nodiscard]] auto create_surface(
    Api target_api,
    IInstance *instance,
    const ecs::Entity &surface_entity
);

[[nodiscard]] auto create_gpu(Api target_api, IInstance *instance) -> memory::Scope<IGpu>;

[[nodiscard]] auto create_swapchain(Api target_api, ISurface *surface, IGpu *gpu, IDevice *device)
    -> memory::Scope<ISwapchain>;

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
}

[[nodiscard]] auto create_swapchain(Api target_api, ISurface *surface, IGpu *gpu, IDevice *device)
    -> memory::Scope<ISwapchain>
{
	switch (target_api)
	{
	case Api::vulkan: return memory::create_scope<vkb::Swapchain>(surface, gpu, device);
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}
}

[[nodiscard]] auto create_buffer(
    Api target_api,
    class IDevice *device,
    class IGpu *gpu,
    const IBuffer::CreateInfo &info
) -> memory::Scope<IBuffer>
{
	debug::ensure(device, "Failed to create renderer::IBuffer: null device");
	debug::ensure(gpu, "Failed to create renderer::IBuffer: null gpu");
	debug::ensure(info.size > 0, "Failed to create renderer::IBuffer: null size");

	switch (target_api)
	{
	case Api::vulkan: return memory::create_scope<vkb::Buffer>(device, gpu, info);
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}
}
