#include <engine/graphics/blender.hpp>
#include <engine/platform/graphics/opengl/blender.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <engine/platform/graphics/directx/blender.hpp>
	#include <engine/platform/graphics/directx/sharedcontext.hpp>
#endif

#include <engine/graphics/graphics_context.hpp>

namespace Light {

Scope<Blender> Blender::Create(Ref<SharedContext> sharedContext)
{
	switch (GraphicsContext::GetGraphicsAPI())
	{
	case GraphicsAPI::OpenGL: return CreateScope<glBlender>();

	case GraphicsAPI::DirectX:
		LT_WIN(return CreateScope<dxBlender>(std::static_pointer_cast<dxSharedContext>(sharedContext
		));)

	default:
		ASSERT(
		    false,
		    "Invalid/unsupported 'GraphicsAPI' {}",
		    static_cast<uint32_t>(GraphicsContext::GetGraphicsAPI())
		);
	}
}

} // namespace Light
