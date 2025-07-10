#include <renderer/dx/shader.hpp>
#include <renderer/dx/shared_context.hpp>
#include <renderer/dx/vertex_layout.hpp>

namespace lt {

dxVertexLayout::dxVertexLayout(
    Ref<Shader> shader,
    const std::vector<std::pair<std::string, VertexElementType>> &elements,
    Ref<dxSharedContext> sharedContext
)
    : m_context(sharedContext)
    , m_input_layout(nullptr)
{
	auto inputElementsDesc = std::vector<D3D11_INPUT_ELEMENT_DESC> {};
	inputElementsDesc.reserve(elements.size());

	// extract elements desc
	for (const auto &element : elements)
	{
		inputElementsDesc.emplace_back(D3D11_INPUT_ELEMENT_DESC { element.first.c_str(),
		                                                          NULL,
		                                                          get_dxgi_format(element.second),
		                                                          0u,
		                                                          D3D11_APPEND_ALIGNED_ELEMENT,
		                                                          D3D11_INPUT_PER_VERTEX_DATA,
		                                                          0u });
	}

	auto dxpShader = std::dynamic_pointer_cast<dxShader>(shader);
	lt_assert(dxpShader, "Failed to cast 'Shader' to 'dxShader'");

	// create input layout (vertex layout)
	auto hr = HRESULT {};
	dxc(m_context->get_device()->CreateInputLayout(
	    &inputElementsDesc[0],
	    inputElementsDesc.size(),
	    dxpShader->get_vertex_blob().Get()->GetBufferPointer(),
	    dxpShader->get_vertex_blob().Get()->GetBufferSize(),
	    &m_input_layout
	));
}

dxVertexLayout::~dxVertexLayout()
{
	un_bind();
}

void dxVertexLayout::bind()
{
	m_context->get_device_context()->IASetInputLayout(m_input_layout.Get());
}

void dxVertexLayout::un_bind()
{
	m_context->get_device_context()->IASetInputLayout(nullptr);
}

auto dxVertexLayout::get_dxgi_format(VertexElementType type) -> DXGI_FORMAT
{
	switch (type)
	{
	/* byte */
	case lt::VertexElementType::Byte1: return DXGI_FORMAT_R8_SINT;
	case lt::VertexElementType::Byte2: return DXGI_FORMAT_R8G8_SINT;
	case lt::VertexElementType::Byte4: return DXGI_FORMAT_R8_SINT;

	/* ubyte */
	case lt::VertexElementType::UByte1: return DXGI_FORMAT_R8_UINT;
	case lt::VertexElementType::UByte2: return DXGI_FORMAT_R8G8_UINT;
	case lt::VertexElementType::UByte4: return DXGI_FORMAT_R8G8B8A8_UINT;

	/* int */
	case lt::VertexElementType::Int1: return DXGI_FORMAT_R32_SINT;
	case lt::VertexElementType::Int2: return DXGI_FORMAT_R32G32_SINT;
	case lt::VertexElementType::Int3: return DXGI_FORMAT_R32G32B32_SINT;
	case lt::VertexElementType::Int4: return DXGI_FORMAT_R32G32B32A32_SINT;

	/* uint */
	case lt::VertexElementType::UInt1: return DXGI_FORMAT_R32_UINT;
	case lt::VertexElementType::UInt2: return DXGI_FORMAT_R32G32_UINT;
	case lt::VertexElementType::UInt3: return DXGI_FORMAT_R32G32B32_UINT;
	case lt::VertexElementType::UInt4: return DXGI_FORMAT_R32G32B32A32_UINT;

	/* float */
	case lt::VertexElementType::Float1: return DXGI_FORMAT_R32_FLOAT;
	case lt::VertexElementType::Float2: return DXGI_FORMAT_R32G32_FLOAT;
	case lt::VertexElementType::Float3: return DXGI_FORMAT_R32G32B32_FLOAT;
	case lt::VertexElementType::Float4: return DXGI_FORMAT_R32G32B32A32_FLOAT;

	default: lt_assert(false, "Invalid 'VertexElementType'"); return DXGI_FORMAT_UNKNOWN;
	}
}

} // namespace lt
