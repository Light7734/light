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
	ResourceManager::load_shader(
	    "LT_ENGINE_RESOURCES_TINTED_TEXTURE_SHADER",
	    "data/assets/shaders/tinted_texture/ps.glsl",
	    "data/assets/shaders/tinted_texture/ps.glsl"
	);

	m_shader = ResourceManager::get_shader("LT_ENGINE_RESOURCES_TINTED_TEXTURE_SHADER");
	m_vertex_buffer = Ref<VertexBuffer>(
	    VertexBuffer::create(nullptr, sizeof(TintedTextureVertexData), maxVertices, sharedContext)
	);
	m_index_buffer = Ref<IndexBuffer>(
	    IndexBuffer::create(nullptr, (maxVertices / 4) * 6, sharedContext)
	);
	m_vertex_layout = Ref<VertexLayout>(VertexLayout::create(
	    m_vertex_buffer,
	    m_shader,
	    { { "POSITION", VertexElementType::Float4 },
	      { "TINT", VertexElementType::Float4 },
	      { "TEXCOORD", VertexElementType::Float2 } },
	    sharedContext
	));
}

auto TintedTextureRendererProgram::advance() -> bool
{
	m_map_current += 4;

	if (m_map_current >= m_map_end)
	{
		lt_log(warn, "'VertexBuffer' map went beyond 'MaxVertices': {}", m_max_vertices);
		return false;
	}

	m_quad_count++;
	return true;
}

void TintedTextureRendererProgram::map()
{
	m_quad_count = 0u;

	m_map_current = (TintedTextureRendererProgram::TintedTextureVertexData *)m_vertex_buffer->map();
	m_map_end = m_map_current + m_max_vertices;
}

void TintedTextureRendererProgram::un_map()
{
	m_vertex_buffer->un_map();
}

void TintedTextureRendererProgram::bind()
{
	m_shader->bind();
	m_vertex_layout->bind();
	m_vertex_buffer->bind();
	m_index_buffer->bind();
}

} // namespace Light
