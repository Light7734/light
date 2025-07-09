#include <engine/camera/camera.hpp>
#include <engine/graphics/buffers.hpp>
#include <engine/graphics/renderer_programs/quad.hpp>
#include <engine/graphics/shader.hpp>
#include <engine/graphics/vertex_layout.hpp>
#include <engine/utils/resource_manager.hpp>

namespace Light {

QuadRendererProgram::QuadRendererProgram(
    unsigned int max_vertices,
    const Ref<SharedContext> &shared_context
)
    : m_shader(nullptr)
    , m_index_buffer(nullptr)
    , m_vertex_layout(nullptr)
    , m_max_vertices(max_vertices)
{
	// #todo: don't use relative path
	ResourceManager::load_shader(
	    "LT_ENGINE_RESOURCES_QUAD_SHADER",
	    "data/assets/shaders/quads/vs.asset",
	    "data/assets/shaders/quads/ps.asset"
	);

	m_shader = ResourceManager::get_shader("LT_ENGINE_RESOURCES_QUAD_SHADER");
	m_vertex_buffer = Ref<VertexBuffer>(
	    VertexBuffer::create(nullptr, sizeof(QuadVertexData), max_vertices, shared_context)
	);
	m_index_buffer = Ref<IndexBuffer>(
	    IndexBuffer::create(nullptr, (max_vertices / 4) * 6, shared_context)
	);
	m_vertex_layout = Ref<VertexLayout>(VertexLayout::create(
	    m_vertex_buffer,
	    m_shader,
	    { { "POSITION", VertexElementType::Float4 }, { "COLOR", VertexElementType::Float4 } },
	    shared_context
	));
}

auto QuadRendererProgram::advance() -> bool
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

void QuadRendererProgram::map()
{
	m_map = std::span<QuadVertexData> {
		static_cast<QuadRendererProgram::QuadVertexData *>(m_vertex_buffer->map()),
		m_max_vertices,
	};

	m_quad_count = 0u;
	m_idx = {};
}

void QuadRendererProgram::un_map()
{
	m_vertex_buffer->un_map();
	m_idx = {};
}

void QuadRendererProgram::bind()
{
	m_shader->bind();
	m_vertex_layout->bind();
	m_vertex_buffer->bind();
	m_index_buffer->bind();
}

} // namespace Light
