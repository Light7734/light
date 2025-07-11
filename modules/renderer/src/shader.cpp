#include <asset_parser/assets/text.hpp>
#include <renderer/gl/shader.hpp>
#include <renderer/shader.hpp>

#ifdef LIGHT_PLATFORM_WINDOWS
	#include <renderer/dx/shader.hpp>
	#include <renderer/dx/shared_context.hpp>
#endif

#include <renderer/graphics_context.hpp>

namespace lt {

/* static */ auto Shader::create(
    Ref<Assets::TextAsset> vertex_asset,
    Ref<Assets::TextAsset> pixel_asset,
    const Ref<SharedContext> &shared_context
) -> Ref<Shader>
{
	std::ignore = shared_context;

	// load shader source
	switch (GraphicsContext::get_graphics_api())
	{
	case GraphicsAPI::OpenGL:
		return create_ref<glShader>(std::move(vertex_asset), std::move(pixel_asset));

	case GraphicsAPI::DirectX:
		lt_win(
		    return create_ref<dxShader>(
		               vertex_asset,
		               pixel_asset,
		               std::static_pointer_cast<dxSharedContext>(sharedContext)
		    );
		);

	default:
		ensure(
		    false,
		    "Invalid/unsupported 'GraphicsAPI' {}",
		    static_cast<uint32_t>(GraphicsContext::get_graphics_api())
		);
		return nullptr;
	}
}

} // namespace lt
