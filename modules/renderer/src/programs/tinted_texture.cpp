#include <camera/camera.hpp>
#include <renderer/buffers.hpp>
#include <renderer/programs/tinted_texture.hpp>
#include <renderer/shader.hpp>
#include <renderer/vertex_layout.hpp>

namespace lt {

TintedTextureRendererProgram::TintedTextureRendererProgram(
    unsigned int max_vertices,
    const Ref<SharedContext> &shared_context,
    Ref<Shader> shader

)
    : m_shader(std::move(shader))
    , m_index_buffer(nullptr)
    , m_vertex_layout(nullptr)
    , m_max_vertices(max_vertices)
{
	m_vertex_buffer = Ref<VertexBuffer>(
	    VertexBuffer::create(nullptr, sizeof(TintedTextureVertexData), max_vertices, shared_context)
	);
	m_index_buffer = Ref<IndexBuffer>(
	    IndexBuffer::create(nullptr, (max_vertices / 4) * 6, shared_context)
	);
	m_vertex_layout = Ref<VertexLayout>(VertexLayout::create(
	    m_vertex_buffer,
	    m_shader,
	    { { "POSITION", VertexElementType::Float4 },
	      { "TINT", VertexElementType::Float4 },
	      { "TEXCOORD", VertexElementType::Float2 } },
	    shared_context
	));
}

auto TintedTextureRendererProgram::advance() -> bool
{
	m_idx += 4;
	if (m_idx >= m_map.size())
	{
		log_wrn("'VertexBuffer' map went beyond 'MaxVertices': {}", m_max_vertices);
		return false;
	}

	m_quad_count++;
	return true;
}

void TintedTextureRendererProgram::map()
{
	m_map = std::span<TintedTextureVertexData> {
		static_cast<TintedTextureVertexData *>(m_vertex_buffer->map()),
		m_max_vertices,
	};

	m_quad_count = 0u;
	m_idx = {};
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

} // namespace lt
