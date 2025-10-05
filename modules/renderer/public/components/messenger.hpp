#pragma once

#include <bitwise/operations.hpp>
#include <any>

namespace lt::renderer {

enum class MessageSeverity : uint8_t
{
	none = 0u,

	verbose = bitwise::bit(0u),
	info = bitwise::bit(1u),
	warning = bitwise::bit(2u),
	error = bitwise::bit(3u),

	all = verbose | info | warning | error,
};

enum class MessageType : uint8_t
{
	none = 0u,
	general = bitwise::bit(0u),
	validation = bitwise::bit(1u),
	performance = bitwise::bit(2u),

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
