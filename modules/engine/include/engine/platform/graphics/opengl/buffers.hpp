#pragma once

#include <engine/base/base.hpp>
#include <engine/graphics/buffers.hpp>

namespace Light {

//========== CONSTANT_BUFFER ==========//
class glConstantBuffer: public ConstantBuffer
{
private:
	unsigned int m_buffer_id;
	unsigned int m_index;

public:
	glConstantBuffer(ConstantBufferIndex index, unsigned int size);
	~glConstantBuffer();

	void Bind() override;

	void *Map() override;
	void UnMap() override;
};

//========== VERTEX_BUFFER ==========//
class glVertexBuffer: public VertexBuffer
{
private:
	unsigned int m_buffer_id;

public:
	glVertexBuffer(float *vertices, unsigned int stride, unsigned int count);
	~glVertexBuffer();

	void Bind() override;
	void UnBind() override;

	void *Map() override;
	void UnMap() override;
};

//========== INDEX_BUFFER ==========//
class glIndexBuffer: public IndexBuffer
{
private:
	unsigned int m_buffer_id;

public:
	glIndexBuffer(unsigned int *indices, unsigned int count);
	~glIndexBuffer();

	void Bind() override;
	void UnBind() override;
};

} // namespace Light
