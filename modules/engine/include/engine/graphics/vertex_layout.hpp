#pragma once

#include <engine/base/base.hpp>

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
	static Ref<VertexLayout> Create(
	    Ref<VertexBuffer> vertexBuffer,
	    Ref<Shader> shader,
	    const std::vector<std::pair<std::string, VertexElementType>> &elements,
	    Ref<SharedContext> sharedContext
	);

	virtual ~VertexLayout() = default;
	;

	virtual void Bind() = 0;
	virtual void UnBind() = 0;

protected:
	VertexLayout() = default;
};

} // namespace Light
