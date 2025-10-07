#pragma once

#include <memory/scope.hpp>
#include <renderer/api.hpp>

namespace lt::renderer {

class ISwapchain
{
public:
	[[nodiscard]] static auto create(
	    Api target_api,
	    class ISurface *surface,
	    class IGpu *gpu,
	    class IDevice *device
	) -> memory::Scope<ISwapchain>;

	ISwapchain() = default;

	virtual ~ISwapchain() = default;

	ISwapchain(ISwapchain &&) = default;

	ISwapchain(const ISwapchain &) = delete;

	auto operator=(ISwapchain &&) -> ISwapchain & = default;

	auto operator=(const ISwapchain &) -> ISwapchain & = delete;
};

} // namespace lt::renderer
