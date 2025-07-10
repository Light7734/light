#pragma once

#include <glm/glm.hpp>
#include <renderer/renderer_programs/renderer_program.hpp>

namespace Light {

class Shader;
class VertexBuffer;
class IndexBuffer;
class VertexLayout;
class OrthographicCamera;
class SharedContext;

class TintedTextureRendererProgram: RendererProgram
{
public:
	virtual ~TintedTextureRendererProgram() = default;
	struct TintedTextureVertexData
	{
		glm::vec4 position;

		glm::vec4 tint;

		glm::vec2 texcoord;
	};

	TintedTextureRendererProgram(
	    unsigned int maxVertices,
	    const Ref<SharedContext> &sharedContext,
	    Ref<Shader> shader
	);

	auto advance() -> bool;

	void map() override;

	void un_map() override;

	void bind() override;

	auto get_map_current() -> TintedTextureVertexData *
	{
		return &m_map[m_idx];
	}

	[[nodiscard]] auto get_quad_count() const -> unsigned int
	{
		return m_quad_count;
	}

	[[nodiscard]] constexpr auto get_vertex_size() const -> unsigned int
	{
		return sizeof(TintedTextureVertexData);
	}

private:
	Ref<Shader> m_shader;

	Ref<VertexBuffer> m_vertex_buffer;

	Ref<IndexBuffer> m_index_buffer;

	Ref<VertexLayout> m_vertex_layout;

	std::span<TintedTextureVertexData> m_map;

	size_t m_idx {};

	unsigned int m_quad_count { 0u };

	unsigned int m_max_vertices;
};

} // namespace Light
