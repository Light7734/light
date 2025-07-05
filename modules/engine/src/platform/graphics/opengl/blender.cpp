#include <engine/platform/graphics/opengl/blender.hpp>
#include <glad/gl.h>

namespace Light {

glBlender::glBlender()
    : m_factor_map { // constants
	                { BlendFactor::ZERO, GL_ZERO },
	                { BlendFactor::ONE, GL_ONE },

	                // source						 ,
	                { BlendFactor::SRC_COLOR, GL_SRC_COLOR },
	                { BlendFactor::INVERSE_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR },

	                { BlendFactor::SRC_ALPHA, GL_SRC_ALPHA },
	                { BlendFactor::INVERSE_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA },

	                // destination					 ,
	                { BlendFactor::DST_COLOR, GL_DST_COLOR },
	                { BlendFactor::INVERSE_DST_COLOR, GL_ONE_MINUS_DST_COLOR },

	                { BlendFactor::DST_ALPHA, GL_DST_ALPHA },
	                { BlendFactor::INVERSE_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA },

	                // source1						 ,
	                { BlendFactor::SRC1_COLOR, GL_SRC1_COLOR },
	                { BlendFactor::INVERSE_SRC1_COLOR, GL_ONE_MINUS_SRC1_COLOR },

	                { BlendFactor::SRC1_ALPHA, GL_SRC1_ALPHA },
	                { BlendFactor::INVERSE_SRC1_ALPHA, GL_ONE_MINUS_SRC_ALPHA }
    }
{
}

void glBlender::enable(BlendFactor srcFactor, BlendFactor dstFactor)
{
	glEnable(GL_BLEND);
	glBlendFunc(m_factor_map.at(srcFactor), m_factor_map.at(dstFactor));
}

void glBlender::disable()
{
	glDisable(GL_BLEND);
}

} // namespace Light
