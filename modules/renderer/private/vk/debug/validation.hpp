#pragma once

#include <renderer/vk/vulkan.hpp>

namespace lt::renderer::vk {

inline void vkc(VkResult result)
{
	if (result)
	{
		throw std::runtime_error {
			std::format("Vulkan call failed with result: {}", std::to_underlying(result))
		};
	}
}

} // namespace lt::renderer::vk
