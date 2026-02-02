export module surface.requests;

import preliminary;
import math.vec2;

export namespace lt::surface {

struct ModifyTitleRequest
{
	std::string title;
};

struct ModifyResolutionRequest
{
	math::vec2_u32 resolution;
};

struct ModifyPositionRequest
{
	math::vec2_i32 position;
};

struct ModifyVisibilityRequest
{
	bool visible;
};

}; // namespace lt::surface
