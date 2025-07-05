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
    : m_shader(nullptr)
    , m_index_buffer(nullptr)
    , m_vertex_layout(nullptr)
    , m_map_current(nullptr)
    , m_map_end(nullptr)
    , m_quad_count(0u)
    , m_max_vertices(maxVertices)
{
	// #todo: don't use relative path
	ResourceManager::LoadShader(
	    "LT_ENGINE_RESOURCES_TINTED_TEXTURE_SHADER",
	    "Assets/Shaders/TintedTexture/TintedTexture_VS.glsl",
	    "Assets/Shaders/TintedTexture/TintedTexture_PS.glsl"
	);

	m_shader = ResourceManager::GetShader("LT_ENGINE_RESOURCES_TINTED_TEXTURE_SHADER");
	m_vertex_buffer = Ref<VertexBuffer>(
	    VertexBuffer::Create(nullptr, sizeof(TintedTextureVertexData), maxVertices, sharedContext)
	);
	m_index_buffer = Ref<IndexBuffer>(
	    IndexBuffer::Create(nullptr, (maxVertices / 4) * 6, sharedContext)
	);
	m_vertex_layout = Ref<VertexLayout>(VertexLayout::Create(
	    m_vertex_buffer,
	    m_shader,
	    { { "POSITION", VertexElementType::Float4 },
	      { "TINT", VertexElementType::Float4 },
	      { "TEXCOORD", VertexElementType::Float2 } },
	    sharedContext
	));
}

bool TintedTextureRendererProgram::Advance()
{
	m_map_current += 4;

	if (m_map_current >= m_map_end)
	{
		LOG(warn, "'VertexBuffer' map went beyond 'MaxVertices': {}", m_max_vertices);
		return false;
	}

	m_quad_count++;
	return true;
}

void TintedTextureRendererProgram::Map()
{
	m_quad_count = 0u;

	m_map_current = (TintedTextureRendererProgram::TintedTextureVertexData *)m_vertex_buffer->Map();
	m_map_end = m_map_current + m_max_vertices;
}

void TintedTextureRendererProgram::UnMap()
{
	m_vertex_buffer->UnMap();
}

void TintedTextureRendererProgram::Bind()
{
	m_shader->Bind();
	m_vertex_layout->Bind();
	m_vertex_buffer->Bind();
	m_index_buffer->Bind();
}

} // namespace Light
