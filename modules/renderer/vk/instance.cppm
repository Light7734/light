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
// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
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

	Instance(const Instance &) = delete;

	auto operator=(const Instance &) -> Instance & = delete;

	Instance(Instance &&other) noexcept = delete;

	auto operator=(Instance &&other) noexcept -> Instance & = delete;

private:
	static auto instance() -> IInstance &
	{
		static auto instance = Instance {};
		return instance;
	}

	Instance();

	~Instance() override;

	vk::Instance m_instance;
};

} // namespace lt::renderer::vkb

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

	m_instance = vk::Instance({
        .application_info = app_info,
        .validation_layer_settings = {
            .enabled = true,
            .validate_core= true,
            .validate_sync = true,
            .thread_safety = true,
            .debug_action = true,
            .enable_message_limit = true,
            .duplicate_message_limit =  std::numeric_limits<u32>::max(),
            .report_flags =  { "info", "warn", "perf", "error", "verbose" },
        },
        .extensions = {
            vk::instance_extension_names::debug_utils,
            vk::instance_extension_names::surface,
            vk::instance_extension_names::platform_surface,
            vk::instance_extension_names::physical_device_properties_2,
        },
    });

	m_instance.load_functions();
}

Instance::~Instance()
{
	vk::unload_library();
}

} // namespace lt::renderer::vkb
