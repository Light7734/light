#pragma once

#include <memory/pointer_types/null_on_move.hpp>
#include <renderer/vk/context/instance.hpp>
#include <renderer/vk/vulkan.hpp>

namespace lt::renderer::vk {

class Messenger
{
public:
	// NOLINTNEXTLINE(performance-enum-size)
	enum Severity : decltype(std::to_underlying(
	    VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT
	))
	{
		verbose = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT,
		info = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT,
		warning = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT,
		error = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,

		all_severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
		               | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
		               | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
		               | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
	};

	// NOLINTNEXTLINE(performance-enum-size)
	enum Type : decltype(std::to_underlying(VK_DEBUG_UTILS_MESSAGE_TYPE_FLAG_BITS_MAX_ENUM_EXT))
	{
		general = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT,
		validation = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT,
		performance = VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,

		// address_binding = VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT,

		/** @note: does not include address binding yet. */
		all_type = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
		           | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
		           | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
	};

	using CallbackData_T = const VkDebugUtilsMessengerCallbackDataEXT *;

	using Callback_T = std::function<void(
	    Severity message_severity,
	    Type message_type,
	    CallbackData_T vulkan_data,
	    void *user_data
	)>;

	struct CreateInfo
	{
		Severity severity;

		Type type;

		Callback_T callback;

		void *user_data;
	};

	explicit Messenger(CreateInfo info)
	    : m_callback(std::move(info.callback))
	    , m_user_data(info.user_data)
	{
		ensure(m_callback, "Failed to initialize vk::Messenger: null callback");
		ensure(info.severity != Severity {}, "Failed to initialize vk::Messenger: null severity");
		ensure(info.type != Type {}, "Failed to initialize vk::Messenger: null type");

		// Instance may not be initialized yet
		// Making it get initialized inside a call to vk_create_debug_messenger
		// Which would invoke a nullptr...
		if (!vk_create_debug_messenger)
		{
			Instance::get();
		}

		const auto vulkan_info = VkDebugUtilsMessengerCreateInfoEXT {
			.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
			.messageSeverity = info.severity,
			.messageType = info.type,
			.pfnUserCallback = &validation_layers_callback,
			.pUserData = this,
		};

		ensure(
		    !vk_create_debug_messenger(Instance::get(), &vulkan_info, nullptr, &m_debug_messenger),
		    "Failed to create vulkan debug utils messenger"
		);
	}

	~Messenger()
	{
		vk_destroy_debug_messenger(Instance::get(), m_debug_messenger, nullptr);
	}

	Messenger(Messenger &&) = default;

	Messenger(const Messenger &) = delete;

	auto operator=(Messenger &&) -> Messenger & = default;

	auto operator=(const Messenger &) const -> Messenger & = delete;


private:
	static auto validation_layers_callback(
	    VkDebugUtilsMessageSeverityFlagBitsEXT const message_severity,
	    VkDebugUtilsMessageTypeFlagsEXT const message_type,
	    VkDebugUtilsMessengerCallbackDataEXT const *const callback_data,
	    void *const vulkan_user_data
	) -> VkBool32
	{
		auto *messenger = (Messenger *)vulkan_user_data; // NOLINT
		ensure(messenger, "Null vulkan_user_data received in messenger callback");

		messenger->validation_layers_callback_impl(message_severity, message_type, callback_data);
		return VK_FALSE;
	}

	void validation_layers_callback_impl(
	    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
	    VkDebugUtilsMessageTypeFlagsEXT message_type,
	    const VkDebugUtilsMessengerCallbackDataEXT *callback_data
	)
	{
		m_callback(
		    static_cast<Severity>(message_severity),
		    static_cast<Type>(message_type),
		    callback_data,
		    m_user_data
		);
	}

	memory::NullOnMove<VkDebugUtilsMessengerEXT> m_debug_messenger = VK_NULL_HANDLE;

	Callback_T m_callback;

	void *m_user_data;
};

} // namespace lt::renderer::vk
