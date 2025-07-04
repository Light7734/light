#include "Framebuffer.hpp"

#include "OpenGL/glFramebuffer.hpp"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxFramebuffer.hpp"
	#include "DirectX/dxSharedContext.hpp"
#endif

#include "GraphicsContext.hpp"

namespace Light {

Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& specification, Ref<SharedContext> sharedContext)
{
	switch (GraphicsContext::GetGraphicsAPI())
	{
	case GraphicsAPI::OpenGL:
		return CreateRef<glFramebuffer>(specification);

	case GraphicsAPI::DirectX: LT_WIN(
		return CreateRef<dxFramebuffer>(specification, std::static_pointer_cast<dxSharedContext>(sharedContext));)

	default:
		ASSERT(false, "Invalid/unsupported 'GraphicsAPI' {}", static_cast<uint32_t>(GraphicsContext::GetGraphicsAPI()));
		return nullptr;
	}
}

} // namespace Light
