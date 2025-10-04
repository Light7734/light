#include <renderer/backend/vk/messenger.hpp>
#include <renderer/frontend/messenger.hpp>

namespace lt::renderer {

[[nodiscard]] /* static */ auto IMessenger::create(
    API target_api,
    IInstance *instance,
    ecs::Entity entity
) -> Scope<IMessenger>
{
	switch (target_api)
	{
	case API::Vulkan: return create_scope<vk::Messenger>(instance, std::move(entity));

	case API::Metal:
	case API::DirectX: throw std::runtime_error { "Invalid API" };
	}
}
} // namespace lt::renderer
