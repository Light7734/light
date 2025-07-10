#include <renderer/shader.hpp>
#include <renderer/gl/shader.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <renderer/dx/shader.hpp>
	#include <renderer/dx/shared_context.hpp>
#endif

#include <renderer/graphics_context.hpp>

namespace Light {

auto Shader::create(
    Assets::Blob vertex_blob,
    Assets::Blob pixel_blob,
    const Ref<SharedContext> &shared_context
) -> Ref<Shader>
{
	std::ignore = shared_context;

	// load shader source
	switch (GraphicsContext::get_graphics_api())
	{
	case GraphicsAPI::OpenGL:
		return create_ref<glShader>(std::move(vertex_blob), std::move(pixel_blob));

	case GraphicsAPI::DirectX:
		lt_win(return create_ref<dxShader>(
		                  vertexFile,
		                  pixelFile,
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
