#pragma once

#include <glm/glm.hpp>
#include <renderer/programs/renderer_program.hpp>

namespace lt {

class Shader;
class VertexBuffer;
class IndexBuffer;
class VertexLayout;
class OrthographicCamera;
class SharedContext;
class Shader;

class QuadRendererProgram: RendererProgram
{
public:
	virtual ~QuadRendererProgram() = default;
	struct QuadVertexData
	{
		glm::vec4 position;

		glm::vec4 tint;
	};

	QuadRendererProgram(
	    unsigned int maxVertices,
	    const Ref<SharedContext> &shared_context,
	    Ref<Shader> shader
	);

	auto advance() -> bool;

	void map() override;

	void un_map() override;

	void bind() override;

	auto get_map_current() -> QuadVertexData *
	{
		return &m_map[m_idx];
	}

	[[nodiscard]] auto get_quad_count() const -> unsigned int
	{
		return m_quad_count;
	}

	[[nodiscard]] constexpr auto get_vertex_size() const -> unsigned int
	{
		return sizeof(QuadVertexData);
	}

private:
	Ref<Shader> m_shader;

	Ref<VertexBuffer> m_vertex_buffer;

	Ref<IndexBuffer> m_index_buffer;

	Ref<VertexLayout> m_vertex_layout;

	std::span<QuadVertexData> m_map;

	size_t m_idx {};

	unsigned int m_quad_count = 0u;

	unsigned int m_max_vertices = 0u;
};

} // namespace lt
