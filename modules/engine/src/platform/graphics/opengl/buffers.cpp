#include <engine/platform/graphics/opengl/buffers.hpp>
#include <glad/gl.h>

namespace Light {

//==================== CONSTANT_BUFFER ====================//
glConstantBuffer::glConstantBuffer(ConstantBufferIndex index, unsigned int size)
    : m_BufferID(NULL)
    , m_Index(static_cast<int>(index))
{
	glCreateBuffers(1, &m_BufferID);
	glNamedBufferData(m_BufferID, size, nullptr, GL_DYNAMIC_DRAW);

	Bind();
}

glConstantBuffer::~glConstantBuffer()
{
	glDeleteBuffers(1, &m_BufferID);
}

void glConstantBuffer::Bind()
{
	glBindBufferBase(GL_UNIFORM_BUFFER, m_Index, m_BufferID);
}

void *glConstantBuffer::Map()
{
	void *map = glMapNamedBuffer(m_BufferID, GL_WRITE_ONLY);
	return map;
}

void glConstantBuffer::UnMap()
{
	glUnmapNamedBuffer(m_BufferID);
}
//==================== CONSTANT_BUFFER ====================//

//==================== VERTEX_BUFFER ====================//
glVertexBuffer::glVertexBuffer(float *vertices, unsigned int stride, unsigned int count)
    : m_BufferID(NULL)
{
	glCreateBuffers(1, &m_BufferID);
	glNamedBufferData(m_BufferID, stride * count, vertices, GL_DYNAMIC_DRAW);
}

glVertexBuffer::~glVertexBuffer()
{
	glDeleteBuffers(1, &m_BufferID);
}

void glVertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void glVertexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

void *glVertexBuffer::Map()
{
	return glMapNamedBuffer(m_BufferID, GL_WRITE_ONLY);
}

void glVertexBuffer::UnMap()
{
	glUnmapNamedBuffer(m_BufferID);
}
//==================== VERTEX_BUFFER ====================//

//==================== INDEX_BUFFER ====================//
glIndexBuffer::glIndexBuffer(unsigned int *indices, unsigned int count): m_BufferID(NULL)
{
	// generate indices if not provided
	bool hasIndices = !!indices;
	if (!hasIndices)
	{
		// check
		if (count % 6 != 0)
		{
			LOG(warn, "'indices' can only be null if count is multiple of 6");
			LOG(warn, "Adding {} to 'count' -> {}", (6 - (count % 6)), count + (6 - (count % 6)));
			count = count + (6 - (count % 6));
		}

		// create indices
		indices = new unsigned int[count];
		unsigned int offset = 0u;
		for (unsigned int i = 0u; i < count; i += 6u)
		{
			indices[i + 0] = offset + 0u;
			indices[i + 1] = offset + 1u;
			indices[i + 2] = offset + 2u;

			indices[i + 3] = offset + 2u;
			indices[i + 4] = offset + 3u;
			indices[i + 5] = offset + 0u;

			offset += 4u;
		}
	}

	// create buffer
	glCreateBuffers(1, &m_BufferID);
	glNamedBufferData(m_BufferID, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// delete indices
	if (!hasIndices)
		delete[] indices;
}

glIndexBuffer::~glIndexBuffer()
{
	glDeleteBuffers(1, &m_BufferID);
}

void glIndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
}

void glIndexBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
}
//==================== INDEX_BUFFER ====================//

} // namespace Light
