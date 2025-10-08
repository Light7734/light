#pragma once

#include <any>
#include <memory/pointer_types/null_on_move.hpp>
#include <renderer/backend/vk/context/instance.hpp>
#include <renderer/backend/vk/raii/raii.hpp>
#include <renderer/backend/vk/vulkan.hpp>
#include <renderer/components/messenger.hpp>
#include <renderer/frontend/messenger.hpp>

namespace lt::renderer::vk {

class Messenger: public IMessenger
{
public:
	Messenger(IInstance *instance, CreateInfo info);

private:
	static auto native_callback(
	    VkDebugUtilsMessageSeverityFlagBitsEXT severity,
	    VkDebugUtilsMessageTypeFlagsEXT type,
	    const VkDebugUtilsMessengerCallbackDataEXT *callback_data,
	    void *vulkan_user_data
	) -> VkBool32;

	[[nodiscard]] static auto to_native_severity(MessageSeverity severity)
	    -> VkDebugUtilsMessageSeverityFlagsEXT;

	[[nodiscard]] static auto from_native_severity(VkDebugUtilsMessageSeverityFlagsEXT severity)
	    -> MessageSeverity;

	[[nodiscard]] static auto to_native_type(MessageType type) -> VkDebugUtilsMessageTypeFlagsEXT;

	[[nodiscard]] static auto from_native_type(VkDebugUtilsMessageTypeFlagsEXT type) -> MessageType;

	class Instance *m_instance {};

	raii::DebugMessenger m_debug_messenger;

	MessageSeverity m_severities {};

	MessageType m_types {};

	Callback_T m_user_callback;

	std::any m_user_data;
};

} // namespace lt::renderer::vk
