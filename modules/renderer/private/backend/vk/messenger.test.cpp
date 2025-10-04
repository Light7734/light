#include <renderer/backend/vk/context/surface.hpp>
#include <renderer/backend/vk/debug/messenger.hpp>
#include <renderer/backend/vk/test_utils.hpp>
#include <surface/components.hpp>
#include <surface/system.hpp>
#include <test/expects.hpp>
#include <test/test.hpp>

using namespace lt;
using renderer::vk::Messenger;
using renderer::vk::Surface;
using enum Messenger::Severity;
using enum Messenger::Type;

void noop_callback(
    Messenger::Severity message_severity,
    Messenger::Type message_type,
    Messenger::CallbackData_T vulkan_data,
    void *user_data
)
{
}

Suite raii = "messenger_raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		Messenger(
		    Messenger::CreateInfo {
		        .severity = all_severity,
		        .type = all_type,
		        .callback = &noop_callback,
		    }
		);
	};

	Case { "unhappy path throws" } = [] {
		expect_throw([] {
			Messenger(
			    Messenger::CreateInfo {
			        .severity = all_severity,
			        .type = all_type,
			        .callback = {},
			    }
			);
		});

		expect_throw([] {
			Messenger(
			    Messenger::CreateInfo {
			        .severity = {},
			        .type = all_type,
			        .callback = &noop_callback,
			    }
			);
		});

		expect_throw([] {
			Messenger(
			    Messenger::CreateInfo {
			        .severity = all_severity,
			        .type = {},
			        .callback = &noop_callback,
			    }
			);
		});
	};
};

// NOLINTNEXTLINE(cppcoreguidelines-interfaces-global-init)
Suite callback = "messenger_callback"_suite = [] {
	Case { "callback gets called with correct arguments" } = [] {
		auto total_messages = 0u;
		auto first_message_is_severity = false;
		auto second_message_is_type = false;
		auto third_message_is_user_callback = false;
		auto all_messages_are_error = true;
		auto all_messages_are_validation = true;
		auto user_data_is_always_69 = true;

		auto callback = [&](Messenger::Severity message_severity,
		                    Messenger::Type message_type,
		                    Messenger::CallbackData_T vulkan_data,
		                    void *user_data) {
			++total_messages;
			auto message = std::string_view { vulkan_data->pMessage };

			// NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast)
			user_data_is_always_69 = user_data_is_always_69 && *(size_t *)user_data == 69u;

			all_messages_are_validation = all_messages_are_validation && message_type == validation;
			all_messages_are_error = all_messages_are_error && message_severity == error;

			if (total_messages == 1)
			{
				first_message_is_severity = message.starts_with(
				    "vkCreateDebugUtilsMessengerEXT(): pCreateInfo->messageSeverity is zero."
				);
				return;
			}


			if (total_messages == 2)
			{
				second_message_is_type = message.starts_with(
				    "vkCreateDebugUtilsMessengerEXT(): pCreateInfo->messageType is zero."
				);
				return;
			}

			if (total_messages == 3)
			{
				third_message_is_user_callback = message.starts_with(
				    "vkCreateDebugUtilsMessengerEXT(): pCreateInfo->pfnUserCallback is NULL."
				);
				return;
			}
		};

		auto user_data = size_t { 69 };
		auto messenger = Messenger(
		    Messenger::CreateInfo {
		        .severity = all_severity,
		        .type = all_type,
		        .callback = callback,
		        .user_data = &user_data,
		    }
		);

		{
			auto *messenger = VkDebugUtilsMessengerEXT {};
			auto info = VkDebugUtilsMessengerCreateInfoEXT {
				.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
			};
			renderer::vk::vk_create_debug_messenger(
			    renderer::vk::Instance::get(),
			    &info,
			    nullptr,
			    &messenger
			);
		}

		expect_eq(total_messages, 3u);
		expect_true(first_message_is_severity);
		expect_true(second_message_is_type);
		expect_true(third_message_is_user_callback);
		expect_true(all_messages_are_error);
		expect_true(all_messages_are_validation);
		expect_true(user_data_is_always_69);
	};
};
