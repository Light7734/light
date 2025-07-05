#include <d3dcompiler.h>
#include <engine/platform/graphics/directx/shader.hpp>
#include <engine/platform/graphics/directx/shared_context.hpp>

namespace Light {

dxShader::dxShader(
    BasicFileHandle vertexFile,
    BasicFileHandle pixelFile,
    Ref<dxSharedContext> sharedContext
)
    : m_context(sharedContext)
    , m_vertex_shader(nullptr)
    , m_pixel_shader(nullptr)
    , m_vertex_blob(nullptr)
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
	    &m_vertex_blob,
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
	DXC(m_context->GetDevice()->CreateVertexShader(
	    m_vertex_blob->GetBufferPointer(),
	    m_vertex_blob->GetBufferSize(),
	    NULL,
	    &m_vertex_shader
	));
	DXC(m_context->GetDevice()
	        ->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), NULL, &m_pixel_shader));
}

dxShader::~dxShader()
{
	UnBind();
}

void dxShader::Bind()
{
	m_context->GetDeviceContext()->VSSetShader(m_vertex_shader.Get(), nullptr, 0u);
	m_context->GetDeviceContext()->PSSetShader(m_pixel_shader.Get(), nullptr, 0u);
}

void dxShader::UnBind()
{
	m_context->GetDeviceContext()->VSSetShader(nullptr, nullptr, 0u);
	m_context->GetDeviceContext()->PSSetShader(nullptr, nullptr, 0u);
}

} // namespace Light
