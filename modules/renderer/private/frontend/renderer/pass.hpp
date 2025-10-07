#pragma once

#include <renderer/api.hpp>
#include <renderer/frontend/context/swapchain.hpp>

namespace lt::assets {
class ShaderAsset;
}

namespace lt::renderer {

class IPass
{
public:
	[[nodiscard]] static auto create(
	    lt::renderer::Api target_api,
	    class IDevice *device,
	    class ISwapchain *swapchain,
	    const class lt::assets::ShaderAsset &vertex_shader,
	    const class lt::assets::ShaderAsset &fragment_shader
	) -> memory::Scope<IPass>;

	IPass() = default;

	virtual ~IPass() = default;

	IPass(IPass &&) = default;

	IPass(const IPass &) = delete;

	auto operator=(IPass &&) -> IPass & = default;

	auto operator=(const IPass &) -> IPass & = delete;

	void replace_swapchain(const ISwapchain &swapchain);
};

} // namespace lt::renderer
