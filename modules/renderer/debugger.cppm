export module renderer.vk.debugger;

import preliminary;
import bitwise;
import renderer.vk.instance;
import renderer.vk.api_wrapper;
import logger;

export namespace lt::renderer::vkb {

class Debugger
{
public:
	enum class MessageSeverity : u8
	{
		none = 0u,

		verbose = bitwise::bit(0u),
		info = bitwise::bit(1u),
		warning = bitwise::bit(2u),
		error = bitwise::bit(3u),

		// NOLINTNEXTLINE(hicpp-signed-bitwise)
		all = verbose | info | warning | error,
	};

	enum class MessageType : u8
	{
		none = 0u,
		general = bitwise::bit(0u),
		validation = bitwise::bit(1u),
		performance = bitwise::bit(2u),

		// NOLINTNEXTLINE(hicpp-signed-bitwise)
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

	Debugger(Instance *instance, CreateInfo info);

private:
	static void native_callback(
	    vk::Flags severity,
	    vk::Flags types,
	    const vk::Messenger::MessageData &data,
	    void *user_data
	);

	vk::Messenger m_messenger;

	MessageSeverity m_severities {};

	MessageType m_types {};

	Callback_T m_user_callback;

	std::any m_user_data;
};

} // namespace lt::renderer::vkb

namespace lt::renderer::vkb {

[[nodiscard]] auto to_native_severity(Debugger::MessageSeverity severity) -> vk::Flags
{
	const auto value = std::to_underlying(severity);
	auto flags = vk::Flags {};

	using enum Debugger::MessageSeverity;
	using NativeSeverity = vk::Messenger::SeverityFlagBits;
	if (value & std::to_underlying(error))
	{
		flags |= NativeSeverity::error;
	}

	if (value & std::to_underlying(warning))
	{
		flags |= NativeSeverity::warning;
	}

	if (value & std::to_underlying(info))
	{
		flags |= NativeSeverity::info;
	}

	if (value & std::to_underlying(verbose))
	{
		flags |= NativeSeverity::verbose;
	}

	return flags;
}

[[nodiscard]] /* static */ auto to_native_type(Debugger::MessageType type) -> vk::Flags
{
	const auto value = std::to_underlying(type);
	auto flags = vk::Flags {};

	using enum Debugger::MessageType;
	using NativeType = vk::Messenger::TypeFlagBits;
	if (value & std::to_underlying(general))
	{
		flags |= NativeType::general;
	}

	if (value & std::to_underlying(validation))
	{
		flags |= NativeType::validation;
	}

	if (value & std::to_underlying(performance))
	{
		flags |= NativeType::performance;
	}

	return flags;
}

[[nodiscard]] auto from_native_type(vk::Flags type) -> Debugger::MessageType
{
	auto flags = std::underlying_type_t<Debugger::MessageType> {};

	using enum Debugger::MessageType;
	using NativeType = vk::Messenger::TypeFlagBits;
	if (type & NativeType::general)
	{
		flags |= std::to_underlying(general);
	}

	if (type & NativeType::validation)
	{
		flags |= std::to_underlying(validation);
	}

	if (type & NativeType::performance)
	{
		flags |= std::to_underlying(performance);
	}

	return static_cast<Debugger::MessageType>(flags);
}

[[nodiscard]] auto from_native_severity(vk::Flags severity) -> Debugger::MessageSeverity
{
	auto flags = std::underlying_type_t<Debugger::MessageSeverity> {};

	using enum Debugger::MessageSeverity;
	using NativeSeverity = vk::Messenger::SeverityFlagBits;
	if (severity & NativeSeverity::error)
	{
		flags |= std::to_underlying(error);
	}

	if (severity & NativeSeverity::warning)
	{
		flags |= std::to_underlying(warning);
	}

	if (severity & NativeSeverity::info)
	{
		flags |= std::to_underlying(info);
	}

	if (severity & NativeSeverity::verbose)
	{
		flags |= std::to_underlying(verbose);
	}

	return static_cast<Debugger::MessageSeverity>(flags);
}

void Debugger::native_callback(
    vk::Flags severity,
    vk::Flags types,
    const vk::Messenger::MessageData &data,
    void *user_data
)
{
	try
	{
		ensure(user_data, "Null vulkan_user_data received in messenger callback");

		auto *messenger = std::bit_cast<Debugger *>(user_data);
		messenger->m_user_callback(
		    from_native_severity(severity),
		    from_native_type(types),
		    {
		        .message = data.message,
		    },
		    messenger->m_user_data
		);
	}
	catch (const std::exception &exp)
	{
		log::error("Uncaught exception in messenger callback:");
		log::error("\twhat: {}", exp.what());
	}
}

Debugger::Debugger(Instance *instance, CreateInfo info)
    : m_user_data(std::move(info.user_data))
    , m_user_callback(std::move(info.callback))
    , m_messenger(
          instance->vk(),
          vk::Messenger::CreateInfo {
              .user_callback = &native_callback,
              .user_data = this,
              .enabled_types = to_native_type(info.types),
              .enabled_severities = to_native_severity(info.severities),
          }
      )
{
	ensure(m_user_callback, "Failed to create vkb::Debugger: null callback");
}

} // namespace lt::renderer::vkb
