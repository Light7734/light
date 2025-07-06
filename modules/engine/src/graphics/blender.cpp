#include <engine/graphics/blender.hpp>
#include <engine/platform/graphics/opengl/blender.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <engine/platform/graphics/directx/blender.hpp>
	#include <engine/platform/graphics/directx/sharedcontext.hpp>
#endif

#include <engine/graphics/graphics_context.hpp>

namespace Light {

auto Blender::create(const Ref<SharedContext>&  /*sharedContext*/) -> Scope<Blender>
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
