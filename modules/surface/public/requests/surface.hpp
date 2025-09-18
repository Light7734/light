#pragma once

#include <math/vec2.hpp>

namespace lt::surface {

struct ModifyTitleRequest
{
	std::string title;
};

struct ModifyResolutionRequest
{
	math::uvec2 resolution;
};

struct ModifyPositionRequest
{
	math::ivec2 position;
};

struct ModifyVisibilityRequest
{
	bool visible;
};

}; // namespace lt::surface
