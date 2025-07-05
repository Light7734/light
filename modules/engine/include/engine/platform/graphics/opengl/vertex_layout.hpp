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
public:
	glVertexLayout(
	    Ref<VertexBuffer> buffer,
	    const std::vector<std::pair<std::string, VertexElementType>> &elements
	);

	~glVertexLayout();

	void bind() override;

	void un_bind() override;

private:
	glVertexElementDesc get_element_desc(VertexElementType type, unsigned int offset);

	unsigned int m_array_id;
};

} // namespace Light
