#include <engine/camera/camera.hpp>
#include <engine/graphics/buffers.hpp>
#include <engine/graphics/renderer_programs/texture.hpp>
#include <engine/graphics/shader.hpp>
#include <engine/graphics/vertex_layout.hpp>
#include <engine/utils/resource_manager.hpp>

namespace Light {

TextureRendererProgram::TextureRendererProgram(
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
	    "LT_ENGINE_RESOURCES_TEXTURE_SHADER",
	    "data/assets/shaders/texture/vs.glsl",
	    "data/assets/shaders/texture/ps.glsl"
	);

	m_shader = ResourceManager::get_shader("LT_ENGINE_RESOURCES_TEXTURE_SHADER");
	m_vertex_buffer = Ref<VertexBuffer>(
	    VertexBuffer::create(nullptr, sizeof(TextureVertexData), max_vertices, shared_context)
	);
	m_index_buffer = Ref<IndexBuffer>(
	    IndexBuffer::create(nullptr, (max_vertices / 4) * 6, shared_context)
	);
	m_vertex_layout = Ref<VertexLayout>(VertexLayout::create(
	    m_vertex_buffer,
	    m_shader,
	    { { "POSITION", VertexElementType::Float4 }, { "TEXCOORD", VertexElementType::Float2 } },
	    shared_context
	));
}

auto TextureRendererProgram::advance() -> bool
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

void TextureRendererProgram::map()
{
	m_map = std::span<TextureVertexData> {
		static_cast<TextureVertexData *>(m_vertex_buffer->map()),
		m_max_vertices,
	};

	m_quad_count = 0u;
	m_idx = {};
}

void TextureRendererProgram::un_map()
{
	m_vertex_buffer->un_map();
}

void TextureRendererProgram::bind()
{
	m_shader->bind();
	m_vertex_layout->bind();
	m_vertex_buffer->bind();
	m_index_buffer->bind();
}

} // namespace Light
