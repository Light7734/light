#include <memory/scope.hpp>
#include <renderer/api.hpp>
#include <renderer/backend/vk/renderer/renderer.hpp>
#include <renderer/frontend/renderer/renderer.hpp>

namespace lt::renderer {

[[nodiscard]] /* static */ auto IRenderer::create(
    Api target_api,
    IDevice *device,
    ISwapchain *swapchain,
    uint32_t max_frames_in_flight
) -> memory::Scope<IRenderer>
{
	ensure(device, "Failed to create renderer::IRenderer: null device");
	ensure(swapchain, "Failed to create renderer::IRenderer: null swapchain");
	ensure(
	    std::clamp(max_frames_in_flight, frames_in_flight_lower_limit, frames_in_flight_upper_limit)
	        == max_frames_in_flight,
	    "Failed to initialize renderer::System: max_frames_in_flight ({}) not within bounds ({} -> "
	    "{}) ",
	    max_frames_in_flight,
	    frames_in_flight_lower_limit,
	    frames_in_flight_upper_limit
	);


	switch (target_api)
	{
	case Api::vulkan:
		return memory::create_scope<vk::Renderer>(device, swapchain, max_frames_in_flight);
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}
}

} // namespace lt::renderer
