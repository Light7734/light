#include <engine/graphics/render_command.hpp>
#include <engine/platform/graphics/opengl/render_command.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <engine/platform/graphics/directx/render_command.hpp>
	#include <engine/platform/graphics/directx/shared_context.hpp>
#endif

#include <engine/graphics/graphics_context.hpp>

namespace Light {

auto RenderCommand::create(GLFWwindow *windowHandle, Ref<SharedContext> sharedContext)
    -> Scope<RenderCommand>
{
	switch (GraphicsContext::get_graphics_api())
	{
	case GraphicsAPI::OpenGL: return create_scope<glRenderCommand>(windowHandle);

	case GraphicsAPI::DirectX:
		lt_win(return create_scope<dxRenderCommand>(
		                  (std::static_pointer_cast<dxSharedContext>)(sharedContext)
		);)

		    default
		    : lt_assert(
		          false,
		          "Invalid/unsupported 'GraphicsAPI' {}",
		          static_cast<uint32_t>(GraphicsContext::get_graphics_api())
		      );
		return nullptr;
	}
}

} // namespace Light
