#include <renderer/gl/graphics_context.hpp>
#include <renderer/graphics_context.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <renderer/dx/graphics_context.hpp>
	#include <renderer/dx/shared_context.hpp>
#endif

namespace lt {

GraphicsContext *GraphicsContext::s_context = nullptr;

GraphicsContext::~GraphicsContext() = default;

auto GraphicsContext::create(GraphicsAPI api, GLFWwindow *window_handle) -> Scope<GraphicsContext>
{
	delete s_context;

	if (api == GraphicsAPI::Default)
	{
#if defined(LIGHT_PLATFORM_WINDOWS)
		api = GraphicsAPI::DirectX;
#elif defined(LIGHT_PLATFORM_LINUX)
		api = GraphicsAPI::OpenGL;
#elif defined(LIGHT_PLATFORM_MAC)
		api = GraphicsAPI::OpenGL;
#endif
	}

	auto scope_gfx = Scope<GraphicsContext> {};
	switch (api)
	{
	// opengl
	case GraphicsAPI::OpenGL:
		scope_gfx = create_scope<glGraphicsContext>(window_handle);
		s_context = scope_gfx.get();
		break;
	// directx
	case GraphicsAPI::DirectX:
		lt_win(scope_gfx = create_scope<dxGraphicsContext>(window_handle);
		       s_context = scope_gfx.get();
		       break;)

		    default
		    : lt_assert(
		          false,
		          "Invalid/unsupported 'GraphicsAPI' {}",
		          // TODO(Light): Stringifier::graphics_api_to_string(api),
		          "TODO"
		      );
		return nullptr;
	}

	return std::move(scope_gfx);
}

} // namespace lt
