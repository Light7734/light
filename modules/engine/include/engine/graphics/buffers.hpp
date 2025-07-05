#pragma once

#include <engine/base/base.hpp>

namespace Light {

class SharedContext;

enum class ConstantBufferIndex
{
	ViewProjection = 0u
};

//========== CONSTANT_BUFFER ==========//
class ConstantBuffer
{
public:
	static Scope<ConstantBuffer> Create(ConstantBufferIndex index, unsigned int size, Ref<SharedContext> sharedContext);

	virtual void* Map()  = 0;
	virtual void UnMap() = 0;

	virtual void Bind() = 0;

protected:
	ConstantBuffer() = default;
};

//========== VERTEX_BUFFER ==========//
class VertexBuffer
{
public:
	static Ref<VertexBuffer> Create(float* vertices, unsigned int stride, unsigned int count, Ref<SharedContext> sharedContext);

	virtual ~VertexBuffer() = default;

	virtual void* Map()  = 0;
	virtual void UnMap() = 0;

	virtual void Bind()   = 0;
	virtual void UnBind() = 0;

protected:
	VertexBuffer() = default;
};

//========== INDEX_BUFFER ==========//
class IndexBuffer
{
public:
	static Ref<IndexBuffer> Create(unsigned int* indices, unsigned int count, Ref<SharedContext> sharedContext);

	virtual ~IndexBuffer() = default;

	virtual void Bind()   = 0;
	virtual void UnBind() = 0;

protected:
	IndexBuffer() = default;
};

} // namespace Light
