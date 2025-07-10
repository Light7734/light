#include <renderer/dx/buffers.hpp>
#include <renderer/dx/shared_context.hpp>

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
	auto bDesc = D3D11_BUFFER_DESC {};

	bDesc.ByteWidth = size;
	bDesc.Usage = D3D11_USAGE_DYNAMIC;
	bDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	auto hr = HRESULT {};
	dxc(m_context->get_device()->CreateBuffer(&bDesc, nullptr, &m_buffer));
	m_context->get_device_context()->VSSetConstantBuffers(m_index, 1u, m_buffer.GetAddressOf());
}

void dxConstantBuffer::bind()
{
	m_context->get_device_context()->VSSetConstantBuffers(m_index, 1u, m_buffer.GetAddressOf());
}

auto dxConstantBuffer::map() -> void *
{
	m_context->get_device_context()->VSSetConstantBuffers(m_index, 1u, m_buffer.GetAddressOf());
	m_context->get_device_context()
	    ->map(m_buffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &m_map);
	return m_map.pData;
}

void dxConstantBuffer::un_map()
{
	m_context->get_device_context()->Unmap(m_buffer.Get(), NULL);
}

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
	auto bDesc = D3D11_BUFFER_DESC {};

	bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bDesc.Usage = D3D11_USAGE_DYNAMIC;
	bDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	bDesc.ByteWidth = count * stride;
	bDesc.StructureByteStride = stride;

	// create buffer
	auto hr = HRESULT {};
	dxc(m_context->get_device()->CreateBuffer(&bDesc, nullptr, &m_buffer));
}

dxVertexBuffer::~dxVertexBuffer()
{
	un_bind();
}

auto dxVertexBuffer::map() -> void *
{
	m_context->get_device_context()
	    ->map(m_buffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &m_map);
	return m_map.pData;
}

void dxVertexBuffer::un_map()
{
	m_context->get_device_context()->Unmap(m_buffer.Get(), NULL);
}

void dxVertexBuffer::bind()
{
	static const auto offset = unsigned int { 0u };
	m_context->get_device_context()
	    ->IASetVertexBuffers(0u, 1u, m_buffer.GetAddressOf(), &m_stride, &offset);
}

void dxVertexBuffer::un_bind()
{
	static const auto offset = unsigned int { 0u };
	static auto *buffer = (ID3D11Buffer *)(nullptr);

	m_context->get_device_context()->IASetVertexBuffers(0u, 1u, &buffer, &m_stride, &offset);
}

dxIndexBuffer::dxIndexBuffer(
    unsigned int *indices,
    unsigned int count,
    Ref<dxSharedContext> sharedContext
)
    : m_context(sharedContext)
    , m_buffer(nullptr)
{
	// generate indices if not provided
	auto hasIndices = !!indices;
	if (!hasIndices)
	{
		// check
		if (count % 6 != 0)
		{
			log_wrn("'indices' can only be null if count is multiple of 6");
			lt_log(
			    warn,
			    "Adding {} to 'count' -> {}",
			    (6 - (count % 6)),
			    count + (6 - (count % 6))
			);
			count = count + (6 - (count % 6));
		}

		// create indices
		indices = new unsigned int[count];
		auto offset = 0;
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
	auto bDesc = D3D11_BUFFER_DESC {};
	bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bDesc.Usage = D3D11_USAGE_DEFAULT;

	bDesc.ByteWidth = count * sizeof(unsigned int);
	bDesc.StructureByteStride = sizeof(unsigned int);

	// subresource data
	auto sDesc = D3D11_SUBRESOURCE_DATA {};
	sDesc.pSysMem = indices;

	// create buffer
	auto hr = HRESULT {};
	dxc(m_context->get_device()->CreateBuffer(&bDesc, &sDesc, &m_buffer));

	// delete indices
	if (!hasIndices)
		delete[] indices;
}

dxIndexBuffer::~dxIndexBuffer()
{
	un_bind();
}

void dxIndexBuffer::bind()
{
	m_context->get_device_context()->IASetIndexBuffer(m_buffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
}

void dxIndexBuffer::un_bind()
{
	static const auto offset = (unsigned int) { 0u };
	static auto *buffer = (ID3D11Buffer *)(nullptr);

	m_context->get_device_context()->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, offset);
}
//======================================== INDEX_BUFFER ========================================//

} // namespace Light
