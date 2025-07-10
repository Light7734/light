#include <debug/assertions.hpp>
#include <renderer/gl/render_command.hpp>
#include <renderer/render_command.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <renderer/dx/render_command.hpp>
	#include <renderer/dx/shared_context.hpp>
#endif

#include <renderer/graphics_context.hpp>

namespace lt {

auto RenderCommand::create(GLFWwindow *windowHandle, const Ref<SharedContext> & /*sharedContext*/)
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
		    : ensure(
		          false,
		          "Invalid/unsupported 'GraphicsAPI' {}",
		          static_cast<uint32_t>(GraphicsContext::get_graphics_api())
		      );
		return nullptr;
	}
}

} // namespace lt
