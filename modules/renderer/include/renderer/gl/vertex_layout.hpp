#pragma once


#include <renderer/vertex_layout.hpp>

namespace lt {

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
	    const Ref<VertexBuffer>& buffer,
	    const std::vector<std::pair<std::string, VertexElementType>> &elements
	);

	~glVertexLayout() override;

	void bind() override;

	void un_bind() override;

private:
	auto get_element_desc(VertexElementType type, unsigned int offset) -> glVertexElementDesc;

	unsigned int m_array_id;
};

} // namespace lt
