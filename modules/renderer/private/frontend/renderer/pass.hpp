#pragma once

#include <renderer/frontend/context/swapchain.hpp>

namespace lt::renderer {

class IPass
{
public:
	IPass() = default;

	virtual ~IPass() = default;

	IPass(IPass &&) = default;

	IPass(const IPass &) = delete;

	auto operator=(IPass &&) -> IPass & = default;

	auto operator=(const IPass &) -> IPass & = delete;

	void replace_swapchain(const ISwapchain &swapchain);
};

} // namespace lt::renderer
