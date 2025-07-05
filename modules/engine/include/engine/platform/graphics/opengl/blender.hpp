#pragma once

#include <engine/base/base.hpp>
#include <engine/graphics/blender.hpp>

namespace Light {

class glBlender: public Blender
{
private:
	std::unordered_map<BlendFactor, unsigned int> m_factor_map;

public:
	glBlender();

	void Enable(BlendFactor srcFactor, BlendFactor dstFactor) override;
	void Disable() override;
};

} // namespace Light
