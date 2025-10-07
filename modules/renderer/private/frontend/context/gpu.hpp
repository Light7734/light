#pragma once

#include <memory/scope.hpp>
#include <renderer/api.hpp>

namespace lt::renderer {

class IGpu
{
public:
	[[nodiscard]] static auto create(Api target_api, class IInstance *instance)
	    -> memory::Scope<IGpu>;

	IGpu() = default;

	virtual ~IGpu() = default;

	IGpu(IGpu &&) = default;

	IGpu(const IGpu &) = delete;

	auto operator=(IGpu &&) -> IGpu & = default;

	auto operator=(const IGpu &) -> IGpu & = delete;
};

} // namespace lt::renderer
