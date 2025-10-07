#include <renderer/backend/vk/context/gpu.hpp>
#include <renderer/frontend/context/gpu.hpp>

namespace lt::renderer {

[[nodiscard]] /* static */ auto IGpu::create(Api target_api, IInstance *instance)
    -> memory::Scope<IGpu>
{
	switch (target_api)
	{
	case Api::vulkan: return memory::create_scope<vk::Gpu>(instance);
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}
}

} // namespace lt::renderer
