#include <engine/graphics/buffers.hpp>
#include <engine/graphics/shared_context.hpp>
#include <engine/platform/graphics/opengl/buffers.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <engine/platform/graphicsdirectx/buffers.hpp>
	#include <engine/platform/graphicsdirectx/shared_context.hpp>
#endif

#include <engine/graphics/graphics_context.hpp>

namespace Light {

//================================================== CONSTANT_BUFFER
//==================================================//
Scope<ConstantBuffer> ConstantBuffer::create(
    ConstantBufferIndex index,
    unsigned int size,
    Ref<SharedContext> sharedContext
)
{
	switch (GraphicsContext::get_graphics_api())
	{
	case GraphicsAPI::OpenGL: return create_scope<glConstantBuffer>(index, size);

	case GraphicsAPI::DirectX:
		lt_win(return create_scope<dxConstantBuffer>(
		                  index,
		                  size,
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
//================================================== CONSTANT_BUFFER
//==================================================//

//================================================== VERTEX_BUFFER
//==================================================//
Ref<VertexBuffer> VertexBuffer::create(
    float *vertices,
    unsigned int stride,
    unsigned int count,
    Ref<SharedContext> sharedContext
)
{
	switch (GraphicsContext::get_graphics_api())
	{
	case GraphicsAPI::OpenGL: return create_ref<glVertexBuffer>(vertices, stride, count);

	case GraphicsAPI::DirectX:
		lt_win(return create_ref<dxVertexBuffer>(
		                  vertices,
		                  stride,
		                  count,
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
//================================================== VERTEX_BUFFER
//==================================================//

//======================================== INDEX_BUFFER ========================================//
Ref<IndexBuffer> IndexBuffer::create(
    unsigned int *indices,
    unsigned int count,
    Ref<SharedContext> sharedContext
)
{
	switch (GraphicsContext::get_graphics_api())
	{
	case GraphicsAPI::OpenGL: return create_ref<glIndexBuffer>(indices, count);

	case GraphicsAPI::DirectX:
		lt_win(return create_ref<dxIndexBuffer>(
		                  indices,
		                  count,
		                  std::dynamic_pointer_cast<dxSharedContext>(sharedContext)
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
//======================================== INDEX_BUFFER ========================================//

} // namespace Light
