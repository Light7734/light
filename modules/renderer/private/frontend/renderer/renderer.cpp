#include <renderer/api.hpp>
#include <renderer/backend/vk/renderer/renderer.hpp>
#include <renderer/frontend/renderer/renderer.hpp>

namespace lt::renderer {

auto IRenderer::create(API target_api, IContext &context, uint32_t max_frames_in_flight)
    -> Scope<IRenderer>
{
	switch (target_api)
	{
	case API::Vulkan: return create_scope<vk::Renderer>(context, max_frames_in_flight);
	default: throw std::runtime_error { "Invalid API" };
	}
}

} // namespace lt::renderer
