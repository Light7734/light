#include <renderer/backend/vk/data/buffer.hpp>
#include <renderer/frontend/data/buffer.hpp>

namespace lt::renderer {


[[nodiscard]] /* static */ auto IBuffer::create(
    Api target_api,
    class IDevice *device,
    class IGpu *gpu,
    const CreateInfo &info
) -> memory::Scope<IBuffer>
{
	ensure(device, "Failed to create renderer::IBuffer: null device");
	ensure(gpu, "Failed to create renderer::IBuffer: null gpu");
	ensure(info.size > 0, "Failed to create renderer::IBuffer: null size");

	switch (target_api)
	{
	case Api::vulkan: return memory::create_scope<vk::Buffer>(device, gpu, info);
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}
}

} // namespace lt::renderer
