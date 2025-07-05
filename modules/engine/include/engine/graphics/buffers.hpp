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
	static Scope<ConstantBuffer> create(ConstantBufferIndex index, unsigned int size, Ref<SharedContext> sharedContext);

	virtual void* map()  = 0;
	virtual void un_map() = 0;

	virtual void bind() = 0;

protected:
	ConstantBuffer() = default;
};

//========== VERTEX_BUFFER ==========//
class VertexBuffer
{
public:
	static Ref<VertexBuffer> create(float* vertices, unsigned int stride, unsigned int count, Ref<SharedContext> sharedContext);

	virtual ~VertexBuffer() = default;

	virtual void* map()  = 0;
	virtual void un_map() = 0;

	virtual void bind()   = 0;
	virtual void un_bind() = 0;

protected:
	VertexBuffer() = default;
};

//========== INDEX_BUFFER ==========//
class IndexBuffer
{
public:
	static Ref<IndexBuffer> create(unsigned int* indices, unsigned int count, Ref<SharedContext> sharedContext);

	virtual ~IndexBuffer() = default;

	virtual void bind()   = 0;
	virtual void un_bind() = 0;

protected:
	IndexBuffer() = default;
};

} // namespace Light
