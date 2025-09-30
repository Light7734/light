#pragma once

#include <renderer/vk/vulkan.hpp>

namespace lt::renderer::vk {

/**
 * Responsible for dynamically loading Vulkan library/functions.
 *
 * @note: The delayed vkInstance destruction is due to a work-around for libx11:
 * @ref:
 * https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers/commit/0017308648b6bf8eef10ef0ffb9470576c0c2e9e
 * https://www.xfree86.org/4.7.0/DRI11.html
 * https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers/issues/1894
 */
class Instance
{
public:
	static auto get() -> VkInstance
	{
		return Instance::instance().m_instance;
	}

	static auto load_device_functions(VkDevice device)
	{
		instance().load_device_functions_impl(device);
	}

	Instance(Instance &&) = delete;

	Instance(const Instance &) = delete;

	auto operator=(const Instance &) -> Instance & = delete;

	auto operator=(Instance &&) -> Instance & = delete;

private:
	static auto instance() -> Instance &
	{
		static auto instance = Instance {};
		return instance;
	}

	Instance();

	~Instance();

	void initialize_instance();

	void load_library();

	void unload_library();

	void load_global_functions();

	void load_instance_functions();

	void load_device_functions_impl(VkDevice device);

	VkInstance m_instance = VK_NULL_HANDLE;
};

} // namespace lt::renderer::vk
