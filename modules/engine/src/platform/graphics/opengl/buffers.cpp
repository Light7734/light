#include <engine/platform/graphics/opengl/buffers.hpp>
#include <glad/gl.h>

namespace Light {

//==================== CONSTANT_BUFFER ====================//
glConstantBuffer::glConstantBuffer(ConstantBufferIndex index, unsigned int size)
    : m_buffer_id(NULL)
    , m_index(static_cast<int>(index))
{
	glCreateBuffers(1, &m_buffer_id);
	glNamedBufferData(m_buffer_id, size, nullptr, GL_DYNAMIC_DRAW);

	bind();
}

glConstantBuffer::~glConstantBuffer()
{
	glDeleteBuffers(1, &m_buffer_id);
}

void glConstantBuffer::bind()
{
	glBindBufferBase(GL_UNIFORM_BUFFER, m_index, m_buffer_id);
}

void *glConstantBuffer::map()
{
	void *map = glMapNamedBuffer(m_buffer_id, GL_WRITE_ONLY);
	return map;
}

void glConstantBuffer::un_map()
{
	glUnmapNamedBuffer(m_buffer_id);
}
//==================== CONSTANT_BUFFER ====================//

//==================== VERTEX_BUFFER ====================//
glVertexBuffer::glVertexBuffer(float *vertices, unsigned int stride, unsigned int count)
    : m_buffer_id(NULL)
{
	glCreateBuffers(1, &m_buffer_id);
	glNamedBufferData(m_buffer_id, stride * count, vertices, GL_DYNAMIC_DRAW);
}

glVertexBuffer::~glVertexBuffer()
{
	glDeleteBuffers(1, &m_buffer_id);
}

void glVertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);
}

void glVertexBuffer::un_bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

void *glVertexBuffer::map()
{
	return glMapNamedBuffer(m_buffer_id, GL_WRITE_ONLY);
}

void glVertexBuffer::un_map()
{
	glUnmapNamedBuffer(m_buffer_id);
}
//==================== VERTEX_BUFFER ====================//

//==================== INDEX_BUFFER ====================//
glIndexBuffer::glIndexBuffer(unsigned int *indices, unsigned int count): m_buffer_id(NULL)
{
	// generate indices if not provided
	bool hasIndices = !!indices;
	if (!hasIndices)
	{
		// check
		if (count % 6 != 0)
		{
			lt_log(warn, "'indices' can only be null if count is multiple of 6");
			lt_log(warn, "Adding {} to 'count' -> {}", (6 - (count % 6)), count + (6 - (count % 6)));
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
	glCreateBuffers(1, &m_buffer_id);
	glNamedBufferData(m_buffer_id, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// delete indices
	if (!hasIndices)
		delete[] indices;
}

glIndexBuffer::~glIndexBuffer()
{
	glDeleteBuffers(1, &m_buffer_id);
}

void glIndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer_id);
}

void glIndexBuffer::un_bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
}
//==================== INDEX_BUFFER ====================//

} // namespace Light
