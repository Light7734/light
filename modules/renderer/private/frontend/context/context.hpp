#pragma once

#include <ecs/entity.hpp>
#include <memory/scope.hpp>
#include <renderer/api.hpp>
#include <renderer/frontend/context/device.hpp>
#include <renderer/frontend/context/gpu.hpp>
#include <renderer/frontend/context/instance.hpp>
#include <renderer/frontend/context/surface.hpp>
#include <renderer/frontend/context/swapchain.hpp>


namespace lt::renderer {

class IContext
{
public:
	static auto create(API target_api, const ecs::Entity &surface_entity)
	    -> memory::Scope<IContext>;
	IContext() = default;

	virtual ~IContext() = default;

	IContext(IContext &&) = default;

	IContext(const IContext &) = delete;

	auto operator=(IContext &&) -> IContext & = default;

	auto operator=(const IContext &) -> IContext & = delete;

	virtual void recreate_swapchain() = 0;

	[[nodiscard]] virtual auto instance() const -> IInstance * = 0;

	[[nodiscard]] virtual auto surface() const -> ISurface * = 0;

	[[nodiscard]] virtual auto gpu() const -> IGpu * = 0;

	[[nodiscard]] virtual auto device() const -> IDevice * = 0;

	[[nodiscard]] virtual auto swapchain() const -> ISwapchain * = 0;
};


} // namespace lt::renderer
