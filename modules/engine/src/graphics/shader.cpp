#include <engine/graphics/shader.hpp>
#include <engine/platform/graphics/opengl/shader.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <engine/platform/graphics/directx/shader.hpp>
	#include <engine/platform/graphics/directx/shared_context.hpp>
#endif

#include <engine/graphics/graphics_context.hpp>

namespace Light {

Ref<Shader> Shader::create(
    BasicFileHandle vertexFile,
    BasicFileHandle pixelFile,
    Ref<SharedContext> sharedContext
)
{
	// load shader source
	switch (GraphicsContext::get_graphics_api())
	{
	case GraphicsAPI::OpenGL: return create_ref<glShader>(vertexFile, pixelFile);

	case GraphicsAPI::DirectX:
		lt_win(return create_ref<dxShader>(
		                  vertexFile,
		                  pixelFile,
		                  std::static_pointer_cast<dxSharedContext>(sharedContext)
		);)

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
