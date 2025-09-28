#include <app/system.hpp>
#include <renderer/vk/context/instance.hpp>

#if defined(_WIN32)
	#error "Unsupported platform (currently)"
#elif defined(__unix__)
	#include <dlfcn.h>
namespace {
void *library = nullptr; // NOLINT
}
#endif

namespace lt::renderer::vk {

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
// global functions
PFN_vkGetInstanceProcAddr vk_get_instance_proc_address {};
PFN_vkCreateInstance vk_create_instance {};
PFN_vkEnumerateInstanceExtensionProperties vk_enumerate_instance_extension_properties {};
PFN_vkEnumerateInstanceLayerProperties vk_enumerate_instance_layer_properties {};

// instance functions
PFN_vkDestroyInstance vk_destroy_instance {};
PFN_vkEnumeratePhysicalDevices vk_enumerate_physical_devices {};
PFN_vkGetPhysicalDeviceProperties vk_get_physical_device_properties {};
PFN_vkGetPhysicalDeviceQueueFamilyProperties vk_get_physical_device_queue_family_properties {};
PFN_vkCreateDevice vk_create_device {};
PFN_vkGetDeviceProcAddr vk_get_device_proc_address {};
PFN_vkDestroyDevice vk_destroy_device {};
PFN_vkGetPhysicalDeviceFeatures vk_get_physical_device_features {};
PFN_vkEnumerateDeviceExtensionProperties vk_enumerate_device_extension_properties {};

// extension instance functions
PFN_vkCmdBeginDebugUtilsLabelEXT vk_cmd_begin_debug_label {};
PFN_vkCmdEndDebugUtilsLabelEXT vk_cmd_end_debug_label {};
PFN_vkCmdInsertDebugUtilsLabelEXT vk_cmd_insert_debug_label {};
PFN_vkCreateDebugUtilsMessengerEXT vk_create_debug_messenger {};
PFN_vkDestroyDebugUtilsMessengerEXT vk_destroy_debug_messenger {};
PFN_vkQueueBeginDebugUtilsLabelEXT vk_queue_begin_debug_label {};
PFN_vkQueueEndDebugUtilsLabelEXT vk_queue_end_debug_label {};
PFN_vkQueueInsertDebugUtilsLabelEXT vk_queue_insert_debug_label {};
PFN_vkSetDebugUtilsObjectNameEXT vk_set_debug_object_name {};
PFN_vkSetDebugUtilsObjectTagEXT vk_set_debug_object_tag {};
PFN_vkSubmitDebugUtilsMessageEXT vk_submit_debug_message {};

// device functions
PFN_vkGetDeviceQueue vk_get_device_queue {};
PFN_vkCreateCommandPool vk_create_command_pool {};
PFN_vkDestroyCommandPool vk_destroy_command_pool {};
PFN_vkAllocateCommandBuffers vk_allocate_command_buffers {};
PFN_vkFreeCommandBuffers vk_free_command_buffers {};
PFN_vkBeginCommandBuffer vk_begin_command_buffer {};
PFN_vkEndCommandBuffer vk_end_command_buffer {};
PFN_vkCmdPipelineBarrier vk_cmd_pipeline_barrier {};
PFN_vkQueueSubmit vk_queue_submit {};
PFN_vkQueueWaitIdle vk_queue_wait_idle {};
PFN_vkDeviceWaitIdle vk_device_wait_idle {};
PFN_vkCreateFence vk_create_fence {};
PFN_vkDestroyFence vk_destroy_fence {};
PFN_vkWaitForFences vk_wait_for_fences {};
PFN_vkResetFences vk_reset_fences {};
PFN_vkCreateSemaphore vk_create_semaphore {};
PFN_vkDestroySemaphore vk_destroy_semaphore {};
PFN_vkCreateSwapchainKHR vk_create_swapchain_khr {};
PFN_vkDestroySwapchainKHR vk_destroy_swapchain_khr {};
PFN_vkGetSwapchainImagesKHR vk_get_swapchain_images_khr {};
PFN_vkAcquireNextImageKHR vk_acquire_next_image_khr {};
PFN_vkQueuePresentKHR vk_queue_present_khr {};
PFN_vkCreateImageView vk_create_image_view {};
PFN_vkDestroyImageView vk_destroy_image_view {};
PFN_vkCreateRenderPass vk_create_render_pass {};
PFN_vkDestroyRenderPass vk_destroy_render_pass {};
PFN_vkCreateFramebuffer vk_create_frame_buffer {};
PFN_vkDestroyFramebuffer vk_destroy_frame_buffer {};
PFN_vkCreateShaderModule vk_create_shader_module {};
PFN_vkDestroyShaderModule vk_destroy_shader_module {};
PFN_vkCreatePipelineLayout vk_create_pipeline_layout {};
PFN_vkDestroyPipelineLayout vk_destroy_pipeline_layout {};
PFN_vkCreateGraphicsPipelines vk_create_graphics_pipelines {};
PFN_vkDestroyPipeline vk_destroy_pipeline {};
PFN_vkCmdBeginRenderPass vk_cmd_begin_render_pass {};
PFN_vkCmdEndRenderPass vk_cmd_end_render_pass {};
PFN_vkCmdBindPipeline vk_cmd_bind_pipeline {};
PFN_vkCmdDraw vk_cmd_draw {};
PFN_vkCmdSetViewport vk_cmd_set_viewport {};
PFN_vkCmdSetScissor vk_cmd_set_scissors {};

PFN_vkGetPhysicalDeviceSurfaceSupportKHR vk_get_physical_device_surface_support {};
PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vk_get_physical_device_surface_capabilities {};
PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vk_get_physical_device_surface_formats {};

PFN_vkCreateXlibSurfaceKHR vk_create_xlib_surface_khr {};
PFN_vkDestroySurfaceKHR vk_destroy_surface_khr {};
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

auto parse_message_type(VkDebugUtilsMessageTypeFlagsEXT message_types) -> const char *;

auto parse_message_severity(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity)
    -> app::SystemDiagnosis::Severity;

auto validation_layers_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_types,
    VkDebugUtilsMessengerCallbackDataEXT const *callback_data,
    void *vulkan_user_data
) -> VkBool32;


Instance::Instance()
{
	load_library();
	load_global_functions();

	initialize_instance();
	load_instance_functions();
	initialize_debug_messenger();
}

Instance::~Instance()
{
	if (m_instance)
	{
		vk_destroy_debug_messenger(m_instance, m_debug_messenger, nullptr);
		vk_destroy_instance(m_instance, nullptr);
	}

	unload_library();
}

void Instance::initialize_instance()
{
	auto app_info = VkApplicationInfo {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = "Hallo Hallo Hallo :3",
		.applicationVersion = VK_MAKE_VERSION(1, 4, 0),
		.pEngineName = "light",
		.engineVersion = VK_MAKE_VERSION(1, 4, 0),
		.apiVersion = VK_API_VERSION_1_4,
	};

	auto extensions = std::vector<const char *> {
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
	};
	auto layers = std::vector<const char *> {
		"VK_LAYER_KHRONOS_validation",
	};

	auto instance_info = VkInstanceCreateInfo {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &app_info,
		.enabledLayerCount = static_cast<uint32_t>(layers.size()),
		.ppEnabledLayerNames = layers.data(),
		.enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
		.ppEnabledExtensionNames = extensions.data(),
	};

	{
		auto count = 0u;
		vkc(vk_enumerate_instance_extension_properties(nullptr, &count, nullptr));

		auto extensions = std::vector<VkExtensionProperties>(count);
		vkc(vk_enumerate_instance_extension_properties(nullptr, &count, extensions.data()));

		// log_inf("Available vulkan instance extensions:");
		for (auto &ext : extensions)
		{
			// log_inf("\t{} @ {}", ext.extensionName, ext.specVersion);
		}
	}

	vkc(vk_create_instance(&instance_info, nullptr, &m_instance));
	ensure(m_instance, "Failed to create vulkan instance");
}

void Instance::initialize_debug_messenger()
{
	const auto info = VkDebugUtilsMessengerCreateInfoEXT {
		.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,

		.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
		                   | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
		                   | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
		                   | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,

		.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
		               | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
		               | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,


		.pfnUserCallback = &validation_layers_callback,

		.pUserData = {},
	};

	ensure(
	    !vk_create_debug_messenger(m_instance, &info, nullptr, &m_debug_messenger),
	    "Failed to create vulkan debug utils messenger"
	);
}

void Instance::load_library()
{
	library = dlopen("libvulkan.so", RTLD_NOW | RTLD_LOCAL);
	ensure(library, "Failed to dlopen libvulkan.so");

	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	vk_get_instance_proc_address = reinterpret_cast<PFN_vkGetInstanceProcAddr>(
	    dlsym(library, "vkGetInstanceProcAddr")
	);
	ensure(vk_get_instance_proc_address, "Failed to load vulkan function: vkGetInstanceProcAddr");
}

void Instance::unload_library()
{
	if (!library)
	{
		return;
	}

	// dlclose(library);
	//  library = nullptr;
}

void Instance::load_global_functions()
{
	constexpr auto load_fn = []<typename T>(T &pfn, const char *fn_name) {
		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
		pfn = reinterpret_cast<T>(vk_get_instance_proc_address(nullptr, fn_name));
		ensure(pfn, "Failed to load vulkan global function: {}", fn_name);
		// log_trc("Loaded global function: {}", fn_name);
	};

	load_fn(vk_create_instance, "vkCreateInstance");
	load_fn(vk_enumerate_instance_extension_properties, "vkEnumerateInstanceExtensionProperties");
	load_fn(vk_enumerate_instance_layer_properties, "vkEnumerateInstanceLayerProperties");
}

void Instance::load_instance_functions()
{
	const auto load_fn = [&]<typename T>(T &pfn, const char *fn_name) {
		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
		pfn = reinterpret_cast<T>(vk_get_instance_proc_address(m_instance, fn_name));
		ensure(pfn, "Failed to load vulkan instance function: {}", fn_name);
		// log_trc("Loaded instance function: {}", fn_name);
	};

	load_fn(vk_destroy_instance, "vkDestroyInstance");
	load_fn(vk_enumerate_physical_devices, "vkEnumeratePhysicalDevices");
	load_fn(vk_get_physical_device_properties, "vkGetPhysicalDeviceProperties");
	load_fn(
	    vk_get_physical_device_queue_family_properties,
	    "vkGetPhysicalDeviceQueueFamilyProperties"
	);
	load_fn(vk_create_device, "vkCreateDevice");
	load_fn(vk_get_device_proc_address, "vkGetDeviceProcAddr");
	load_fn(vk_destroy_device, "vkDestroyDevice");
	load_fn(vk_get_physical_device_features, "vkGetPhysicalDeviceFeatures");
	load_fn(vk_enumerate_device_extension_properties, "vkEnumerateDeviceExtensionProperties");

	load_fn(vk_cmd_begin_debug_label, "vkCmdBeginDebugUtilsLabelEXT");
	load_fn(vk_cmd_end_debug_label, "vkCmdEndDebugUtilsLabelEXT");
	load_fn(vk_cmd_insert_debug_label, "vkCmdInsertDebugUtilsLabelEXT");
	load_fn(vk_create_debug_messenger, "vkCreateDebugUtilsMessengerEXT");
	load_fn(vk_destroy_debug_messenger, "vkDestroyDebugUtilsMessengerEXT");
	load_fn(vk_queue_begin_debug_label, "vkQueueBeginDebugUtilsLabelEXT");
	load_fn(vk_queue_end_debug_label, "vkQueueEndDebugUtilsLabelEXT");
	load_fn(vk_queue_insert_debug_label, "vkQueueInsertDebugUtilsLabelEXT");
	load_fn(vk_set_debug_object_name, "vkSetDebugUtilsObjectNameEXT");
	load_fn(vk_set_debug_object_tag, "vkSetDebugUtilsObjectTagEXT");
	load_fn(vk_submit_debug_message, "vkSubmitDebugUtilsMessageEXT");

	load_fn(vk_get_physical_device_surface_support, "vkGetPhysicalDeviceSurfaceSupportKHR");
	load_fn(
	    vk_get_physical_device_surface_capabilities,
	    "vkGetPhysicalDeviceSurfaceCapabilitiesKHR"
	);
	load_fn(vk_get_physical_device_surface_formats, "vkGetPhysicalDeviceSurfaceFormatsKHR");
	load_fn(vk_create_xlib_surface_khr, "vkCreateXlibSurfaceKHR");
	load_fn(vk_destroy_surface_khr, "vkDestroySurfaceKHR");
}

void Instance::load_device_functions_impl(VkDevice device)
{
	const auto load_fn = [&]<typename T>(T &pfn, const char *fn_name) {
		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
		pfn = reinterpret_cast<T>(vk_get_device_proc_address(device, fn_name));
		ensure(pfn, "Failed to load vulkan device function: {}", fn_name);
		// log_trc("Loaded device function: {}", fn_name);
	};

	load_fn(vk_get_device_queue, "vkGetDeviceQueue");
	load_fn(vk_create_command_pool, "vkCreateCommandPool");
	load_fn(vk_destroy_command_pool, "vkDestroyCommandPool");
	load_fn(vk_allocate_command_buffers, "vkAllocateCommandBuffers");
	load_fn(vk_free_command_buffers, "vkFreeCommandBuffers");
	load_fn(vk_begin_command_buffer, "vkBeginCommandBuffer");
	load_fn(vk_end_command_buffer, "vkEndCommandBuffer");
	load_fn(vk_cmd_pipeline_barrier, "vkCmdPipelineBarrier");
	load_fn(vk_queue_submit, "vkQueueSubmit");
	load_fn(vk_queue_wait_idle, "vkQueueWaitIdle");
	load_fn(vk_device_wait_idle, "vkDeviceWaitIdle");
	load_fn(vk_create_fence, "vkCreateFence");
	load_fn(vk_destroy_fence, "vkDestroyFence");
	load_fn(vk_wait_for_fences, "vkWaitForFences");
	load_fn(vk_reset_fences, "vkResetFences");
	load_fn(vk_create_semaphore, "vkCreateSemaphore");
	load_fn(vk_destroy_semaphore, "vkDestroySemaphore");
	load_fn(vk_create_swapchain_khr, "vkCreateSwapchainKHR");
	load_fn(vk_destroy_swapchain_khr, "vkDestroySwapchainKHR");
	load_fn(vk_get_swapchain_images_khr, "vkGetSwapchainImagesKHR");
	load_fn(vk_acquire_next_image_khr, "vkAcquireNextImageKHR");
	load_fn(vk_queue_present_khr, "vkQueuePresentKHR");
	load_fn(vk_create_image_view, "vkCreateImageView");
	load_fn(vk_destroy_image_view, "vkDestroyImageView");
	load_fn(vk_create_render_pass, "vkCreateRenderPass");
	load_fn(vk_destroy_render_pass, "vkDestroyRenderPass");
	load_fn(vk_create_frame_buffer, "vkCreateFramebuffer");
	load_fn(vk_destroy_frame_buffer, "vkDestroyFramebuffer");
	load_fn(vk_create_shader_module, "vkCreateShaderModule");
	load_fn(vk_destroy_shader_module, "vkDestroyShaderModule");
	load_fn(vk_create_pipeline_layout, "vkCreatePipelineLayout");
	load_fn(vk_destroy_pipeline_layout, "vkDestroyPipelineLayout");
	load_fn(vk_create_graphics_pipelines, "vkCreateGraphicsPipelines");
	load_fn(vk_destroy_pipeline, "vkDestroyPipeline");
	load_fn(vk_cmd_begin_render_pass, "vkCmdBeginRenderPass");
	load_fn(vk_cmd_end_render_pass, "vkCmdEndRenderPass");
	load_fn(vk_cmd_bind_pipeline, "vkCmdBindPipeline");
	load_fn(vk_cmd_draw, "vkCmdDraw");
	load_fn(vk_cmd_set_viewport, "vkCmdSetViewport");
	load_fn(vk_cmd_set_scissors, "vkCmdSetScissor");
}

auto parse_message_type(VkDebugUtilsMessageTypeFlagsEXT message_types) -> const char *
{
	if (message_types == VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
	{
		return "GENERAL";
	}

	if (message_types
	    == (VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
	        | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT))
	{
		return "VALIDATION | PERFORMANCE";
	}

	if (message_types == VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
	{
		return "VALIDATION";
	}

	return "PERFORMANCE";
}

auto parse_message_severity(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity)
    -> app::SystemDiagnosis::Severity
{
	using enum app::SystemDiagnosis::Severity;

	switch (message_severity)
	{
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: return verbose;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: return info;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: return warning;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: return error;
	default: ensure(false, "Invalid message severity: {}", static_cast<int>(message_severity));
	}

	return {};
}

auto validation_layers_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT const message_severity,
    VkDebugUtilsMessageTypeFlagsEXT const message_types,
    VkDebugUtilsMessengerCallbackDataEXT const *const callback_data,
    void *const vulkan_user_data
) -> VkBool32
{
	std::cout << callback_data->pMessage << std::endl;
	return VK_FALSE;

	log_dbg("VALIDATION: {}", callback_data->pMessage);

	ensure(vulkan_user_data, "Validation layers's user data is not set!");

	auto stats = *(Ref<app::SystemStats> *)vulkan_user_data; // NOLINT

	const auto &type = parse_message_type(message_types);

	auto message = std::format(
	    "Vulkan Validation Message:\ntype: {}\nseverity: {}\nmessage: {}",
	    type,
	    std::to_underlying(parse_message_severity(message_severity)),
	    callback_data->pMessage
	);

	auto severity = parse_message_severity(message_severity);
	if (std::to_underlying(severity) < 2)
	{
		return static_cast<VkBool32>(VK_FALSE);
	}

	stats->push_diagnosis(
	    app::SystemDiagnosis {
	        .message = message,
	        .code = {}, // TODO(Light): extract vulkan validation-layers code from the message
	        .severity = severity,
	    }
	);
	return static_cast<VkBool32>(VK_FALSE);
}

} // namespace lt::renderer::vk
