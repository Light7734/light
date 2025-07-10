#include <glad/gl.h>
#include <debug/assertions.hpp>
#include <renderer/gl/buffers.hpp>
#include <renderer/gl/vertex_layout.hpp>

namespace lt {

glVertexLayout::glVertexLayout(
    const Ref<VertexBuffer> &buffer,
    const std::vector<std::pair<std::string, VertexElementType>> &elements
)
    : m_array_id(NULL)
{
	// check
	lt_assert(
	    std::dynamic_pointer_cast<glVertexBuffer>(buffer),
	    "Failed to cast 'VertexBuffer' to 'glVertexBuffer'"
	);
	lt_assert(!elements.empty(), "'elements' is empty");

	// local
	auto elementsDesc = std::vector<glVertexElementDesc> {};
	elementsDesc.reserve(elements.size());
	auto stride = 0u;

	// extract elements desc
	for (const auto &element : elements)
	{
		elementsDesc.push_back(get_element_desc(element.second, stride));
		stride += elementsDesc.back().typeSize * elementsDesc.back().count;
	}

	// create vertex array
	glCreateVertexArrays(1, &m_array_id);

	// bind buffer and array
	buffer->bind();
	bind();

	// enable vertex attributes
	auto index = 0u;
	for (const auto &elementDesc : elementsDesc)
	{
		glVertexAttribPointer(
		    index,
		    elementDesc.count,
		    elementDesc.type,
		    GL_FALSE,
		    stride,
		    (const void *)elementDesc.offset
		);
		glEnableVertexAttribArray(index++);
	}
}

glVertexLayout::~glVertexLayout()
{
	glDeleteVertexArrays(1, &m_array_id);
}

void glVertexLayout::bind()
{
	glBindVertexArray(m_array_id);
}

void glVertexLayout::un_bind()
{
	glBindVertexArray(NULL);
}

auto glVertexLayout::get_element_desc(VertexElementType type, unsigned int offset)
    -> glVertexElementDesc
{
	switch (type)
	{
	/* byte */
	case lt::VertexElementType::Byte1:
		return { .type = GL_BYTE, .count = 1u, .typeSize = sizeof(GLbyte), .offset = offset };
	case lt::VertexElementType::Byte2:
		return { .type = GL_BYTE, .count = 1u, .typeSize = sizeof(GLbyte), .offset = offset };
	case lt::VertexElementType::Byte4:
		return { .type = GL_BYTE, .count = 1u, .typeSize = sizeof(GLbyte), .offset = offset };

	/* ubyte */
	case lt::VertexElementType::UByte1:
		return { .type = GL_UNSIGNED_BYTE,
			     .count = 1u,
			     .typeSize = sizeof(GLubyte),
			     .offset = offset };
	case lt::VertexElementType::UByte2:
		return { .type = GL_UNSIGNED_BYTE,
			     .count = 2u,
			     .typeSize = sizeof(GLubyte),
			     .offset = offset };
	case lt::VertexElementType::UByte4:
		return { .type = GL_UNSIGNED_BYTE,
			     .count = 4u,
			     .typeSize = sizeof(GLubyte),
			     .offset = offset };

	/* int */
	case VertexElementType::Int1:
		return { .type = GL_INT, .count = 1u, .typeSize = sizeof(GLint), .offset = offset };
	case VertexElementType::Int2:
		return { .type = GL_INT, .count = 2u, .typeSize = sizeof(GLint), .offset = offset };
	case VertexElementType::Int3:
		return { .type = GL_INT, .count = 3u, .typeSize = sizeof(GLint), .offset = offset };
	case VertexElementType::Int4:
		return { .type = GL_INT, .count = 4u, .typeSize = sizeof(GLint), .offset = offset };

	/* uint */
	case VertexElementType::UInt1:
		return { .type = GL_UNSIGNED_INT,
			     .count = 1u,
			     .typeSize = sizeof(GLuint),
			     .offset = offset };
	case VertexElementType::UInt2:
		return { .type = GL_UNSIGNED_INT,
			     .count = 2u,
			     .typeSize = sizeof(GLuint),
			     .offset = offset };
	case VertexElementType::UInt3:
		return { .type = GL_UNSIGNED_INT,
			     .count = 3u,
			     .typeSize = sizeof(GLuint),
			     .offset = offset };
	case VertexElementType::UInt4:
		return { .type = GL_UNSIGNED_INT,
			     .count = 4u,
			     .typeSize = sizeof(GLuint),
			     .offset = offset };

	/* float */
	case VertexElementType::Float1:
		return { .type = GL_FLOAT, .count = 1u, .typeSize = sizeof(GLfloat), .offset = offset };
	case VertexElementType::Float2:
		return { .type = GL_FLOAT, .count = 2u, .typeSize = sizeof(GLfloat), .offset = offset };
	case VertexElementType::Float3:
		return { .type = GL_FLOAT, .count = 3u, .typeSize = sizeof(GLfloat), .offset = offset };
	case VertexElementType::Float4:
		return { .type = GL_FLOAT, .count = 4u, .typeSize = sizeof(GLfloat), .offset = offset };

	default: lt_assert(false, "Invalid 'VertexElementType'"); return {};
	}
}

} // namespace lt
