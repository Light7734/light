#include <engine/graphics/render_command.hpp>
#include <engine/platform/graphics/opengl/render_command.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <engine/platform/graphics/directx/render_command.hpp>
	#include <engine/platform/graphics/directx/shared_context.hpp>
#endif

#include <engine/graphics/graphics_context.hpp>

namespace Light {

Scope<RenderCommand> RenderCommand::Create(
    GLFWwindow *windowHandle,
    Ref<SharedContext> sharedContext
)
{
	switch (GraphicsContext::GetGraphicsAPI())
	{
	case GraphicsAPI::OpenGL: return CreateScope<glRenderCommand>(windowHandle);

	case GraphicsAPI::DirectX:
		LT_WIN(return CreateScope<dxRenderCommand>(
		                  (std::static_pointer_cast<dxSharedContext>)(sharedContext)
		);)

	default:
		ASSERT(
		    false,
		    "Invalid/unsupported 'GraphicsAPI' {}",
		    static_cast<uint32_t>(GraphicsContext::GetGraphicsAPI())
		);
		return nullptr;
	}
}

} // namespace Light
