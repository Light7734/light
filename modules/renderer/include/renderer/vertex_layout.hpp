#pragma once

#include <ltdebug/assertions.hpp>

namespace Light {

class VertexBuffer;
class Shader;
class SharedContext;

enum class VertexElementType
{
	Byte1,
	Byte2,
	Byte4,
	UByte1,
	UByte2,
	UByte4,
	Int1,
	Int2,
	Int3,
	Int4,
	UInt1,
	UInt2,
	UInt3,
	UInt4,
	Float1,
	Float2,
	Float3,
	Float4,
};

class VertexLayout
{
public:
	static auto create(
	    const Ref<VertexBuffer> &vertexBuffer,
	    const Ref<Shader> &shader,
	    const std::vector<std::pair<std::string, VertexElementType>> &elements,
	    const Ref<SharedContext> &sharedContext
	) -> Ref<VertexLayout>;

	virtual ~VertexLayout() = default;

	virtual void bind() = 0;

	virtual void un_bind() = 0;

protected:
	VertexLayout() = default;
};

} // namespace Light
