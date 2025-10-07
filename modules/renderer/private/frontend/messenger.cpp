#include <memory/scope.hpp>
#include <renderer/backend/vk/messenger.hpp>
#include <renderer/frontend/messenger.hpp>

namespace lt::renderer {

[[nodiscard]] /* static */ auto IMessenger::create(
    Api target_api,
    IInstance *instance,
    ecs::Entity entity
) -> memory::Scope<IMessenger>
{
	switch (target_api)
	{
	case Api::vulkan: return memory::create_scope<vk::Messenger>(instance, std::move(entity));
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}
}
} // namespace lt::renderer
