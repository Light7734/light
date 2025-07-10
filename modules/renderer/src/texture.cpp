#include <logger/logger.hpp>
#include <renderer/gl/texture.hpp>
#include <renderer/texture.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <renderer/dx/shared_context.hpp>
	#include <renderer/dx/texture.hpp>
#endif

#include <renderer/graphics_context.hpp>

namespace lt {

/* static */ auto Texture::create(
    Ref<Assets::TextureAsset> asset,
    const Ref<SharedContext> &shared_context
) -> Ref<Texture>
{
	switch (GraphicsContext::get_graphics_api())
	{
	case GraphicsAPI::OpenGL: return create_ref<glTexture>(std::move(asset));

	case GraphicsAPI::DirectX:
		lt_win(return create_ref<dxTexture>(
		                  width,
		                  height,
		                  components,
		                  pixels,
		                  std::static_pointer_cast<dxSharedContext>(sharedContext),
		                  filePath
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
