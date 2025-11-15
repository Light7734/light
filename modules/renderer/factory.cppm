export module renderer.factory;
export import renderer.frontend;
export import assets.shader;
export import renderer.vk.device;
export import renderer.vk.pass;
export import renderer.vk.instance;
export import renderer.vk.swapchain;
export import renderer.vk.renderer;
export import renderer.vk.buffer;
export import renderer.vk.gpu;
export import renderer.vk.debugger;
export import renderer.vk.surface;
export import memory.scope;
export import debug.assertions;
export import ecs.entity;
export import std;

export namespace lt::renderer {

[[nodiscard]] auto get_instance(Api target_api) -> IInstance *;

[[nodiscard]] auto create_debugger(Api target_api, IInstance *instance, IDebugger::CreateInfo info)
    -> memory::Scope<IDebugger>;

[[nodiscard]] auto create_surface(
    Api target_api,
    IInstance *instance,
    const ecs::Entity &surface_entity
) -> memory::Scope<ISurface>;

[[nodiscard]] auto create_gpu(Api target_api, IInstance *instance) -> memory::Scope<IGpu>;

[[nodiscard]] auto create_device(Api target_api, IGpu *gpu, ISurface *surface)
    -> memory::Scope<IDevice>;

[[nodiscard]] auto create_swapchain(Api target_api, ISurface *surface, IGpu *gpu, IDevice *device)
    -> memory::Scope<ISwapchain>;

[[nodiscard]] auto create_pass(
    lt::renderer::Api target_api,
    IDevice *device,
    const lt::assets::ShaderAsset &vertex_shader,
    const lt::assets::ShaderAsset &fragment_shader
) -> memory::Scope<IPass>;

[[nodiscard]] auto create_renderer(
    Api target_api,
    IGpu *gpu,
    IDevice *device,
    ISwapchain *swapchain,
    std::uint32_t max_frames_in_flight
) -> memory::Scope<IRenderer>;

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

	std::unreachable();
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

	std::unreachable();
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

	std::unreachable();
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

	std::unreachable();
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

	std::unreachable();
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

	std::unreachable();
}


[[nodiscard]] auto create_pass(
    lt::renderer::Api target_api,
    IDevice *device,
    const lt::assets::ShaderAsset &vertex_shader,
    const lt::assets::ShaderAsset &fragment_shader
) -> memory::Scope<IPass>
{
	debug::ensure(device, "Failed to create renderer::IPass: null device");

	switch (target_api)
	{
	case Api::vulkan:
		return memory::create_scope<vkb::Pass>(device, vertex_shader, fragment_shader);
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}

	std::unreachable();
}

[[nodiscard]] auto create_renderer(
    Api target_api,
    IGpu *gpu,
    IDevice *device,
    ISwapchain *swapchain,
    std::uint32_t max_frames_in_flight
) -> memory::Scope<IRenderer>
{
	debug::ensure(gpu, "Failed to create renderer::IRenderer: null gpu");
	debug::ensure(device, "Failed to create renderer::IRenderer: null device");
	debug::ensure(swapchain, "Failed to create renderer::IRenderer: null swapchain");
	debug::ensure(
	    std::clamp(
	        max_frames_in_flight,
	        IRenderer::frames_in_flight_lower_limit,
	        IRenderer::frames_in_flight_upper_limit
	    ) == max_frames_in_flight,
	    "Failed to initialize renderer::System: max_frames_in_flight ({}) not within bounds ({} -> "
	    "{}) ",
	    max_frames_in_flight,
	    IRenderer::frames_in_flight_lower_limit,
	    IRenderer::frames_in_flight_upper_limit
	);


	switch (target_api)
	{
	case Api::vulkan:
		return memory::create_scope<vkb::Renderer>(gpu, device, swapchain, max_frames_in_flight);
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}

	std::unreachable();
}

[[nodiscard]] auto create_debugger(Api target_api, IInstance *instance, IDebugger::CreateInfo info)
    -> memory::Scope<IDebugger>
{
	debug::ensure(
	    info.severities != IDebugger::MessageSeverity::none,
	    "Failed to create renderer::IDebugger: severities == none"
	);

	debug::ensure(
	    info.types != IDebugger::MessageType::none,
	    "Failed to create renderer::IDebugger: types == none"
	);

	debug::ensure(info.callback, "Failed to create vk::Messenger: null callback");

	switch (target_api)
	{
	case Api::vulkan: return memory::create_scope<vkb::Debugger>(instance, std::move(info));
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}

	std::unreachable();
}
