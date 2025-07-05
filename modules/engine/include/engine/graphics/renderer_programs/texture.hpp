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
	Ref<Shader> m_Shader;
	Ref<VertexBuffer> m_VertexBuffer;
	Ref<IndexBuffer> m_IndexBuffer;
	Ref<VertexLayout> m_VertexLayout;

	TextureVertexData *m_MapCurrent = nullptr;
	TextureVertexData *m_MapEnd = nullptr;

	unsigned int m_QuadCount;
	unsigned int m_MaxVertices;

public:
	TextureRendererProgram(unsigned int maxVertices, Ref<SharedContext> sharedContext);

	bool Advance();

	void Map() override;
	void UnMap() override;

	void Bind() override;

	inline TextureVertexData *GetMapCurrent()
	{
		return m_MapCurrent;
	}

	inline unsigned int GetQuadCount() const
	{
		return m_QuadCount;
	}

	inline constexpr unsigned int GetVertexSize() const
	{
		return sizeof(TextureVertexData);
	}
};

} // namespace Light
