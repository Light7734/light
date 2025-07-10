#include <d3dcompiler.h>
#include <renderer/dx/shader.hpp>
#include <renderer/dx/shared_context.hpp>

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
	auto ps = Microsoft::WRL::ComPtr<ID3DBlob> { nullptr };
	auto vsErr = Microsoft::WRL::ComPtr<ID3DBlob> { nullptr };
	auto psErr = Microsoft::WRL::ComPtr<ID3DBlob> { nullptr };

	// compile shaders (we don't use dxc here because if d3_d_compile fails it throws a dxException
	// without logging the vsErr/psErr
	d3_d_compile(
	    vertexFile.GetData(),
	    vertexFile.get_size(),
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
	d3_d_compile(
	    pixelFile.GetData(),
	    pixelFile.get_size(),
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
	lt_assert(!vsErr.Get(), "Vertex shader compile error: {}", (char *)vsErr->GetBufferPointer());
	lt_assert(!psErr.Get(), "Pixels shader compile error: {}", (char *)psErr->GetBufferPointer());

	// create shaders
	auto hr = HRESULT {};
	dxc(m_context->get_device()->CreateVertexShader(
	    m_vertex_blob->GetBufferPointer(),
	    m_vertex_blob->GetBufferSize(),
	    NULL,
	    &m_vertex_shader
	));
	dxc(m_context->get_device()
	        ->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), NULL, &m_pixel_shader)
	);
}

dxShader::~dxShader()
{
	un_bind();
}

void dxShader::bind()
{
	m_context->get_device_context()->VSSetShader(m_vertex_shader.Get(), nullptr, 0u);
	m_context->get_device_context()->PSSetShader(m_pixel_shader.Get(), nullptr, 0u);
}

void dxShader::un_bind()
{
	m_context->get_device_context()->VSSetShader(nullptr, nullptr, 0u);
	m_context->get_device_context()->PSSetShader(nullptr, nullptr, 0u);
}

} // namespace Light
