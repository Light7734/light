export module renderer.backend.vk.instance;
import debug.assertions;
import renderer.frontend;
import renderer.backend.vk.library_wrapper;
// import renderer.backend.vk.library_loader;
import std;

namespace lt::renderer::vkb {

/**
 * Responsible for dynamically loading Vulkan library/functions.
 *
 * @note: The delayed vkInstance destruction is due to a work-around for a libx11 quirk:
 * @ref:
 * https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers/commit/0017308648b6bf8eef10ef0ffb9470576c0c2e9e
 * https://www.xfree86.org/4.7.0/DRI11.html
 * https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers/issues/1894
 */
export class Instance: public IInstance
{
public:
	static auto get() -> IInstance *
	{
		return &Instance::instance();
	}

	[[nodiscard]] auto vk() -> vk::Instance &
	{
		return m_instance;
	}

	// /* create functions */
	// [[nodiscard]] auto create_xlib_surface(VkXlibSurfaceCreateInfoKHR info) const ->
	// VkSurfaceKHR;
	//
	// [[nodiscard]] auto create_messenger(VkDebugUtilsMessengerCreateInfoEXT info) const
	//     -> VkDebugUtilsMessengerEXT;
	//
	// /* destroy functions */
	// void destroy_surface(VkSurfaceKHR surface) const;
	//
	// void destroy_messenger(VkDebugUtilsMessengerEXT messenger) const;
	//
	// [[nodiscard]] auto enumerate_gpus() const -> std::vector<VkPhysicalDevice>;

private:
	static auto instance() -> IInstance &
	{
		static auto instance = Instance {};
		return instance;
	}

	Instance();

	vk::Instance m_instance;
};

} // namespace lt::renderer::vkb

module :private;
using namespace lt::renderer::vkb;

Instance::Instance()
{
	vk::load_library();
	vk::load_global_functions();

	const auto app_info = vk::ApplicationInfo {
		.name = "Hallo Hallo Hallo :3",
		.version = vk::constants::application_version,
		.engine_name = vk::constants::engine_name,
		.engine_version = vk::constants::engine_version,
		.api_version = vk::constants::api_version,
	};

	using Setting = vk::Instance::Layer::Setting;
	const auto validation_layer_settings = std::vector<Setting> {
		Setting { .name = "validate_core", .values = true },
		Setting { .name = "validate_sync", .values = true },
		Setting { .name = "thread_safety", .values = true },
		Setting { .name = "debug_action", .values = true },
		Setting { .name = "enable_message_limit", .values = true },
		Setting {
		    .name = "duplicate_message_limit",
		    .values = std::numeric_limits<std::uint32_t>::max(),
		},
		Setting {
		    .name = "report_flags",
		    .values = std::vector<const char *> { "info", "warn", "perf", "error", "verbose" },
		},
	};


	using Layer = vk::Instance::Layer;
	m_instance = vk::Instance(
	    vk::Instance::CreateInfo {
	        .application_info = app_info,
            .layers = std::vector<Layer> { Layer {
		.name = vk::instance_layer_names::validation,
		.settings = validation_layer_settings,
	} },
            .extensions = {
                vk::instance_extension_names::debug_utils,
                vk::instance_extension_names::surface,
                vk::instance_extension_names::xlib_surface,
                vk::instance_extension_names::physical_device_properties_2,
            },
	    }
	);

	m_instance.load_functions();
}

// auto Instance::enumerate_gpus() const -> std::vector<VkPhysicalDevice>
// {
// 	auto count = 0u;
// 	vkc(vk_enumerate_physical_devices(m_instance, &count, nullptr));
// 	debug::ensure(count != 0u, "Failed to find any gpus with Vulkan support");
//
// 	auto gpus = std::vector<VkPhysicalDevice>(count);
// 	vkc(vk_enumerate_physical_devices(m_instance, &count, gpus.data()));
// 	return gpus;
// }
//
// auto Instance::create_xlib_surface(VkXlibSurfaceCreateInfoKHR info) const -> VkSurfaceKHR
// {
// 	auto *value = VkSurfaceKHR {};
// 	vk_create_xlib_surface_khr(m_instance, &info, m_allocator, &value);
//
// 	return value;
// }
//
// [[nodiscard]] auto Instance::create_messenger(VkDebugUtilsMessengerCreateInfoEXT info) const
//     -> VkDebugUtilsMessengerEXT
// {
// 	auto *messenger = VkDebugUtilsMessengerEXT {};
// 	vkc(vk_create_debug_messenger(m_instance, &info, m_allocator, &messenger));
// 	return messenger;
// }
//
// void Instance::destroy_surface(VkSurfaceKHR surface) const
// {
// 	vk_destroy_surface_khr(m_instance, surface, m_allocator);
// }
//
// void Instance::destroy_messenger(VkDebugUtilsMessengerEXT messenger) const
// {
// 	vk_destroy_debug_messenger(m_instance, messenger, m_allocator);
// }
