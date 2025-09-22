#pragma once

#define VK_NO_PROTOTYPES
#define VK_USE_PLATFORM_XLIB_KHR
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_xlib.h>

//
#include <ecs/entity.hpp>

namespace lt::renderer::vk {

class Surface
{
public:
	Surface(ecs::Entity entity)
	{
	}

	~Surface();

private:
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;
};

} // namespace lt::renderer::vk
