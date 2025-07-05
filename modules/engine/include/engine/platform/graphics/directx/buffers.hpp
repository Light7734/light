#pragma once

#include <d3d11.h>
#include <engine/base/base.hpp>
#include <engine/graphics/buffers.hpp>
#include <wrl.h>

namespace Light {

class dxSharedContext;

//========== CONSTANT_BUFFER ==========//
class dxConstantBuffer: public ConstantBuffer
{
private:
	Ref<dxSharedContext> m_context;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
	D3D11_MAPPED_SUBRESOURCE m_map;

	unsigned int m_index;

public:
	dxConstantBuffer(
	    ConstantBufferIndex index,
	    unsigned int size,
	    Ref<dxSharedContext> sharedContext
	);

	void bind() override;

	void *map() override;
	void un_map() override;
};

//========== VERTEX_BUFFER  ==========//
class dxVertexBuffer: public VertexBuffer
{
private:
	Ref<dxSharedContext> m_context;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
	D3D11_MAPPED_SUBRESOURCE m_map;

	unsigned int m_stride;

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

	void *map() override;
	void un_map() override;
};

//========== INDEX_BUFFER  ==========//
class dxIndexBuffer: public IndexBuffer
{
private:
	Ref<dxSharedContext> m_context;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;

public:
	dxIndexBuffer(unsigned int *indices, unsigned int count, Ref<dxSharedContext> sharedContext);
	~dxIndexBuffer();

	void bind() override;
	void un_bind() override;
};

} // namespace Light
