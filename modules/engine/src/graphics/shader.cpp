#include <engine/graphics/shader.hpp>
#include <engine/platform/graphics/opengl/shader.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <engine/platform/graphics/directx/shader.hpp>
	#include <engine/platform/graphics/directx/shared_context.hpp>
#endif

#include <engine/graphics/graphics_context.hpp>

namespace Light {

Ref<Shader> Shader::Create(
    BasicFileHandle vertexFile,
    BasicFileHandle pixelFile,
    Ref<SharedContext> sharedContext
)
{
	// load shader source
	switch (GraphicsContext::GetGraphicsAPI())
	{
	case GraphicsAPI::OpenGL: return CreateRef<glShader>(vertexFile, pixelFile);

	case GraphicsAPI::DirectX:
		LT_WIN(return CreateRef<dxShader>(
		                  vertexFile,
		                  pixelFile,
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
