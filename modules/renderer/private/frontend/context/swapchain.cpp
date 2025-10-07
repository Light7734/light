#include <renderer/backend/vk/context/swapchain.hpp>
#include <renderer/frontend/context/swapchain.hpp>

namespace lt::renderer {

[[nodiscard]] /* static */ auto ISwapchain::create(
    Api target_api,
    ISurface *surface,
    IGpu *gpu,
    IDevice *device
) -> memory::Scope<ISwapchain>
{
	switch (target_api)
	{
	case Api::vulkan: return memory::create_scope<vk::Swapchain>(surface, gpu, device);
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}
}


} // namespace lt::renderer
