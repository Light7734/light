#pragma once

#include <d3d11.h>
#include <engine/base/base.hpp>
#include <engine/graphics/shader.hpp>
#include <engine/utils/file_manager.hpp>
#include <wrl.h>

namespace Light {

class dxSharedContext;

class dxShader: public Shader
{
private:
	Ref<dxSharedContext> m_context;

	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertex_shader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixel_shader;

	Microsoft::WRL::ComPtr<ID3DBlob> m_vertex_blob;

public:
	dxShader(
	    BasicFileHandle vertexFile,
	    BasicFileHandle pixelFile,
	    Ref<dxSharedContext> sharedContext
	);
	~dxShader();

	void Bind() override;
	void UnBind() override;

	inline Microsoft::WRL::ComPtr<ID3DBlob> GetVertexBlob()
	{
		return m_vertex_blob;
	}
};

} // namespace Light
