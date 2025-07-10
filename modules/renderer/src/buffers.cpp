#include <debug/assertions.hpp>
#include <renderer/buffers.hpp>
#include <renderer/gl/buffers.hpp>
#include <renderer/shared_context.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <renderer/dx/buffers.hpp>
	#include <renderer/dx/shared_context.hpp>
#endif

#include <renderer/graphics_context.hpp>

namespace lt {

auto ConstantBuffer::create(
    ConstantBufferIndex index,
    unsigned int size,
    const Ref<SharedContext> & /*sharedContext*/
) -> Scope<ConstantBuffer>
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

		    default
		    : ensure(
		          false,
		          "Invalid/unsupported 'GraphicsAPI' {}",
		          static_cast<uint32_t>(GraphicsContext::get_graphics_api())
		      );
		return nullptr;
	}
}

auto VertexBuffer::create(
    float *vertices,
    unsigned int stride,
    unsigned int count,
    const Ref<SharedContext> & /*sharedContext*/
) -> Ref<VertexBuffer>
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

		    default
		    : ensure(
		          false,
		          "Invalid/unsupported 'GraphicsAPI' {}",
		          static_cast<uint32_t>(GraphicsContext::get_graphics_api())
		      );
		return nullptr;
	}
}

auto IndexBuffer::create(
    unsigned int *indices,
    unsigned int count,
    const Ref<SharedContext> & /*sharedContext*/
) -> Ref<IndexBuffer>
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
