#include <ranges>
#include <renderer/vk/context.hpp>

#if defined(_WIN32)

#elif defined(__unix__)
	#include <dlfcn.h>
namespace {
void *library = nullptr; // NOLINT
}
#endif

namespace lt::renderer::vk {

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
// global functions
PFN_vkGetInstanceProcAddr vk_get_instance_proc_address;
PFN_vkCreateInstance vk_create_instance;
PFN_vkEnumerateInstanceExtensionProperties vk_enumerate_instance_extension_properties;
PFN_vkEnumerateInstanceLayerProperties vk_enumerate_instance_layer_properties;

// instance functions
PFN_vkDestroyInstance vk_destroy_instance;
PFN_vkEnumeratePhysicalDevices vk_enumerate_physical_devices;
PFN_vkGetPhysicalDeviceProperties vk_get_physical_device_properties;
PFN_vkGetPhysicalDeviceQueueFamilyProperties vk_get_physical_device_queue_family_properties;
PFN_vkCreateDevice vk_create_device;
PFN_vkGetDeviceProcAddr vk_get_device_proc_address;
PFN_vkDestroyDevice vk_destroy_device;
PFN_vkGetPhysicalDeviceFeatures vk_get_physical_device_features;
PFN_vkEnumerateDeviceExtensionProperties vk_enumerate_device_extension_properties;

// extension instance functions
PFN_vkCmdBeginDebugUtilsLabelEXT vk_cmd_begin_debug_label;
PFN_vkCmdEndDebugUtilsLabelEXT vk_cmd_end_debug_label;
PFN_vkCmdInsertDebugUtilsLabelEXT vk_cmd_insert_debug_label;
PFN_vkCreateDebugUtilsMessengerEXT vk_create_debug_messenger;
PFN_vkDestroyDebugUtilsMessengerEXT vk_destroy_debug_messenger;
PFN_vkQueueBeginDebugUtilsLabelEXT vk_queue_begin_debug_label;
PFN_vkQueueEndDebugUtilsLabelEXT vk_queue_end_debug_label;
PFN_vkQueueInsertDebugUtilsLabelEXT vk_queue_insert_debug_label;
PFN_vkSetDebugUtilsObjectNameEXT vk_set_debug_object_name;
PFN_vkSetDebugUtilsObjectTagEXT vk_set_debug_object_tag;
PFN_vkSubmitDebugUtilsMessageEXT vk_submit_debug_message;

// device functions
PFN_vkGetDeviceQueue vk_get_device_queue;
PFN_vkCreateCommandPool vk_create_command_pool;
PFN_vkDestroyCommandPool vk_destroy_command_pool;
PFN_vkAllocateCommandBuffers vk_allocate_command_buffers;
PFN_vkFreeCommandBuffers vk_free_command_buffers;
PFN_vkBeginCommandBuffer vk_begin_command_buffer;
PFN_vkEndCommandBuffer vk_end_command_buffer;
PFN_vkCmdPipelineBarrier vk_cmd_pipeline_barrier;
PFN_vkQueueSubmit vk_queue_submit;
PFN_vkQueueWaitIdle vk_queue_wait_idle;
PFN_vkDeviceWaitIdle vk_device_wait_idle;
PFN_vkCreateFence vk_create_fence;
PFN_vkDestroyFence vk_destroy_fence;
PFN_vkWaitForFences vk_wait_for_fences;
PFN_vkResetFences vk_reset_fences;
PFN_vkCreateSemaphore vk_create_semaphore;
PFN_vkDestroySemaphore vk_destroy_semaphore;
PFN_vkCreateSwapchainKHR vk_create_swapchain_khr;
PFN_vkDestroySwapchainKHR vk_destroy_swapchain_khr;
PFN_vkGetSwapchainImagesKHR vk_get_swapchain_images_khr;
PFN_vkAcquireNextImageKHR vk_acquire_next_image_khr;
PFN_vkQueuePresentKHR vk_queue_present_khr;
PFN_vkCreateImageView vk_create_image_view;
PFN_vkDestroyImageView vk_destroy_image_view;
PFN_vkCreateRenderPass vk_create_render_pass;
PFN_vkDestroyRenderPass vk_destroy_render_pass;
PFN_vkCreateFramebuffer vk_create_frame_buffer;
PFN_vkDestroyFramebuffer vk_destroy_frame_buffer;
PFN_vkCreateShaderModule vk_create_shader_module;
PFN_vkDestroyShaderModule vk_destroy_shader_module;
PFN_vkCreatePipelineLayout vk_create_pipeline_layout;
PFN_vkDestroyPipelineLayout vk_destroy_pipeline_layout;
PFN_vkCreateGraphicsPipelines vk_create_graphics_pipelines;
PFN_vkDestroyPipeline vk_destroy_pipeline;
PFN_vkCmdBeginRenderPass vk_cmd_begin_render_pass;
PFN_vkCmdEndRenderPass vk_cmd_end_render_pass;
PFN_vkCmdBindPipeline vk_cmd_bind_pipeline;
PFN_vkCmdDraw vk_cmd_draw;
PFN_vkCmdSetViewport vk_cmd_set_viewport;
PFN_vkCmdSetScissor vk_cmd_set_scissors;

PFN_vkGetPhysicalDeviceSurfaceSupportKHR vk_get_physical_device_surface_support;
PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vk_get_physical_device_surface_capabilities;
PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vk_get_physical_device_surface_formats;

PFN_vkCreateXlibSurfaceKHR vk_create_xlib_surface_khr;
PFN_vkDestroySurfaceKHR vk_destroy_surface_khr;
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

auto parse_message_type(VkDebugUtilsMessageTypeFlagsEXT message_types) -> const char *;

auto parse_message_severity(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity)
    -> app::SystemDiagnosis::Severity;

auto validation_layers_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT const message_severity,
    VkDebugUtilsMessageTypeFlagsEXT const message_types,
    VkDebugUtilsMessengerCallbackDataEXT const *const callback_data,
    void *const vulkan_user_data
) -> VkBool32;


Context::Context(const ecs::Entity &surface_entity, Ref<app::SystemStats> system_stats)
    : m_stats(std::move(system_stats))
{
	ensure(m_stats, "Failed to create Vulkan Context: null stats");

	load_library();
	load_global_functions();

	initialize_instance();
	load_instance_functions();

	initialize_debug_messenger();

	initialize_physical_device();
	initialize_logical_device();
	load_device_functions();

	initialize_surface(surface_entity);
	initialize_queue();
	initialize_swapchain();
}

Context::~Context()
{
	try
	{
		if (m_device)
		{
			vkc(vk_device_wait_idle(m_device));

			for (auto &view : m_swapchain_image_views)
			{
				vk_destroy_image_view(m_device, view, nullptr);
			}

			vk_destroy_swapchain_khr(m_device, m_swapchain, nullptr);
			vk_destroy_device(m_device, nullptr);
		}

		if (m_instance)
		{
			vk_destroy_surface_khr(m_instance, m_surface, nullptr);
			vk_destroy_debug_messenger(m_instance, m_debug_messenger, nullptr);
			// TODO(Light): fix this issue
			// @ref:
			// https://git.light7734.com/light7734/light/commit/f268724034a2ceb63b90dc13aedf86a1eecac62e
			// vk_destroy_instance(m_instance, nullptr);
		}
	}
	catch (const std::exception &exp)
	{
		log_err("Exception: {}", exp.what());
	}
}


void Context::initialize_instance()
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

void Context::initialize_debug_messenger()
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

		.pUserData = &m_stats,
	};

	ensure(
	    !vk_create_debug_messenger(m_instance, &info, nullptr, &m_debug_messenger),
	    "Failed to create vulkan debug utils messenger"
	);
}

void Context::initialize_physical_device()
{
	auto count = 0u;
	vkc(vk_enumerate_physical_devices(m_instance, &count, nullptr));
	ensure(count != 0u, "Failed to find any physical devices with Vulkan support");

	auto devices = std::vector<VkPhysicalDevice>(count);
	vkc(vk_enumerate_physical_devices(m_instance, &count, devices.data()));

	for (auto &device : devices)
	{
		auto properties = VkPhysicalDeviceProperties {};
		auto features = VkPhysicalDeviceFeatures {};

		vk_get_physical_device_properties(device, &properties);
		vk_get_physical_device_features(device, &features);

		if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
		    && features.geometryShader)
		{
			m_physical_device = device;
		}
	}
	ensure(m_physical_device, "Failed to find any suitable Vulkan physical device");
}

void Context::initialize_logical_device()
{
	const float priorities = .0f;

	auto queue_info = VkDeviceQueueCreateInfo {
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		.queueFamilyIndex = find_suitable_queue_family(),
		.queueCount = 1u,
		.pQueuePriorities = &priorities,
	};

	auto physical_device_features = VkPhysicalDeviceFeatures {};

	auto extensions = std::vector<const char *> {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
	};

	auto device_info = VkDeviceCreateInfo {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &queue_info,
		.enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
		.ppEnabledExtensionNames = extensions.data(),
		.pEnabledFeatures = &physical_device_features,
	};

	ensuree
	    !vk_create_device(m_physical_device, &device_info, nullptr, &m_device),
	    "Failed to create logical vulkan device"
	);
}

void Context::initialize_surface(const ecs::Entity &surface_entity)
{
	const auto &component = surface_entity.get<surface::SurfaceComponent>();

	auto create_info = VkXlibSurfaceCreateInfoKHR {
		.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,
		.dpy = component.get_native_data().display,
		.window = component.get_native_data().window,
	};

	vkc(vk_create_xlib_surface_khr(m_instance, &create_info, nullptr, &m_surface));

	const auto &[width, height] = component.get_resolution();
	m_framebuffer_size = {
		.width = width,
		.height = height,
	};
}

void Context::initialize_queue()
{
	vk_get_device_queue(m_device, find_suitable_queue_family(), 0, &m_queue);

	auto count = uint32_t { 0u };
	vk_get_physical_device_queue_family_properties(m_physical_device, &count, nullptr);

	auto properties = std::vector<VkQueueFamilyProperties>(count);
	vk_get_physical_device_queue_family_properties(m_physical_device, &count, properties.data());

	for (auto idx = uint32_t { 0u }; const auto &property : properties)
	{
		if (property.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			m_graphics_queue_family_index = idx;
		}

		auto has_presentation_support = VkBool32 { false };
		vkc(vk_get_physical_device_surface_support(
		    m_physical_device,
		    idx,
		    m_surface,
		    &has_presentation_support
		));
		if (has_presentation_support)
		{
			m_present_queue_family_index = idx;
		}

		++idx;

		if (m_graphics_queue_family_index != VK_QUEUE_FAMILY_IGNORED
		    && m_present_queue_family_index != VK_QUEUE_FAMILY_IGNORED)
		{
			break;
		}
	}

	ensure(
	    m_graphics_queue_family_index != VK_QUEUE_FAMILY_IGNORED,
	    "Failed to find graphics queue family"
	);

	ensure(
	    m_present_queue_family_index != VK_QUEUE_FAMILY_IGNORED,
	    "Failed to find presentation queue family"
	);
}


void Context::initialize_swapchain()
{
	auto capabilities = VkSurfaceCapabilitiesKHR {};
	vkc(vk_get_physical_device_surface_capabilities(m_physical_device, m_surface, &capabilities));

	auto count = uint32_t { 0 };
	vkc(vk_get_physical_device_surface_formats(m_physical_device, m_surface, &count, nullptr));

	auto formats = std::vector<VkSurfaceFormatKHR>(count);
	vkc(
	    vk_get_physical_device_surface_formats(m_physical_device, m_surface, &count, formats.data())
	);
	ensure(!formats.empty(), "Surface has no formats!");

	// TODO(Light): parameterize
	constexpr auto desired_swapchain_image_count = uint32_t { 3 };
	const auto surface_format = formats.front();

	const auto queue_indices = std::array<uint32_t, 2> {
		m_graphics_queue_family_index,
		m_present_queue_family_index,
	};

	auto create_info = VkSwapchainCreateInfoKHR {
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.surface = m_surface,
		.minImageCount = get_optimal_swapchain_image_count(
		    capabilities,
		    desired_swapchain_image_count
		),
		.imageFormat = surface_format.format,
		.imageColorSpace = surface_format.colorSpace,
		.imageExtent = m_framebuffer_size,
		.imageArrayLayers = 1u,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = queue_indices.size(),
		.pQueueFamilyIndices = queue_indices.data(),
		.preTransform = capabilities.currentTransform,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = VK_PRESENT_MODE_FIFO_RELAXED_KHR, // TODO(Light): parameterize
		.clipped = VK_TRUE,
		.oldSwapchain = nullptr,
	};

	vkc(vk_create_swapchain_khr(m_device, &create_info, nullptr, &m_swapchain));
	vkc(vk_device_wait_idle(m_device));

	auto image_count = uint32_t { 0u };
	vk_get_swapchain_images_khr(m_device, m_swapchain, &image_count, nullptr);

	m_swapchain_images.resize(image_count);
	m_swapchain_image_views.resize(image_count);
	vk_get_swapchain_images_khr(m_device, m_swapchain, &image_count, m_swapchain_images.data());

	for (auto [image, view] : std::views::zip(m_swapchain_images, m_swapchain_image_views))
	{
		auto create_info = VkImageViewCreateInfo {
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.image = image,
			.viewType = VK_IMAGE_VIEW_TYPE_2D,
			.format = surface_format.format,
            .components = VkComponentMapping {
                .r = VK_COMPONENT_SWIZZLE_IDENTITY,
                .g = VK_COMPONENT_SWIZZLE_IDENTITY,
                .b = VK_COMPONENT_SWIZZLE_IDENTITY,
                .a = VK_COMPONENT_SWIZZLE_IDENTITY,
            },
            .subresourceRange = VkImageSubresourceRange {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .baseMipLevel = 0u,
                .levelCount = 1u,
                .baseArrayLayer = 0u,
                .layerCount = 1u,
            }
		};

		vkc(vk_create_image_view(m_device, &create_info, nullptr, &view));
	}
}

auto Context::get_optimal_swapchain_image_count(
    VkSurfaceCapabilitiesKHR capabilities,
    uint32_t desired_image_count
) -> uint32_t
{
	const auto min_image_count = capabilities.minImageCount;
	const auto max_image_count = capabilities.maxImageCount;

	const auto has_max_limit = max_image_count != 0;

	// Desired image count is in range
	if ((!has_max_limit || max_image_count >= desired_image_count)
	    && min_image_count <= desired_image_count)
	{
		return desired_image_count;
	}

	// Fall-back to 2 if in ange
	if (min_image_count <= 2 && max_image_count >= 2)
	{
		return 2;
	}

	// Fall-back to min_image_count
	return min_image_count;
}

void Context::load_library()
{
	library = dlopen("libvulkan.so", RTLD_NOW | RTLD_LOCAL);
	ensure(library, "Failed to dlopen libvulkan.so");

	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	vk_get_instance_proc_address = reinterpret_cast<PFN_vkGetInstanceProcAddr>(
	    dlsym(library, "vkGetInstanceProcAddr")
	);
	ensure(vk_get_instance_proc_address, "Failed to load vulkan function: vkGetInstanceProcAddr");
}

void Context::load_global_functions()
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

void Context::load_instance_functions()
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

void Context::load_device_functions()
{
	const auto load_fn = [&]<typename T>(T &pfn, const char *fn_name) {
		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
		pfn = reinterpret_cast<T>(vk_get_device_proc_address(m_device, fn_name));
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

[[nodiscard]] auto Context::find_suitable_queue_family() const -> uint32_t
{
	auto count = 0u;
	vk_get_physical_device_queue_family_properties(m_physical_device, &count, nullptr);
	ensure(count != 0u, "Failed to find any physical devices with Vulkan support");

	auto families = std::vector<VkQueueFamilyProperties>(count);
	vk_get_physical_device_queue_family_properties(m_physical_device, &count, families.data());

	const auto required_flags = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT;
	for (auto idx = 0u; auto &family : families)
	{
		if ((family.queueFlags & required_flags) == required_flags)
		{
			return idx;
		}
	}

	ensure(false, "Failed to find a suitable Vulkan queue family");
	return 0;
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
