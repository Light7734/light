#pragma once

#include <ecs/entity.hpp>
#include <memory/pointer_types/null_on_move.hpp>
#include <renderer/vk/context/instance.hpp>

namespace lt::renderer::vk {

class Surface
{
public:
	Surface(ecs::Entity surface_entity);

	~Surface();

	Surface(Surface &&) = default;

	Surface(const Surface &) = delete;

	auto operator=(Surface &&) -> Surface & = default;

	auto operator=(const Surface &) const -> Surface & = delete;

	[[nodiscard]] auto vk() const -> VkSurfaceKHR
	{
		return m_surface;
	}

	[[nodiscard]] auto get_framebuffer_size() const -> VkExtent2D;

private:
	memory::NullOnMove<VkSurfaceKHR> m_surface = VK_NULL_HANDLE;

	ecs::Entity m_surface_entity;
};

} // namespace lt::renderer::vk
