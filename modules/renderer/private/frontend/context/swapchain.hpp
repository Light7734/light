#pragma once

namespace lt::renderer {

class ISwapchain
{
public:
	ISwapchain() = default;

	virtual ~ISwapchain() = default;

	ISwapchain(ISwapchain &&) = default;

	ISwapchain(const ISwapchain &) = delete;

	auto operator=(ISwapchain &&) -> ISwapchain & = default;

	auto operator=(const ISwapchain &) -> ISwapchain & = delete;
};

} // namespace lt::renderer
