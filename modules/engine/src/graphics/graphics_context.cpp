#include <engine/graphics/graphics_context.hpp>
#include <engine/platform/graphics/opengl/graphics_context.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <engine/platform/graphics/directx/graphics_context.hpp>
	#include <engine/platform/graphics/directx/shared_context.hpp>
#endif

#include <engine/graphics/blender.hpp>              // required for forward declaratio>
#include <engine/graphics/buffers.hpp>              // required for forward declaratio>
#include <engine/graphics/render_command.hpp>       // required for forward declaratio>
#include <engine/graphics/renderer.hpp>             // required for forward declaratio>
#include <engine/user_interface/user_interface.hpp> // required for forward declaratio>
#include <engine/utils/resource_manager.hpp>

namespace Light {

GraphicsContext *GraphicsContext::s_context = nullptr;

GraphicsContext::~GraphicsContext()
{
}

Scope<GraphicsContext> GraphicsContext::create(GraphicsAPI api, GLFWwindow *windowHandle)
{
	// terminate 'GraphicsContext' dependent classes
	if (s_context)
	{
		s_context->m_renderer.reset();
		s_context->m_user_interface.reset();

		delete s_context;
	}

	// determine the default api
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

	// create gfx context
	Scope<GraphicsContext> scopeGfx;
	switch (api)
	{
	// opengl
	case GraphicsAPI::OpenGL:
		scopeGfx = create_scope<glGraphicsContext>(windowHandle);
		s_context = scopeGfx.get();
		break;
	// directx
	case GraphicsAPI::DirectX:
		lt_win(scopeGfx = create_scope<dxGraphicsContext>(windowHandle); s_context = scopeGfx.get();
		       break;)

		    default
		    : lt_assert(
		          false,
		          "Invalid/unsupported 'GraphicsAPI' {}",
		          Stringifier::graphics_api_to_string(api)
		      );
		return nullptr;
	}

	// create 'GraphicsContext' dependent classes
	s_context->m_user_interface = UserInterface::create(windowHandle, s_context->m_shared_context);
	s_context->m_renderer = renderer::create(windowHandle, s_context->m_shared_context);

	// check
	lt_assert(s_context->m_user_interface, "Failed to create UserInterface");
	lt_assert(s_context->m_renderer, "Failed to create renderer");

	return std::move(scopeGfx);
}

} // namespace Light
