#include <engine/platform/graphics/directx/buffers.hpp>
#include <engine/platform/graphics/directx/shared_context.hpp>

namespace Light {

//======================================== CONSTANT_BUFFER
//========================================//
dxConstantBuffer::dxConstantBuffer(
    ConstantBufferIndex index,
    unsigned int size,
    Ref<dxSharedContext> sharedContext
)
    : m_context(sharedContext)
    , m_buffer(nullptr)
    , m_map {}
    , m_index(static_cast<int>(index))
{
	D3D11_BUFFER_DESC bDesc = {};

	bDesc.ByteWidth = size;
	bDesc.Usage = D3D11_USAGE_DYNAMIC;
	bDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr;
	DXC(m_context->GetDevice()->CreateBuffer(&bDesc, nullptr, &m_buffer));
	m_context->GetDeviceContext()->VSSetConstantBuffers(m_index, 1u, m_buffer.GetAddressOf());
}

void dxConstantBuffer::Bind()
{
	m_context->GetDeviceContext()->VSSetConstantBuffers(m_index, 1u, m_buffer.GetAddressOf());
}

void *dxConstantBuffer::Map()
{
	m_context->GetDeviceContext()->VSSetConstantBuffers(m_index, 1u, m_buffer.GetAddressOf());
	m_context->GetDeviceContext()->Map(m_buffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &m_map);
	return m_map.pData;
}

void dxConstantBuffer::UnMap()
{
	m_context->GetDeviceContext()->Unmap(m_buffer.Get(), NULL);
}
//======================================== CONSTANT_BUFFER
//========================================//

//================================================== VERTEX_BUFFER
//==================================================//
dxVertexBuffer::dxVertexBuffer(
    float *vertices,
    unsigned int stride,
    unsigned int count,
    Ref<dxSharedContext> sharedContext
)
    : m_context(sharedContext)
    , m_buffer(nullptr)
    , m_map {}
    , m_stride(stride)
{
	// buffer desc
	D3D11_BUFFER_DESC bDesc = {};

	bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bDesc.Usage = D3D11_USAGE_DYNAMIC;
	bDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	bDesc.ByteWidth = count * stride;
	bDesc.StructureByteStride = stride;

	// create buffer
	HRESULT hr;
	DXC(m_context->GetDevice()->CreateBuffer(&bDesc, nullptr, &m_buffer));
}

dxVertexBuffer::~dxVertexBuffer()
{
	UnBind();
}

void *dxVertexBuffer::Map()
{
	m_context->GetDeviceContext()->Map(m_buffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &m_map);
	return m_map.pData;
}

void dxVertexBuffer::UnMap()
{
	m_context->GetDeviceContext()->Unmap(m_buffer.Get(), NULL);
}

void dxVertexBuffer::Bind()
{
	static const unsigned int offset = 0u;
	m_context->GetDeviceContext()
	    ->IASetVertexBuffers(0u, 1u, m_buffer.GetAddressOf(), &m_stride, &offset);
}

void dxVertexBuffer::UnBind()
{
	static const unsigned int offset = 0u;
	static ID3D11Buffer *buffer = nullptr;

	m_context->GetDeviceContext()->IASetVertexBuffers(0u, 1u, &buffer, &m_stride, &offset);
}
//================================================== VERTEX_BUFFER
//==================================================//

//======================================== INDEX_BUFFER ========================================//
dxIndexBuffer::dxIndexBuffer(
    unsigned int *indices,
    unsigned int count,
    Ref<dxSharedContext> sharedContext
)
    : m_context(sharedContext)
    , m_buffer(nullptr)
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
		unsigned int offset = 0;
		for (unsigned int i = 0; i < count; i += 6)
		{
			indices[i + 0] = offset + 0u;
			indices[i + 1] = offset + 3u;
			indices[i + 2] = offset + 2u;

			indices[i + 3] = offset + 2u;
			indices[i + 4] = offset + 1u;
			indices[i + 5] = offset + 0u;

			offset += 4u;
		}
	}

	// buffer desc
	D3D11_BUFFER_DESC bDesc = {};
	bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bDesc.Usage = D3D11_USAGE_DEFAULT;

	bDesc.ByteWidth = count * sizeof(unsigned int);
	bDesc.StructureByteStride = sizeof(unsigned int);

	// subresource data
	D3D11_SUBRESOURCE_DATA sDesc = {};
	sDesc.pSysMem = indices;

	// create buffer
	HRESULT hr;
	DXC(m_context->GetDevice()->CreateBuffer(&bDesc, &sDesc, &m_buffer));

	// delete indices
	if (!hasIndices)
		delete[] indices;
}

dxIndexBuffer::~dxIndexBuffer()
{
	UnBind();
}

void dxIndexBuffer::Bind()
{
	m_context->GetDeviceContext()->IASetIndexBuffer(m_buffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
}

void dxIndexBuffer::UnBind()
{
	static const unsigned int offset = 0u;
	static ID3D11Buffer *buffer = nullptr;

	m_context->GetDeviceContext()->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, offset);
}
//======================================== INDEX_BUFFER ========================================//

} // namespace Light
