#pragma once


#include <engine/core/uuid.hpp>

namespace lt {

struct UUIDComponent
{
	UUIDComponent(UUID _uuid): uuid(_uuid)
	{
	}

	UUIDComponent(const UUIDComponent &) = default;

	UUID uuid;
};

} // namespace lt
