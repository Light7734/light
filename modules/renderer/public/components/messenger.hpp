#pragma once

#include <any>

namespace lt::renderer {

enum class MessageSeverity : uint8_t
{
	none = 0u,

	verbose = bit(0u),
	info = bit(1u),
	warning = bit(2u),
	error = bit(3u),

	all = verbose | info | warning | error,
};

enum class MessageType : uint8_t
{
	none = 0u,
	general = bit(0u),
	validation = bit(1u),
	performance = bit(2u),

	all = general | validation | performance,
};

struct MessengerCallbackData
{
	std::string message;
};

using Callback_T = std::function<void(
    MessageSeverity message_severity,
    MessageType message_type,
    MessengerCallbackData data,
    std::any user_data
)>;

struct MessengerComponent
{
	MessageSeverity severities;

	MessageType types;

	Callback_T callback;

	std::any user_data;
};

} // namespace lt::renderer
