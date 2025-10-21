#pragma once

#include <renderer/backend/vk/vulkan.hpp>
#include <renderer/frontend/context/instance.hpp>

namespace lt::renderer::vk {

/**
 * Responsible for dynamically loading Vulkan library/functions.
 *
 * @note: The delayed vkInstance destruction is due to a work-around for a libx11 quirk:
 * @ref:
 * https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers/commit/0017308648b6bf8eef10ef0ffb9470576c0c2e9e
 * https://www.xfree86.org/4.7.0/DRI11.html
 * https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers/issues/1894
 */
class Instance: public IInstance
{
public:
	static auto get() -> IInstance *
	{
		return &Instance::instance();
	}

	static auto load_device_functions(VkDevice device)
	{
		static_cast<Instance &>(instance()).load_device_functions_impl(device);
	}

	~Instance() override;

	Instance(Instance &&) = delete;

	Instance(const Instance &) = delete;

	auto operator=(const Instance &) -> Instance & = delete;

	auto operator=(Instance &&) -> Instance & = delete;

	[[nodiscard]] auto vk() const -> VkInstance
	{
		return m_instance;
	}

	/* create functions */
	[[nodiscard]] auto create_xlib_surface(VkXlibSurfaceCreateInfoKHR info) const -> VkSurfaceKHR;

	[[nodiscard]] auto create_messenger(VkDebugUtilsMessengerCreateInfoEXT info) const
	    -> VkDebugUtilsMessengerEXT;

	/* destroy functions */
	void destroy_surface(VkSurfaceKHR surface) const;

	void destroy_messenger(VkDebugUtilsMessengerEXT messenger) const;

	[[nodiscard]] auto enumerate_gpus() const -> std::vector<VkPhysicalDevice>;

private:
	static auto instance() -> IInstance &
	{
		static auto instance = Instance {};
		return instance;
	}

	Instance();

	void initialize_instance();

	void load_library();

	void unload_library();

	void load_global_functions();

	void load_instance_functions();

	void load_device_functions_impl(VkDevice device);
	VkInstance m_instance = VK_NULL_HANDLE;

	VkAllocationCallbacks *m_allocator = nullptr;
};

} // namespace lt::renderer::vk
