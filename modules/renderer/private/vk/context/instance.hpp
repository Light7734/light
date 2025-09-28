#pragma once

#define VK_NO_PROTOTYPES
#define VK_USE_PLATFORM_XLIB_KHR
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_xlib.h>

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
// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
// global functions
extern PFN_vkGetInstanceProcAddr vk_get_instance_proc_address;
extern PFN_vkCreateInstance vk_create_instance;
extern PFN_vkEnumerateInstanceExtensionProperties vk_enumerate_instance_extension_properties;
extern PFN_vkEnumerateInstanceLayerProperties vk_enumerate_instance_layer_properties;

// instance functions
extern PFN_vkDestroyInstance vk_destroy_instance;
extern PFN_vkEnumeratePhysicalDevices vk_enumerate_physical_devices;
extern PFN_vkGetPhysicalDeviceProperties vk_get_physical_device_properties;
extern PFN_vkGetPhysicalDeviceQueueFamilyProperties vk_get_physical_device_queue_family_properties;
extern PFN_vkCreateDevice vk_create_device;
extern PFN_vkGetDeviceProcAddr vk_get_device_proc_address;
extern PFN_vkDestroyDevice vk_destroy_device;
extern PFN_vkGetPhysicalDeviceFeatures vk_get_physical_device_features;
extern PFN_vkEnumerateDeviceExtensionProperties vk_enumerate_device_extension_properties;

// extension instance functions
extern PFN_vkCmdBeginDebugUtilsLabelEXT vk_cmd_begin_debug_label;
extern PFN_vkCmdEndDebugUtilsLabelEXT vk_cmd_end_debug_label;
extern PFN_vkCmdInsertDebugUtilsLabelEXT vk_cmd_insert_debug_label;
extern PFN_vkCreateDebugUtilsMessengerEXT vk_create_debug_messenger;
extern PFN_vkDestroyDebugUtilsMessengerEXT vk_destroy_debug_messenger;
extern PFN_vkQueueBeginDebugUtilsLabelEXT vk_queue_begin_debug_label;
extern PFN_vkQueueEndDebugUtilsLabelEXT vk_queue_end_debug_label;
extern PFN_vkQueueInsertDebugUtilsLabelEXT vk_queue_insert_debug_label;
extern PFN_vkSetDebugUtilsObjectNameEXT vk_set_debug_object_name;
extern PFN_vkSetDebugUtilsObjectTagEXT vk_set_debug_object_tag;
extern PFN_vkSubmitDebugUtilsMessageEXT vk_submit_debug_message;

// surface instance functions
extern PFN_vkGetPhysicalDeviceSurfaceSupportKHR vk_get_physical_device_surface_support;
extern PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vk_get_physical_device_surface_capabilities;
extern PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vk_get_physical_device_surface_formats;
extern PFN_vkCreateXlibSurfaceKHR vk_create_xlib_surface_khr;
extern PFN_vkDestroySurfaceKHR vk_destroy_surface_khr;

// device functions
extern PFN_vkGetDeviceQueue vk_get_device_queue;
extern PFN_vkCreateCommandPool vk_create_command_pool;
extern PFN_vkDestroyCommandPool vk_destroy_command_pool;
extern PFN_vkAllocateCommandBuffers vk_allocate_command_buffers;
extern PFN_vkFreeCommandBuffers vk_free_command_buffers;
extern PFN_vkBeginCommandBuffer vk_begin_command_buffer;
extern PFN_vkEndCommandBuffer vk_end_command_buffer;
extern PFN_vkCmdPipelineBarrier vk_cmd_pipeline_barrier;
extern PFN_vkQueueSubmit vk_queue_submit;
extern PFN_vkQueueWaitIdle vk_queue_wait_idle;
extern PFN_vkDeviceWaitIdle vk_device_wait_idle;
extern PFN_vkCreateFence vk_create_fence;
extern PFN_vkDestroyFence vk_destroy_fence;
extern PFN_vkWaitForFences vk_wait_for_fences;
extern PFN_vkResetFences vk_reset_fences;
extern PFN_vkCreateSemaphore vk_create_semaphore;
extern PFN_vkDestroySemaphore vk_destroy_semaphore;
extern PFN_vkCreateSwapchainKHR vk_create_swapchain_khr;
extern PFN_vkDestroySwapchainKHR vk_destroy_swapchain_khr;
extern PFN_vkGetSwapchainImagesKHR vk_get_swapchain_images_khr;
extern PFN_vkAcquireNextImageKHR vk_acquire_next_image_khr;
extern PFN_vkQueuePresentKHR vk_queue_present_khr;
extern PFN_vkCreateImageView vk_create_image_view;
extern PFN_vkDestroyImageView vk_destroy_image_view;
extern PFN_vkCreateRenderPass vk_create_render_pass;
extern PFN_vkDestroyRenderPass vk_destroy_render_pass;
extern PFN_vkCreateFramebuffer vk_create_frame_buffer;
extern PFN_vkDestroyFramebuffer vk_destroy_frame_buffer;
extern PFN_vkCreateShaderModule vk_create_shader_module;
extern PFN_vkDestroyShaderModule vk_destroy_shader_module;
extern PFN_vkCreatePipelineLayout vk_create_pipeline_layout;
extern PFN_vkDestroyPipelineLayout vk_destroy_pipeline_layout;
extern PFN_vkCreateGraphicsPipelines vk_create_graphics_pipelines;
extern PFN_vkDestroyPipeline vk_destroy_pipeline;
extern PFN_vkCmdBeginRenderPass vk_cmd_begin_render_pass;
extern PFN_vkCmdEndRenderPass vk_cmd_end_render_pass;
extern PFN_vkCmdBindPipeline vk_cmd_bind_pipeline;
extern PFN_vkCmdDraw vk_cmd_draw;
extern PFN_vkCmdSetViewport vk_cmd_set_viewport;
extern PFN_vkCmdSetScissor vk_cmd_set_scissors;

// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

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

	void initialize_debug_messenger();

	void load_library();

	void unload_library();

	void load_global_functions();

	void load_instance_functions();

	void load_device_functions_impl(VkDevice device);

	VkInstance m_instance = VK_NULL_HANDLE;

	VkDebugUtilsMessengerEXT m_debug_messenger = VK_NULL_HANDLE;
};

} // namespace lt::renderer::vk
