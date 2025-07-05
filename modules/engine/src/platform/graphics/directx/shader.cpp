#include <d3dcompiler.h>
#include <engine/platform/graphics/directx/shader.hpp>
#include <engine/platform/graphics/directx/shared_context.hpp>

namespace Light {

dxShader::dxShader(
    BasicFileHandle vertexFile,
    BasicFileHandle pixelFile,
    Ref<dxSharedContext> sharedContext
)
    : m_Context(sharedContext)
    , m_VertexShader(nullptr)
    , m_PixelShader(nullptr)
    , m_VertexBlob(nullptr)
{
	Microsoft::WRL::ComPtr<ID3DBlob> ps = nullptr, vsErr = nullptr, psErr = nullptr;

	// compile shaders (we don't use DXC here because if D3DCompile fails it throws a dxException
	// without logging the vsErr/psErr
	D3DCompile(
	    vertexFile.GetData(),
	    vertexFile.GetSize(),
	    NULL,
	    nullptr,
	    nullptr,
	    "main",
	    "vs_4_0",
	    NULL,
	    NULL,
	    &m_VertexBlob,
	    &vsErr
	);
	D3DCompile(
	    pixelFile.GetData(),
	    pixelFile.GetSize(),
	    NULL,
	    nullptr,
	    nullptr,
	    "main",
	    "ps_4_0",
	    NULL,
	    NULL,
	    &ps,
	    &psErr
	);

	// check
	ASSERT(!vsErr.Get(), "Vertex shader compile error: {}", (char *)vsErr->GetBufferPointer());
	ASSERT(!psErr.Get(), "Pixels shader compile error: {}", (char *)psErr->GetBufferPointer());

	// create shaders
	HRESULT hr;
	DXC(m_Context->GetDevice()->CreateVertexShader(
	    m_VertexBlob->GetBufferPointer(),
	    m_VertexBlob->GetBufferSize(),
	    NULL,
	    &m_VertexShader
	));
	DXC(m_Context->GetDevice()
	        ->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), NULL, &m_PixelShader));
}

dxShader::~dxShader()
{
	UnBind();
}

void dxShader::Bind()
{
	m_Context->GetDeviceContext()->VSSetShader(m_VertexShader.Get(), nullptr, 0u);
	m_Context->GetDeviceContext()->PSSetShader(m_PixelShader.Get(), nullptr, 0u);
}

void dxShader::UnBind()
{
	m_Context->GetDeviceContext()->VSSetShader(nullptr, nullptr, 0u);
	m_Context->GetDeviceContext()->PSSetShader(nullptr, nullptr, 0u);
}

} // namespace Light
