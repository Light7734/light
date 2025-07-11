#pragma once


#include <renderer/buffers.hpp>

namespace lt {

class glConstantBuffer: public ConstantBuffer
{
public:
	glConstantBuffer(ConstantBufferIndex index, unsigned int size);

	virtual ~glConstantBuffer();

	void bind() override;

	auto map() -> void * override;

	void un_map() override;

private:
	unsigned int m_buffer_id;

	unsigned int m_index;
};

class glVertexBuffer: public VertexBuffer
{
public:
	glVertexBuffer(float *vertices, unsigned int stride, unsigned int count);

	~glVertexBuffer() override;

	void bind() override;

	void un_bind() override;

	auto map() -> void * override;

	void un_map() override;

private:
	unsigned int m_buffer_id;
};

class glIndexBuffer: public IndexBuffer
{
public:
	glIndexBuffer(unsigned int *indices, unsigned int count);

	~glIndexBuffer() override;

	void bind() override;

	void un_bind() override;

private:
	unsigned int m_buffer_id;
};

} // namespace lt
