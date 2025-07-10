#pragma once

#include <d3d11.h>

#include <renderer/buffers.hpp>
#include <wrl.h>

namespace Light {

class dxSharedContext;

class dxConstantBuffer: public ConstantBuffer
{
public:
	dxConstantBuffer(
	    ConstantBufferIndex index,
	    unsigned int size,
	    Ref<dxSharedContext> sharedContext
	);

	void bind() override;

	void *map() override;

	void un_map() override;

private:
	Ref<dxSharedContext> m_context;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;

	D3D11_MAPPED_SUBRESOURCE m_map;

	unsigned int m_index;
};

class dxVertexBuffer: public VertexBuffer
{
public:
	dxVertexBuffer(
	    float *vertices,
	    unsigned int stride,
	    unsigned int count,
	    Ref<dxSharedContext> sharedContext
	);

	~dxVertexBuffer();

	void bind() override;

	void un_bind() override;

	auto map() -> void * override;

	void un_map() override;

private:
	Ref<dxSharedContext> m_context;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;

	D3D11_MAPPED_SUBRESOURCE m_map;

	unsigned int m_stride;
};

class dxIndexBuffer: public IndexBuffer
{
public:
	dxIndexBuffer(unsigned int *indices, unsigned int count, Ref<dxSharedContext> sharedContext);

	~dxIndexBuffer();

	void bind() override;

	void un_bind() override;

private:
	Ref<dxSharedContext> m_context;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
};

} // namespace Light
