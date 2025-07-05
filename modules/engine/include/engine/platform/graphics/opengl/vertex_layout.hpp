#pragma once

#include <engine/base/base.hpp>
#include <engine/graphics/vertex_layout.hpp>

namespace Light {

class VertexBuffer;

struct glVertexElementDesc
{
	unsigned int type;
	unsigned int count;
	unsigned int typeSize;
	unsigned int offset;
};

class glVertexLayout: public VertexLayout
{
private:
	unsigned int m_ArrayID;

public:
	glVertexLayout(
	    Ref<VertexBuffer> buffer,
	    const std::vector<std::pair<std::string, VertexElementType>> &elements
	);
	~glVertexLayout();

	void Bind() override;
	void UnBind() override;

private:
	glVertexElementDesc GetElementDesc(VertexElementType type, unsigned int offset);
};

} // namespace Light
