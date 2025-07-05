#pragma once

#include <engine/base/base.hpp>
#include <engine/core/uuid.hpp>

namespace Light {

struct UUIDComponent
{
	UUID uuid;

	UUIDComponent(UUID _uuid): uuid(_uuid)
	{
	}
	UUIDComponent(const UUIDComponent &) = default;
};

} // namespace Light
