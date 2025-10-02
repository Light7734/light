#pragma once

#include <renderer/vk/vulkan.hpp>
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

template<typename T>
inline auto get_object_type(T object) -> VkObjectType
{
	if constexpr (std::is_same_v<T, VkQueue>)
	{
		return VK_OBJECT_TYPE_QUEUE;
	}

	if constexpr (std::is_same_v<T, VkFence>)
	{
		return VK_OBJECT_TYPE_FENCE;
	}

	if constexpr (std::is_same_v<T, VkSemaphore>)
	{
		return VK_OBJECT_TYPE_SEMAPHORE;
	}

	if constexpr (std::is_same_v<T, VkSwapchainKHR>)
	{
		return VK_OBJECT_TYPE_SWAPCHAIN_KHR;
	}

	static_assert("invalid type");
}

template<typename T, typename... Args>
inline void set_object_name(
    VkDevice device,
    T object,
    std::format_string<Args...> fmt,
    Args &&...args
)
{
	const auto name = std::format(fmt, std::forward<Args>(args)...);
	auto info = VkDebugUtilsObjectNameInfoEXT {
		.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
		.objectType = get_object_type(object),
		.objectHandle = (uint64_t)(object),
		.pObjectName = name.c_str(),
	};

	vk_set_debug_object_name(device, &info);
}

} // namespace lt::renderer::vk
