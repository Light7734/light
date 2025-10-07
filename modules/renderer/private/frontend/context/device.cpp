#include <renderer/backend/vk/context/device.hpp>
#include <renderer/frontend/context/device.hpp>

namespace lt::renderer {

[[nodiscard]] /* static */ auto IDevice::create(Api target_api, IGpu *gpu, ISurface *surface)
    -> memory::Scope<IDevice>
{
	ensure(gpu, "Failed to create renderer::IDevice: null gpu");
	ensure(surface, "Failed to create renderer::IDevice: null surface");

	switch (target_api)
	{
	case Api::vulkan: return memory::create_scope<vk::Device>(gpu, surface);
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}
}

} // namespace lt::renderer
