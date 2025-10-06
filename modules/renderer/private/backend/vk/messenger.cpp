#include <renderer/backend/vk/messenger.hpp>

namespace lt::renderer::vk {

Messenger::Messenger(IInstance *instance, ecs::Entity entity)
    : m_instance(static_cast<Instance *>(instance))
    , m_entity(std::move(entity))

{
	const auto &component = m_entity.get<MessengerComponent>();

	m_debug_messenger = m_instance->create_messenger(
	    VkDebugUtilsMessengerCreateInfoEXT {
	        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
	        .messageSeverity = to_native_severity(component.get_severities()),
	        .messageType = to_native_type(component.get_types()),
	        .pfnUserCallback = &native_callback,
	        .pUserData = this,
	    }
	);
}

Messenger::~Messenger()
{
	if (!m_instance)
	{
		return;
	}

	m_instance->destroy_messenger(m_debug_messenger);
}

/*static*/ auto Messenger::native_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT severity,
    VkDebugUtilsMessageTypeFlagsEXT type,
    const VkDebugUtilsMessengerCallbackDataEXT *callback_data,
    void *vulkan_user_data
) -> VkBool32
{
	try
	{
		ensure(vulkan_user_data, "Null vulkan_user_data received in messenger callback");

		auto *messenger = (Messenger *)vulkan_user_data; // NOLINT
		auto &component = messenger->m_entity.get<MessengerComponent>();
		component.get_callback()(
		    from_native_severity(severity),
		    from_native_type(type),
		    {
		        .message = callback_data->pMessage,
		    },
		    component.get_user_data()
		);
	}
	catch (const std::exception &exp)
	{
		log_err("Uncaught exception in messenger callback:");
		log_err("\twhat: {}", exp.what());
	}

	return VK_FALSE;
}

[[nodiscard]] /*static*/ auto Messenger::to_native_severity(MessageSeverity severity)
    -> VkDebugUtilsMessageSeverityFlagsEXT
{
	using enum MessageSeverity;

	const auto value = std::to_underlying(severity);
	auto flags = VkDebugUtilsMessageSeverityFlagsEXT {};

	if (value & std::to_underlying(error))
	{
		flags |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	}

	if (value & std::to_underlying(warning))
	{
		flags |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
	}

	if (value & std::to_underlying(info))
	{
		flags |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
	}

	if (value & std::to_underlying(verbose))
	{
		flags |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
	}

	return flags;
}

[[nodiscard]] /*static*/ auto Messenger::from_native_severity(
    VkDebugUtilsMessageSeverityFlagsEXT severity
) -> MessageSeverity
{
	using enum MessageSeverity;

	auto flags = std::underlying_type_t<MessageSeverity> {};

	if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
	{
		flags &= std::to_underlying(error);
	}

	if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	{
		flags &= std::to_underlying(warning);
	}

	if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
	{
		flags &= std::to_underlying(info);
	}

	if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
	{
		flags &= std::to_underlying(verbose);
	}

	return static_cast<MessageSeverity>(flags);
}

[[nodiscard]] /*static*/ auto Messenger::to_native_type(MessageType type)
    -> VkDebugUtilsMessageTypeFlagsEXT
{
	using enum MessageType;

	const auto value = std::to_underlying(type);
	auto flags = VkDebugUtilsMessageTypeFlagsEXT {};

	if (value & std::to_underlying(general))
	{
		flags |= VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT;
	}

	if (value & std::to_underlying(validation))
	{
		flags |= VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
	}

	if (value & std::to_underlying(performance))
	{
		flags |= VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	}

	return flags;
}

[[nodiscard]] /* static */ auto Messenger::from_native_type(VkDebugUtilsMessageTypeFlagsEXT type)
    -> MessageType
{
	using enum MessageType;

	auto flags = std::underlying_type_t<MessageType> {};

	if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
	{
		flags |= std::to_underlying(general);
	}

	if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
	{
		flags |= std::to_underlying(validation);
	}

	if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
	{
		flags |= std::to_underlying(general);
	}

	return static_cast<MessageType>(flags);
}

} // namespace lt::renderer::vk
