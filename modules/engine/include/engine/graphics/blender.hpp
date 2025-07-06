#pragma once

#include <engine/base/base.hpp>

namespace Light {

class SharedContext;

enum class BlendFactor : uint8_t
{
	// constants
	ZERO,
	ONE,

	// source
	SRC_COLOR,
	INVERSE_SRC_COLOR,

	SRC_ALPHA,
	INVERSE_SRC_ALPHA,

	// destination
	DST_COLOR,
	INVERSE_DST_COLOR,

	DST_ALPHA,
	INVERSE_DST_ALPHA,

	// source1
	SRC1_COLOR,
	INVERSE_SRC1_COLOR,

	SRC1_ALPHA,
	INVERSE_SRC1_ALPHA,
};

class Blender
{
public:
	static auto create(Ref<SharedContext> sharedContext) -> Scope<Blender>;

	virtual void enable(BlendFactor srcFactor, BlendFactor dstFactor) = 0;

	virtual void disable() = 0;

protected:
	Blender() = default;
};

} // namespace Light
