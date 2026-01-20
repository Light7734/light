export module renderer.vk.instance;

import preliminary;
import renderer.frontend;
import renderer.vk.api_wrapper;

export namespace lt::renderer::vkb {

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

	[[nodiscard]] auto vk() -> vk::Instance &
	{
		return m_instance;
	}

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
namespace lt::renderer::vkb {

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
		    .values = std::numeric_limits<u32>::max(),
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
                vk::instance_extension_names::platform_surface,
                vk::instance_extension_names::physical_device_properties_2,
            },
	    }
	);

	m_instance.load_functions();
}

} // namespace lt::renderer::vkb
