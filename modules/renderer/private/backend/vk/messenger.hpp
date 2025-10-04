#pragma once

#include <any>
#include <memory/pointer_types/null_on_move.hpp>
#include <renderer/backend/vk/context/instance.hpp>
#include <renderer/backend/vk/vulkan.hpp>
#include <renderer/components/messenger.hpp>
#include <renderer/frontend/messenger.hpp>

namespace lt::renderer::vk {

class Messenger: public IMessenger
{
public:
	Messenger(IInstance *instance, ecs::Entity entity);

	~Messenger() override;

	Messenger(Messenger &&) = default;

	Messenger(const Messenger &) = delete;

	auto operator=(Messenger &&) -> Messenger & = default;

	auto operator=(const Messenger &) const -> Messenger & = delete;


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

	memory::NullOnMove<class Instance *> m_instance {};

	ecs::Entity m_entity;

	VkDebugUtilsMessengerEXT m_debug_messenger = VK_NULL_HANDLE;

	MessageSeverity m_severities {};

	MessageType m_types {};
};

} // namespace lt::renderer::vk
