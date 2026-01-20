export module renderer.vk.debugger;

import preliminary;
import renderer.vk.instance;
import renderer.frontend;
import renderer.vk.api_wrapper;
import memory.null_on_move;
import debug.assertions;
import logger;

export namespace lt::renderer::vkb {

class Debugger: public IDebugger
{
public:
	Debugger(IInstance *instance, CreateInfo info);

private:
	static void native_callback(
	    vk::Flags severity,
	    vk::Flags types,
	    vk::Messenger::MessageData data,
	    void *user_data
	);

	vk::Messenger m_messenger;

	MessageSeverity m_severities {};

	MessageType m_types {};

	Callback_T m_user_callback;

	std::any m_user_data;
};

} // namespace lt::renderer::vkb

module :private;
namespace lt::renderer::vkb {

[[nodiscard]] auto to_native_severity(IDebugger::MessageSeverity severity) -> vk::Flags
{
	const auto value = std::to_underlying(severity);
	auto flags = vk::Flags {};

	using enum IDebugger::MessageSeverity;
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

[[nodiscard]] /* static */ auto to_native_type(IDebugger::MessageType type) -> vk::Flags
{
	const auto value = std::to_underlying(type);
	auto flags = vk::Flags {};

	using enum IDebugger::MessageType;
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

[[nodiscard]] auto from_native_type(vk::Flags type) -> IDebugger::MessageType
{
	auto flags = std::underlying_type_t<IDebugger::MessageType> {};

	using enum IDebugger::MessageType;
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

	return static_cast<IDebugger::MessageType>(flags);
}

[[nodiscard]] auto from_native_severity(vk::Flags severity) -> IDebugger::MessageSeverity
{
	auto flags = std::underlying_type_t<IDebugger::MessageSeverity> {};

	using enum IDebugger::MessageSeverity;
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

	return static_cast<IDebugger::MessageSeverity>(flags);
}

void Debugger::native_callback(
    vk::Flags severity,
    vk::Flags types,
    vk::Messenger::MessageData data,
    void *user_data
)
{
	try
	{
		debug::ensure(user_data, "Null vulkan_user_data received in messenger callback");

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

Debugger::Debugger(IInstance *instance, CreateInfo info)
    : m_user_data(std::move(info.user_data))
    , m_user_callback(std::move(info.callback))
    , m_messenger(
          static_cast<Instance *>(instance)->vk(),
          vk::Messenger::CreateInfo {
              .user_callback = &native_callback,
              .user_data = this,
              .enabled_types = to_native_type(info.types),
              .enabled_severities = to_native_severity(info.severities),
          }
      )
{
}

} // namespace lt::renderer::vkb
