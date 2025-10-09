#pragma once

#include <renderer/api.hpp>

namespace lt::renderer {

class IInstance
{
public:
	[[nodiscard]] static auto get(Api target_api) -> IInstance *;
	IInstance() = default;

	virtual ~IInstance() = default;

	IInstance(IInstance &&) = default;

	IInstance(const IInstance &) = delete;

	auto operator=(IInstance &&) -> IInstance & = default;

	auto operator=(const IInstance &) -> IInstance & = delete;
};

} // namespace lt::renderer
