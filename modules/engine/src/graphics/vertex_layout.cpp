#include <engine/graphics/vertex_layout.hpp>
#include <engine/platform/graphics/opengl/vertex_layout.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <engine/platform/graphics/directx/shared_context.hpp>
	#include <engine/platform/graphics/directx/vertex_layout.hpp>
#endif

#include <engine/graphics/graphics_context.hpp>

namespace Light {

Ref<VertexLayout> VertexLayout::Create(
    Ref<VertexBuffer> vertexBuffer,
    Ref<Shader> shader,
    const std::vector<std::pair<std::string, VertexElementType>> &elements,
    Ref<SharedContext> sharedContext
)
{
	switch (GraphicsContext::GetGraphicsAPI())
	{
	case GraphicsAPI::OpenGL: return CreateRef<glVertexLayout>(vertexBuffer, elements);

	case GraphicsAPI::DirectX:
		LT_WIN(return CreateRef<dxVertexLayout>(
		                  shader,
		                  elements,
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
