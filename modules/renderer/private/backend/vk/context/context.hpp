#pragma once

#include <ecs/entity.hpp>
#include <memory/pointer_types/null_on_move.hpp>
#include <memory/scope.hpp>
#include <renderer/frontend/context/context.hpp>

namespace lt::renderer::vk {

using memory::NullOnMove;

/** A layer of glue between main graphics objects. */
class Context: public IContext
{
public:
	Context(const ecs::Entity &surface_entity);

	[[nodiscard]] auto instance() const -> IInstance * override
	{
		return m_instance;
	}

	[[nodiscard]] auto gpu() const -> IGpu * override
	{
		return m_gpu.get();
	}

	[[nodiscard]] auto device() const -> IDevice * override
	{
		return m_device.get();
	}

	[[nodiscard]] auto swapchain() const -> ISwapchain * override
	{
		return m_swapchain.get();
	}

	[[nodiscard]] auto surface() const -> ISurface * override
	{
		return m_surface.get();
	}

	void recreate_swapchain() override
	{
		m_swapchain.reset();
		// m_swapchain = memory::create_scope<vk::Swapchain>(m_device, m_surface);
	}

private:
	IInstance *m_instance;

	memory::Scope<ISurface> m_surface;

	memory::Scope<IGpu> m_gpu;

	memory::Scope<IDevice> m_device;

	memory::Scope<ISwapchain> m_swapchain;
};

} // namespace lt::renderer::vk
