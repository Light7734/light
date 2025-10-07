#include <renderer/backend/vk/context/instance.hpp>
#include <renderer/frontend/context/instance.hpp>

namespace lt::renderer {

[[nodiscard]] /* static */ auto IInstance::get(Api target_api) -> IInstance *
{
	switch (target_api)
	{
	case Api::vulkan: return vk::Instance::get();
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}
}

} // namespace lt::renderer
