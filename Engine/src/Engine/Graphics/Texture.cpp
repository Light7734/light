#include "Texture.hpp"

#include "OpenGL/glTexture.hpp"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxSharedContext.hpp"
	#include "DirectX/dxTexture.hpp"
#endif

#include "GraphicsContext.hpp"

namespace Light {

Ref<Texture> Texture::Create(unsigned int width, unsigned int height, unsigned int components, unsigned char* pixels, Ref<SharedContext> sharedContext, const std::string& filePath)
{
	switch (GraphicsContext::GetGraphicsAPI())
	{
	case GraphicsAPI::OpenGL:
		return CreateRef<glTexture>(width, height, components, pixels, filePath);

	case GraphicsAPI::DirectX: LT_WIN(
		return CreateRef<dxTexture>(width, height, components, pixels, std::static_pointer_cast<dxSharedContext>(sharedContext), filePath);)

	default:
		ASSERT(false, "Invalid/unsupported 'GraphicsAPI' {}", static_cast<uint32_t>(GraphicsContext::GetGraphicsAPI()));
		return nullptr;
	}
}

Texture::Texture(const std::string& filePath)
    : m_FilePath(filePath)
{
}

} // namespace Light
