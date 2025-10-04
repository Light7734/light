#include <renderer/api.hpp>
#include <renderer/backend/vk/context/context.hpp>
#include <renderer/frontend/context/context.hpp>

namespace lt::renderer {

auto IContext::create(API target_api, const ecs::Entity &surface_entity) -> Scope<IContext>
{
	switch (target_api)
	{
	case API::Vulkan: return create_scope<vk::Context>(surface_entity);
	default: throw std::runtime_error { "Invalid API" };
	}
}

} // namespace lt::renderer
