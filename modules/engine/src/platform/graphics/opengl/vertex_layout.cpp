#include <engine/platform/graphics/opengl/buffers.hpp>
#include <engine/platform/graphics/opengl/vertex_layout.hpp>
#include <glad/gl.h>

namespace Light {

glVertexLayout::glVertexLayout(
    Ref<VertexBuffer> buffer,
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

	default: lt_assert(false, "Invalid 'VertexElementType'"); return {};
	}
}

} // namespace Light
