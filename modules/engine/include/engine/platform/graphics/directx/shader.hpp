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
	    basic_file_handle vertexFile,
	    basic_file_handle pixelFile,
	    Ref<dxSharedContext> sharedContext
	);
	~dxShader();

	void bind() override;
	void un_bind() override;

	inline Microsoft::WRL::ComPtr<ID3DBlob> get_vertex_blob()
	{
		return m_vertex_blob;
	}
};

} // namespace Light
