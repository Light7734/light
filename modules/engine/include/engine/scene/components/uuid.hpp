#pragma once


#include <engine/core/uuid.hpp>

namespace Light {

struct UUIDComponent
{
	UUIDComponent(UUID _uuid): uuid(_uuid)
	{
	}

	UUIDComponent(const UUIDComponent &) = default;

	UUID uuid;
};

} // namespace Light
