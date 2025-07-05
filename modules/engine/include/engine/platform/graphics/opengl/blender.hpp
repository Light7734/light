#pragma once

#include <engine/base/base.hpp>
#include <engine/graphics/blender.hpp>

namespace Light {

class glBlender: public Blender
{
public:
	glBlender();

	void enable(BlendFactor srcFactor, BlendFactor dstFactor) override;

	void disable() override;

private:
	std::unordered_map<BlendFactor, unsigned int> m_factor_map;
};

} // namespace Light
