#pragma once


namespace lt {

class SharedContext;

enum class ConstantBufferIndex
{
	ViewProjection = 0u
};

class ConstantBuffer
{
public:
	virtual ~ConstantBuffer() = default;
	static auto create(
	    ConstantBufferIndex index,
	    unsigned int size,
	    const Ref<SharedContext> &sharedContext
	) -> Scope<ConstantBuffer>;

	virtual auto map() -> void * = 0;

	virtual void un_map() = 0;

	virtual void bind() = 0;

protected:
	ConstantBuffer() = default;
};

class VertexBuffer
{
public:
	static auto create(
	    float *vertices,
	    unsigned int stride,
	    unsigned int count,
	    const Ref<SharedContext> &sharedContext
	) -> Ref<VertexBuffer>;

	virtual ~VertexBuffer() = default;

	virtual auto map() -> void * = 0;

	virtual void un_map() = 0;

	virtual void bind() = 0;

	virtual void un_bind() = 0;

protected:
	VertexBuffer() = default;
};

class IndexBuffer
{
public:
	static auto create(
	    unsigned int *indices,
	    unsigned int count,
	    const Ref<SharedContext> &sharedContext
	) -> Ref<IndexBuffer>;

	virtual ~IndexBuffer() = default;

	virtual void bind() = 0;

	virtual void un_bind() = 0;

protected:
	IndexBuffer() = default;
};

} // namespace lt
