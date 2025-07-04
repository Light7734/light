#include "Buffers.hpp"

#include "OpenGL/glBuffers.hpp"
#include "SharedContext.hpp"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxBuffers.hpp"
	#include "DirectX/dxSharedContext.hpp"
#endif

#include "GraphicsContext.hpp"

namespace Light {

//================================================== CONSTANT_BUFFER ==================================================//
Scope<ConstantBuffer> ConstantBuffer::Create(ConstantBufferIndex index, unsigned int size, Ref<SharedContext> sharedContext)
{
	switch (GraphicsContext::GetGraphicsAPI())
	{
	case GraphicsAPI::OpenGL:
		return CreateScope<glConstantBuffer>(index, size);

	case GraphicsAPI::DirectX: LT_WIN(
		return CreateScope<dxConstantBuffer>(index, size, std::static_pointer_cast<dxSharedContext>(sharedContext));)

	default:
		ASSERT(false, "Invalid/unsupported 'GraphicsAPI' {}", static_cast<uint32_t>(GraphicsContext::GetGraphicsAPI()));
		return nullptr;
	}
}
//================================================== CONSTANT_BUFFER ==================================================//

//================================================== VERTEX_BUFFER ==================================================//
Ref<VertexBuffer> VertexBuffer::Create(float* vertices, unsigned int stride, unsigned int count, Ref<SharedContext> sharedContext)
{
	switch (GraphicsContext::GetGraphicsAPI())
	{
	case GraphicsAPI::OpenGL:
		return CreateRef<glVertexBuffer>(vertices, stride, count);

	case GraphicsAPI::DirectX: LT_WIN(
		return CreateRef<dxVertexBuffer>(vertices, stride, count, std::static_pointer_cast<dxSharedContext>(sharedContext));)

	default:
		ASSERT(false, "Invalid/unsupported 'GraphicsAPI' {}", static_cast<uint32_t>(GraphicsContext::GetGraphicsAPI()));
		return nullptr;
	}
}
//================================================== VERTEX_BUFFER ==================================================//

//======================================== INDEX_BUFFER ========================================//
Ref<IndexBuffer> IndexBuffer::Create(unsigned int* indices, unsigned int count, Ref<SharedContext> sharedContext)
{
	switch (GraphicsContext::GetGraphicsAPI())
	{
	case GraphicsAPI::OpenGL:
		return CreateRef<glIndexBuffer>(indices, count);

	case GraphicsAPI::DirectX: LT_WIN(
		return CreateRef<dxIndexBuffer>(indices, count, std::dynamic_pointer_cast<dxSharedContext>(sharedContext));)

	default:
		ASSERT(false, "Invalid/unsupported 'GraphicsAPI' {}", static_cast<uint32_t>(GraphicsContext::GetGraphicsAPI()));
		return nullptr;
	}
}
//======================================== INDEX_BUFFER ========================================//

} // namespace Light
