#pragma once

#include <renderer/backend/vk/vulkan.hpp>
#include <vulkan/vk_enum_string_helper.h>

namespace lt::renderer::vk {

inline void vkc(VkResult result)
{
	if (result)
	{
		throw std::runtime_error { std::format(
			"Vulkan call failed with result: {}({})",
			string_VkResult(result),
			std::to_underlying(result)
		) };
	}
}

} // namespace lt::renderer::vk
