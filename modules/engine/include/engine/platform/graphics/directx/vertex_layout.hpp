#pragma once

#include <d3d11.h>
#include <engine/base/base.hpp>
#include <engine/graphics/vertex_layout.hpp>
#include <wrl.h>

namespace Light {

class Shader;

class dxSharedContext;

class dxVertexLayout: public VertexLayout
{
private:
	Ref<dxSharedContext> m_Context;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;

public:
	dxVertexLayout(
	    Ref<Shader> shader,
	    const std::vector<std::pair<std::string, VertexElementType>> &elements,
	    Ref<dxSharedContext> sharedContext
	);
	~dxVertexLayout();

	void Bind() override;
	void UnBind() override;

private:
	DXGI_FORMAT GetDxgiFormat(VertexElementType type);
};

} // namespace Light
