#include "Blender.hpp"

#include "OpenGL/glBlender.hpp"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxBlender.hpp"
	#include "DirectX/dxSharedContext.hpp"
#endif

#include "GraphicsContext.hpp"

namespace Light {

Scope<Blender> Blender::Create(Ref<SharedContext> sharedContext)
{
	switch (GraphicsContext::GetGraphicsAPI())
	{
	case GraphicsAPI::OpenGL:
		return CreateScope<glBlender>();

	case GraphicsAPI::DirectX: LT_WIN(
		return CreateScope<dxBlender>(std::static_pointer_cast<dxSharedContext>(sharedContext));)

	default:
		ASSERT(false, "Invalid/unsupported 'GraphicsAPI' {}", static_cast<uint32_t>(GraphicsContext::GetGraphicsAPI()));
	}
}

} // namespace Light
