#pragma once

#include <utility>

namespace lt {

struct TagComponent
{
	TagComponent() = default;

	TagComponent(const TagComponent &) = default;

	TagComponent(std::string _tag): tag(std::move(_tag))
	{
	}

	operator std::string() const
	{
		return tag;
	}

	operator const std::string &() const
	{
		return tag;
	}

	std::string tag = "Unnamed";
};

} // namespace lt
