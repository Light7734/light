#include <engine/camera/camera.hpp>
#include <engine/graphics/buffers.hpp>
#include <engine/graphics/renderer_programs/tinted_texture.hpp>
#include <engine/graphics/shader.hpp>
#include <engine/graphics/vertex_layout.hpp>
#include <engine/utils/resource_manager.hpp>

namespace Light {

TintedTextureRendererProgram::TintedTextureRendererProgram(
    unsigned int maxVertices,
    Ref<SharedContext> sharedContext
)
    : m_Shader(nullptr)
    , m_IndexBuffer(nullptr)
    , m_VertexLayout(nullptr)
    , m_MapCurrent(nullptr)
    , m_MapEnd(nullptr)
    , m_QuadCount(0u)
    , m_MaxVertices(maxVertices)
{
	// #todo: don't use relative path
	ResourceManager::LoadShader(
	    "LT_ENGINE_RESOURCES_TINTED_TEXTURE_SHADER",
	    "Assets/Shaders/TintedTexture/TintedTexture_VS.glsl",
	    "Assets/Shaders/TintedTexture/TintedTexture_PS.glsl"
	);

	m_Shader = ResourceManager::GetShader("LT_ENGINE_RESOURCES_TINTED_TEXTURE_SHADER");
	m_VertexBuffer = Ref<VertexBuffer>(
	    VertexBuffer::Create(nullptr, sizeof(TintedTextureVertexData), maxVertices, sharedContext)
	);
	m_IndexBuffer = Ref<IndexBuffer>(
	    IndexBuffer::Create(nullptr, (maxVertices / 4) * 6, sharedContext)
	);
	m_VertexLayout = Ref<VertexLayout>(VertexLayout::Create(
	    m_VertexBuffer,
	    m_Shader,
	    { { "POSITION", VertexElementType::Float4 },
	      { "TINT", VertexElementType::Float4 },
	      { "TEXCOORD", VertexElementType::Float2 } },
	    sharedContext
	));
}

bool TintedTextureRendererProgram::Advance()
{
	m_MapCurrent += 4;

	if (m_MapCurrent >= m_MapEnd)
	{
		LOG(warn, "'VertexBuffer' map went beyond 'MaxVertices': {}", m_MaxVertices);
		return false;
	}

	m_QuadCount++;
	return true;
}

void TintedTextureRendererProgram::Map()
{
	m_QuadCount = 0u;

	m_MapCurrent = (TintedTextureRendererProgram::TintedTextureVertexData *)m_VertexBuffer->Map();
	m_MapEnd = m_MapCurrent + m_MaxVertices;
}

void TintedTextureRendererProgram::UnMap()
{
	m_VertexBuffer->UnMap();
}

void TintedTextureRendererProgram::Bind()
{
	m_Shader->Bind();
	m_VertexLayout->Bind();
	m_VertexBuffer->Bind();
	m_IndexBuffer->Bind();
}

} // namespace Light
