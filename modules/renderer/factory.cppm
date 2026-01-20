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
export import ecs.entity;

import preliminary;

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
    u32 max_frames_in_flight
) -> memory::Scope<IRenderer>;

[[nodiscard]] auto create_buffer(
    Api target_api,
    IDevice *device,
    IGpu *gpu,
    const IBuffer::CreateInfo &info
) -> memory::Scope<IBuffer>;

} // namespace lt::renderer

module :private;
namespace lt::renderer {

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
    IInstance *instance,
    const lt::ecs::Entity &surface_entity
) -> memory::Scope<ISurface>
{
	ensure(instance, "Failed to create renderer::ISurface: null instance");

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
	ensure(gpu, "Failed to create renderer::IDevice: null gpu");
	ensure(surface, "Failed to create renderer::IDevice: null surface");

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
    IDevice *device,
    IGpu *gpu,
    const IBuffer::CreateInfo &info
) -> memory::Scope<IBuffer>
{
	ensure(device, "Failed to create renderer::IBuffer: null device");
	ensure(gpu, "Failed to create renderer::IBuffer: null gpu");
	ensure(info.size > 0, "Failed to create renderer::IBuffer: null size");

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
	ensure(device, "Failed to create renderer::IPass: null device");

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
    u32 max_frames_in_flight
) -> memory::Scope<IRenderer>
{
	ensure(gpu, "Failed to create renderer::IRenderer: null gpu");
	ensure(device, "Failed to create renderer::IRenderer: null device");
	ensure(swapchain, "Failed to create renderer::IRenderer: null swapchain");
	ensure(
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
	ensure(
	    info.severities != IDebugger::MessageSeverity::none,
	    "Failed to create renderer::IDebugger: severities == none"
	);

	ensure(
	    info.types != IDebugger::MessageType::none,
	    "Failed to create renderer::IDebugger: types == none"
	);

	ensure(info.callback, "Failed to create vk::Messenger: null callback");

	switch (target_api)
	{
	case Api::vulkan: return memory::create_scope<vkb::Debugger>(instance, std::move(info));
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}

	std::unreachable();
}

} // namespace lt::renderer
