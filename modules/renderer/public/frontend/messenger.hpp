#pragma once

#include <bitwise/operations.hpp>
#include <ecs/entity.hpp>
#include <memory/scope.hpp>
#include <renderer/api.hpp>

namespace lt::renderer {


class IMessenger
{
public:
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
	    const MessageData &data,
	    std::any &user_data
	)>;

	struct CreateInfo
	{
		MessageSeverity severities;

		MessageType types;

		Callback_T callback;

		std::any user_data;
	};

	[[nodiscard]] static auto create(Api target_api, class IInstance *instance, CreateInfo info)
	    -> memory::Scope<IMessenger>;

	IMessenger() = default;

	virtual ~IMessenger() = default;

	IMessenger(IMessenger &&) = default;

	IMessenger(const IMessenger &) = delete;

	auto operator=(IMessenger &&) -> IMessenger & = default;

	auto operator=(const IMessenger &) -> IMessenger & = delete;
};

} // namespace lt::renderer
