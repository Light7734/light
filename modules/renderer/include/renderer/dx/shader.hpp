#pragma once

#include <d3d11.h>

#include <renderer/shader.hpp>
#include <wrl.h>

namespace lt {

class dxSharedContext;

class dxShader: public Shader
{
public:
	dxShader(
	    BasicFileHandle vertexFile,
	    BasicFileHandle pixelFile,
	    Ref<dxSharedContext> sharedContext
	);

	~dxShader();

	void bind() override;

	void un_bind() override;

	auto get_vertex_blob() -> Microsoft::WRL::ComPtr<ID3DBlob>
	{
		return m_vertex_blob;
	}

private:
	Ref<dxSharedContext> m_context;

	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertex_shader;

	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixel_shader;

	Microsoft::WRL::ComPtr<ID3DBlob> m_vertex_blob;
};

} // namespace lt
