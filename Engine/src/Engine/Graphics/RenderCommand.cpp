#include "RenderCommand.hpp"

#include "OpenGL/glRenderCommand.hpp"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxRenderCommand.hpp"
	#include "DirectX/dxSharedContext.hpp"
#endif

#include "GraphicsContext.hpp"

namespace Light {

Scope<RenderCommand> RenderCommand::Create(GLFWwindow* windowHandle, Ref<SharedContext> sharedContext)
{
	switch (GraphicsContext::GetGraphicsAPI())
	{
	case GraphicsAPI::OpenGL:
		return CreateScope<glRenderCommand>(windowHandle);

	case GraphicsAPI::DirectX: LT_WIN(
		return CreateScope<dxRenderCommand>((std::static_pointer_cast<dxSharedContext>)(sharedContext));)

	default:
		ASSERT(false, "Invalid/unsupported 'GraphicsAPI' {}", static_cast<uint32_t>(GraphicsContext::GetGraphicsAPI()));
		return nullptr;
	}
}

} // namespace Light
