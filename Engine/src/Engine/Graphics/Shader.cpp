#include "Shader.hpp"

#include "OpenGL/glShader.hpp"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxShader.hpp"
	#include "DirectX/dxSharedContext.hpp"
#endif

#include "GraphicsContext.hpp"

namespace Light {

Ref<Shader> Shader::Create(BasicFileHandle vertexFile, BasicFileHandle pixelFile, Ref<SharedContext> sharedContext)
{
	// load shader source
	switch (GraphicsContext::GetGraphicsAPI())
	{
	case GraphicsAPI::OpenGL:
		return CreateRef<glShader>(vertexFile, pixelFile);

	case GraphicsAPI::DirectX: LT_WIN(
		return CreateRef<dxShader>(vertexFile, pixelFile, std::static_pointer_cast<dxSharedContext>(sharedContext));)

	default:
		ASSERT(false, "Invalid/unsupported 'GraphicsAPI' {}", static_cast<uint32_t>(GraphicsContext::GetGraphicsAPI()));
		return nullptr;
	}
}

} // namespace Light
