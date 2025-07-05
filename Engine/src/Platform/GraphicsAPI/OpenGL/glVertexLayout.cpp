#include "glVertexLayout.hpp"

#include "glBuffers.hpp"

#include <glad/gl.h>

namespace Light {

glVertexLayout::glVertexLayout(Ref<VertexBuffer> buffer, const std::vector<std::pair<std::string, VertexElementType>>& elements)
    : m_ArrayID(NULL)
{
	// check
	ASSERT(std::dynamic_pointer_cast<glVertexBuffer>(buffer), "Failed to cast 'VertexBuffer' to 'glVertexBuffer'");
	ASSERT(!elements.empty(), "'elements' is empty");

	// local
	std::vector<glVertexElementDesc> elementsDesc;
	elementsDesc.reserve(elements.size());
	unsigned int stride = 0u;

	// extract elements desc
	for (const auto& element : elements)
	{
		elementsDesc.push_back(GetElementDesc(element.second, stride));
		stride += elementsDesc.back().typeSize * elementsDesc.back().count;
	}

	// create vertex array
	glCreateVertexArrays(1, &m_ArrayID);

	// bind buffer and array
	buffer->Bind();
	Bind();

	// enable vertex attributes
	unsigned int index = 0u;
	for (const auto& elementDesc : elementsDesc)
	{
		glVertexAttribPointer(index, elementDesc.count, elementDesc.type, GL_FALSE, stride, (const void*)elementDesc.offset);
		glEnableVertexAttribArray(index++);
	}
}

glVertexLayout::~glVertexLayout()
{
	glDeleteVertexArrays(1, &m_ArrayID);
}

void glVertexLayout::Bind()
{
	glBindVertexArray(m_ArrayID);
}

void glVertexLayout::UnBind()
{
	glBindVertexArray(NULL);
}

glVertexElementDesc glVertexLayout::GetElementDesc(VertexElementType type, unsigned int offset)
{
	switch (type)
	{
	/* byte */
	case Light::VertexElementType::Byte1: return { GL_BYTE, 1u, sizeof(GLbyte), offset };
	case Light::VertexElementType::Byte2: return { GL_BYTE, 1u, sizeof(GLbyte), offset };
	case Light::VertexElementType::Byte4: return { GL_BYTE, 1u, sizeof(GLbyte), offset };

	/* ubyte */
	case Light::VertexElementType::UByte1: return { GL_UNSIGNED_BYTE, 1u, sizeof(GLubyte), offset };
	case Light::VertexElementType::UByte2: return { GL_UNSIGNED_BYTE, 2u, sizeof(GLubyte), offset };
	case Light::VertexElementType::UByte4: return { GL_UNSIGNED_BYTE, 4u, sizeof(GLubyte), offset };

	/* int */
	case VertexElementType::Int1: return { GL_INT, 1u, sizeof(GLint), offset };
	case VertexElementType::Int2: return { GL_INT, 2u, sizeof(GLint), offset };
	case VertexElementType::Int3: return { GL_INT, 3u, sizeof(GLint), offset };
	case VertexElementType::Int4: return { GL_INT, 4u, sizeof(GLint), offset };

	/* uint */
	case VertexElementType::UInt1: return { GL_UNSIGNED_INT, 1u, sizeof(GLuint), offset };
	case VertexElementType::UInt2: return { GL_UNSIGNED_INT, 2u, sizeof(GLuint), offset };
	case VertexElementType::UInt3: return { GL_UNSIGNED_INT, 3u, sizeof(GLuint), offset };
	case VertexElementType::UInt4: return { GL_UNSIGNED_INT, 4u, sizeof(GLuint), offset };

	/* float */
	case VertexElementType::Float1: return { GL_FLOAT, 1u, sizeof(GLfloat), offset };
	case VertexElementType::Float2: return { GL_FLOAT, 2u, sizeof(GLfloat), offset };
	case VertexElementType::Float3: return { GL_FLOAT, 3u, sizeof(GLfloat), offset };
	case VertexElementType::Float4: return { GL_FLOAT, 4u, sizeof(GLfloat), offset };

	default:
		ASSERT(false, "Invalid 'VertexElementType'");
		return {};
	}
}

} // namespace Light
