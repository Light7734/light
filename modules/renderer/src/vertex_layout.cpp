#include <debug/assertions.hpp>
#include <renderer/gl/vertex_layout.hpp>
#include <renderer/vertex_layout.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <renderer/dx/shared_context.hpp>
	#include <renderer/dx/vertex_layout.hpp>
#endif

#include <renderer/graphics_context.hpp>

namespace Light {

auto VertexLayout::create(
    const Ref<VertexBuffer> &vertexBuffer,
    const Ref<Shader> & /*shader*/,
    const std::vector<std::pair<std::string, VertexElementType>> &elements,
    const Ref<SharedContext> & /*sharedContext*/
) -> Ref<VertexLayout>
{
	switch (GraphicsContext::get_graphics_api())
	{
	case GraphicsAPI::OpenGL: return create_ref<glVertexLayout>(vertexBuffer, elements);

	case GraphicsAPI::DirectX:
		lt_win(return create_ref<dxVertexLayout>(
		                  shader,
		                  elements,
		                  std::static_pointer_cast<dxSharedContext>(sharedContext)
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

} // namespace Light
