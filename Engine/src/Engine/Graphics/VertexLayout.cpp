#include "VertexLayout.hpp"

#include "OpenGL/glVertexLayout.hpp"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxSharedContext.hpp"
	#include "DirectX/dxVertexLayout.hpp"
#endif

#include "GraphicsContext.hpp"

namespace Light {

Ref<VertexLayout> VertexLayout::Create(Ref<VertexBuffer> vertexBuffer, Ref<Shader> shader, const std::vector<std::pair<std::string, VertexElementType>>& elements, Ref<SharedContext> sharedContext)
{
	switch (GraphicsContext::GetGraphicsAPI())
	{
	case GraphicsAPI::OpenGL:
		return CreateRef<glVertexLayout>(vertexBuffer, elements);

	case GraphicsAPI::DirectX: LT_WIN(
		return CreateRef<dxVertexLayout>(shader, elements, std::static_pointer_cast<dxSharedContext>(sharedContext));)

	default:
		ASSERT(false, "Invalid/unsupported 'GraphicsAPI' {}", static_cast<uint32_t>(GraphicsContext::GetGraphicsAPI()));
		return nullptr;
	}
}

} // namespace Light
