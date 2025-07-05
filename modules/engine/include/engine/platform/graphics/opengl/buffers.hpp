#pragma once

#include <engine/base/base.hpp>
#include <engine/graphics/buffers.hpp>

namespace Light {

class glConstantBuffer: public ConstantBuffer
{
public:
	glConstantBuffer(ConstantBufferIndex index, unsigned int size);

	~glConstantBuffer();

	void bind() override;

	void *map() override;

	void un_map() override;

private:
	unsigned int m_buffer_id;

	unsigned int m_index;
};

class glVertexBuffer: public VertexBuffer
{
public:
	glVertexBuffer(float *vertices, unsigned int stride, unsigned int count);

	~glVertexBuffer();

	void bind() override;

	void un_bind() override;

	void *map() override;

	void un_map() override;

private:
	unsigned int m_buffer_id;
};

class glIndexBuffer: public IndexBuffer
{
public:
	glIndexBuffer(unsigned int *indices, unsigned int count);

	~glIndexBuffer();

	void bind() override;

	void un_bind() override;

private:
	unsigned int m_buffer_id;
};

} // namespace Light
