#pragma once

#include <any>
#include <bitwise/operations.hpp>
#include <memory/scope.hpp>
#include <renderer/frontend/messenger.hpp>

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

struct MessageData
{
	std::string message;
};

using Callback_T = std::function<void(
    MessageSeverity message_severity,
    MessageType message_type,
    MessageData data,
    std::any &user_data
)>;

class MessengerComponent
{
public:
	friend class System;

	struct CreateInfo
	{
		MessageSeverity severities;

		MessageType types;

		Callback_T callback;

		std::any user_data;
	};

	[[nodiscard]] auto get_severities() const -> MessageSeverity
	{
		return m_severities;
	}

	[[nodiscard]] auto get_types() const -> MessageType
	{
		return m_types;
	}

	[[nodiscard]] auto get_callback() const -> const Callback_T &
	{
		return m_callback;
	}

	[[nodiscard]] auto get_user_data() -> std::any &
	{
		return m_user_data;
	}

private:
	MessengerComponent(CreateInfo info)
	    : m_severities(info.severities)
	    , m_types(info.types)
	    , m_callback(std::move(info.callback))
	    , m_user_data(std::move(info.user_data))
	{
	}

	MessageSeverity m_severities;

	MessageType m_types;

	Callback_T m_callback;

	std::any m_user_data;

	memory::Scope<IMessenger> m_implementation;
};

} // namespace lt::renderer
