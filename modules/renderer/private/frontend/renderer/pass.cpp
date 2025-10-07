#include <assets/shader.hpp>
#include <renderer/backend/vk/renderer/pass.hpp>
#include <renderer/frontend/context/gpu.hpp>
#include <renderer/frontend/renderer/pass.hpp>

namespace lt::renderer {

[[nodiscard]] /* static */ auto IPass::create(
    lt::renderer::Api target_api,
    IDevice *device,
    ISwapchain *swapchain,
    const lt::assets::ShaderAsset &vertex_shader,
    const lt::assets::ShaderAsset &fragment_shader
) -> memory::Scope<IPass>
{
	ensure(device, "Failed to create renderer::IPass: null device");
	ensure(swapchain, "Failed to create renderer::IPass: null swapchain");

	switch (target_api)
	{
	case Api::vulkan:
		return memory::create_scope<vk::Pass>(device, swapchain, vertex_shader, fragment_shader);
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}
}

} // namespace lt::renderer
