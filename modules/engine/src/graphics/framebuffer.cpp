#include <engine/graphics/framebuffer.hpp>
#include <engine/platform/graphics/opengl/framebuffers.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <engine/platform/graphics/directx/framebuffer.hpp>
	#include <engine/platform/graphics/directx/sharedcontext.hpp>
#endif

#include <engine/graphics/graphics_context.hpp>

namespace Light {

Ref<Framebuffer> Framebuffer::Create(
    const FramebufferSpecification &specification,
    Ref<SharedContext> sharedContext
)
{
	switch (GraphicsContext::GetGraphicsAPI())
	{
	case GraphicsAPI::OpenGL: return CreateRef<glFramebuffer>(specification);

	case GraphicsAPI::DirectX:
		LT_WIN(return CreateRef<dxFramebuffer>(
		                  specification,
		                  std::static_pointer_cast<dxSharedContext>(sharedContext)
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
