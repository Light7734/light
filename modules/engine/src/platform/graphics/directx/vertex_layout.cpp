#include <engine/platform/graphics/directx/shader.hpp>
#include <engine/platform/graphics/directx/shared_context.hpp>
#include <engine/platform/graphics/directx/vertex_layout.hpp>

namespace Light {

dxVertexLayout::dxVertexLayout(
    Ref<Shader> shader,
    const std::vector<std::pair<std::string, VertexElementType>> &elements,
    Ref<dxSharedContext> sharedContext
)
    : m_context(sharedContext)
    , m_input_layout(nullptr)
{
	// occupy space for input elements
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementsDesc;
	inputElementsDesc.reserve(elements.size());

	// extract elements desc
	for (const auto &element : elements)
	{
		inputElementsDesc.emplace_back(D3D11_INPUT_ELEMENT_DESC { element.first.c_str(),
		                                                          NULL,
		                                                          GetDxgiFormat(element.second),
		                                                          0u,
		                                                          D3D11_APPEND_ALIGNED_ELEMENT,
		                                                          D3D11_INPUT_PER_VERTEX_DATA,
		                                                          0u });
	}

	Ref<dxShader> dxpShader = std::dynamic_pointer_cast<dxShader>(shader);
	ASSERT(dxpShader, "Failed to cast 'Shader' to 'dxShader'");

	// create input layout (vertex layout)
	HRESULT hr;
	DXC(m_context->GetDevice()->CreateInputLayout(
	    &inputElementsDesc[0],
	    inputElementsDesc.size(),
	    dxpShader->GetVertexBlob().Get()->GetBufferPointer(),
	    dxpShader->GetVertexBlob().Get()->GetBufferSize(),
	    &m_input_layout
	));
}

dxVertexLayout::~dxVertexLayout()
{
	UnBind();
}

void dxVertexLayout::Bind()
{
	m_context->GetDeviceContext()->IASetInputLayout(m_input_layout.Get());
}

void dxVertexLayout::UnBind()
{
	m_context->GetDeviceContext()->IASetInputLayout(nullptr);
}

DXGI_FORMAT dxVertexLayout::GetDxgiFormat(VertexElementType type)
{
	switch (type)
	{
	/* byte */
	case Light::VertexElementType::Byte1: return DXGI_FORMAT_R8_SINT;
	case Light::VertexElementType::Byte2: return DXGI_FORMAT_R8G8_SINT;
	case Light::VertexElementType::Byte4: return DXGI_FORMAT_R8_SINT;

	/* ubyte */
	case Light::VertexElementType::UByte1: return DXGI_FORMAT_R8_UINT;
	case Light::VertexElementType::UByte2: return DXGI_FORMAT_R8G8_UINT;
	case Light::VertexElementType::UByte4: return DXGI_FORMAT_R8G8B8A8_UINT;

	/* int */
	case Light::VertexElementType::Int1: return DXGI_FORMAT_R32_SINT;
	case Light::VertexElementType::Int2: return DXGI_FORMAT_R32G32_SINT;
	case Light::VertexElementType::Int3: return DXGI_FORMAT_R32G32B32_SINT;
	case Light::VertexElementType::Int4: return DXGI_FORMAT_R32G32B32A32_SINT;

	/* uint */
	case Light::VertexElementType::UInt1: return DXGI_FORMAT_R32_UINT;
	case Light::VertexElementType::UInt2: return DXGI_FORMAT_R32G32_UINT;
	case Light::VertexElementType::UInt3: return DXGI_FORMAT_R32G32B32_UINT;
	case Light::VertexElementType::UInt4: return DXGI_FORMAT_R32G32B32A32_UINT;

	/* float */
	case Light::VertexElementType::Float1: return DXGI_FORMAT_R32_FLOAT;
	case Light::VertexElementType::Float2: return DXGI_FORMAT_R32G32_FLOAT;
	case Light::VertexElementType::Float3: return DXGI_FORMAT_R32G32B32_FLOAT;
	case Light::VertexElementType::Float4: return DXGI_FORMAT_R32G32B32A32_FLOAT;

	default: ASSERT(false, "Invalid 'VertexElementType'"); return DXGI_FORMAT_UNKNOWN;
	}
}

} // namespace Light
