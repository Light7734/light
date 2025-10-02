#pragma once

#include <app/system.hpp>
#include <ecs/entity.hpp>
#include <memory/pointer_types/null_on_move.hpp>
#include <surface/components.hpp>

//
#include <renderer/vk/context/device.hpp>
#include <renderer/vk/context/instance.hpp>
#include <renderer/vk/context/surface.hpp>
#include <renderer/vk/context/swapchain.hpp>

namespace lt::renderer::vk {

using memory::NullOnMove;

class Context
{
public:
	Context(const ecs::Entity &surface_entity);

	[[nodiscard]] auto instance() const -> VkInstance
	{
		return Instance::get();
	}

	[[nodiscard]] auto device() const -> const Device &
	{
		return m_device;
	}

	[[nodiscard]] auto swapchain() const -> const Swapchain &
	{
		return m_swapchain;
	}

	void recreate_swapchain()
	{
		m_swapchain.destroy();
		m_swapchain = Swapchain { m_device, m_surface };
	}

private:
	Surface m_surface;

	Device m_device;

	Swapchain m_swapchain;
};

} // namespace lt::renderer::vk
