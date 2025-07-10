#include <renderer/blender.hpp>
#include <renderer/gl/blender.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <renderer/dx/blender.hpp>
	#include <renderer/dx/sharedcontext.hpp>
#endif

#include <renderer/graphics_context.hpp>

namespace Light {

auto Blender::create(const Ref<SharedContext> & /*sharedContext*/) -> Scope<Blender>
{
	switch (GraphicsContext::get_graphics_api())
	{
	case GraphicsAPI::OpenGL: return create_scope<glBlender>();

	case GraphicsAPI::DirectX:
		lt_win(return create_scope<dxBlender>(
		                  std::static_pointer_cast<dxSharedContext>(sharedContext)
		);)

		    default
		    : lt_assert(
		          false,
		          "Invalid/unsupported 'GraphicsAPI' {}",
		          static_cast<uint32_t>(GraphicsContext::get_graphics_api())
		      );
	}
}

} // namespace Light
