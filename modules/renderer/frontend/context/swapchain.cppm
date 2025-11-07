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


#include <renderer/backend/vk/context/swapchain.hpp>
#include <renderer/frontend/context/swapchain.hpp>

namespace lt::renderer {

[[nodiscard]] /* static */ auto ISwapchain::create(
    Api target_api,
    ISurface *surface,
    IGpu *gpu,
    IDevice *device
) -> memory::Scope<ISwapchain>
{
	switch (target_api)
	{
	case Api::vulkan: return memory::create_scope<vk::Swapchain>(surface, gpu, device);
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}
}


} // namespace lt::renderer
