#include <logger/logger.hpp>
#include <renderer/gl/texture.hpp>
#include <renderer/texture.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <renderer/dx/shared_context.hpp>
	#include <renderer/dx/texture.hpp>
#endif

#include <renderer/graphics_context.hpp>
#include <utility>

namespace Light {

auto Texture::create(
    unsigned int width,
    unsigned int height,
    unsigned int components,
    unsigned char *pixels,
    const Ref<SharedContext> & /*sharedContext*/,
    const std::string &filePath
) -> Ref<Texture>
{
	switch (GraphicsContext::get_graphics_api())
	{
	case GraphicsAPI::OpenGL:
		return create_ref<glTexture>(width, height, components, pixels, filePath);

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
		    : lt_assert(
		          false,
		          "Invalid/unsupported 'GraphicsAPI' {}",
		          static_cast<uint32_t>(GraphicsContext::get_graphics_api())
		      );
		return nullptr;
	}
}

Texture::Texture(std::string filePath): m_file_path(std::move(filePath))
{
}

} // namespace Light
