#pragma once

#include <memory/scope.hpp>
#include <renderer/api.hpp>

namespace lt::renderer {

class IDevice
{
public:
	[[nodiscard]] static auto create(Api target_api, class IGpu *gpu, class ISurface *surface)
	    -> memory::Scope<IDevice>;

	IDevice() = default;

	virtual ~IDevice() = default;

	IDevice(IDevice &&) = default;

	IDevice(const IDevice &) = delete;

	auto operator=(IDevice &&) -> IDevice & = default;

	auto operator=(const IDevice &) -> IDevice & = delete;
};

} // namespace lt::renderer
