#pragma once

#include <engine/base/base.hpp>
#include <engine/graphics/renderer_programs/renderer_program.hpp>
#include <glm/glm.hpp>

namespace Light {

class Shader;
class VertexBuffer;
class IndexBuffer;
class VertexLayout;

class OrthographicCamera;

class SharedContext;

class TextureRendererProgram: RendererProgram
{
public:
	struct TextureVertexData
	{
		glm::vec4 position;
		glm::vec2 texcoord;
	};

private:
	Ref<Shader> m_shader;
	Ref<VertexBuffer> m_vertex_buffer;
	Ref<IndexBuffer> m_index_buffer;
	Ref<VertexLayout> m_vertex_layout;

	TextureVertexData *m_map_current = nullptr;
	TextureVertexData *m_map_end = nullptr;

	unsigned int m_quad_count;
	unsigned int m_max_vertices;

public:
	TextureRendererProgram(unsigned int maxVertices, Ref<SharedContext> sharedContext);

	bool Advance();

	void Map() override;
	void UnMap() override;

	void Bind() override;

	inline TextureVertexData *GetMapCurrent()
	{
		return m_map_current;
	}

	inline unsigned int GetQuadCount() const
	{
		return m_quad_count;
	}

	inline constexpr unsigned int GetVertexSize() const
	{
		return sizeof(TextureVertexData);
	}
};

} // namespace Light
