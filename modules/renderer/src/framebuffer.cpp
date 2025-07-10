#include <renderer/framebuffer.hpp>
#include <renderer/gl/framebuffers.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <renderer/dx/framebuffer.hpp>
	#include <renderer/dx/sharedcontext.hpp>
#endif

#include <renderer/graphics_context.hpp>

namespace Light {

auto Framebuffer::create(
    const FramebufferSpecification &specification,
    const Ref<SharedContext>&  /*sharedContext*/
) -> Ref<Framebuffer>
{
	switch (GraphicsContext::get_graphics_api())
	{
	case GraphicsAPI::OpenGL: return create_ref<glFramebuffer>(specification);

	case GraphicsAPI::DirectX:
		lt_win(return create_ref<dxFramebuffer>(
		                  specification,
		                  std::static_pointer_cast<dxSharedContext>(sharedContext)
		););

	default:
		lt_assert(
		    false,
		    "Invalid/unsupported 'GraphicsAPI' {}",
		    static_cast<uint32_t>(GraphicsContext::get_graphics_api())
		);

		return nullptr;
	}
}

} // namespace Light
