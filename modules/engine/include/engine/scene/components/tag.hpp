#pragma once

#include <engine/base/base.hpp>

namespace Light {

struct TagComponent
{
	TagComponent() = default;

	TagComponent(const TagComponent &) = default;

	TagComponent(const std::string &_tag): tag(_tag)
	{
	}

	operator std::string()
	{
		return tag;
	}

	operator const std::string &() const
	{
		return tag;
	}

	std::string tag = "Unnamed";
};

} // namespace Light
