#pragma once

#include <ecs/entity.hpp>
#include <memory/pointer_types/null_on_move.hpp>
#include <renderer/backend/vk/vulkan.hpp>
#include <renderer/frontend/context/instance.hpp>
#include <renderer/frontend/context/surface.hpp>

namespace lt::renderer::vk {

class Instance;

class Surface: public ISurface
{
public:
	Surface(IInstance *instance, const ecs::Entity &surface_entity);

	~Surface() override;

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
	class Instance *m_instance {};

	VkSurfaceKHR m_surface = VK_NULL_HANDLE;

	ecs::Entity m_surface_entity;
};

} // namespace lt::renderer::vk
