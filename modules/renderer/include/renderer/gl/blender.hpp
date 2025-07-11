#pragma once


#include <renderer/blender.hpp>

namespace lt {

class glBlender: public Blender
{
public:
	virtual ~glBlender() = default;
	glBlender();

	void enable(BlendFactor srcFactor, BlendFactor dstFactor) override;

	void disable() override;

private:
	std::unordered_map<BlendFactor, unsigned int> m_factor_map;
};

} // namespace lt
