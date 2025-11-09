export module renderer.frontend;
import debug.assertions;
import memory.scope;
import bitwise;
import std;

namespace lt::renderer {

export class IMessenger
{
public:
	enum class MessageSeverity : std::uint8_t
	{
		none = 0u,

		verbose = bitwise::bit(0u),
		info = bitwise::bit(1u),
		warning = bitwise::bit(2u),
		error = bitwise::bit(3u),

		all = verbose | info | warning | error,
	};

	enum class MessageType : std::uint8_t
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

module :private;
using namespace lt::renderer;

import renderer.backends.vk.messenger;

[[nodiscard]] /* static */ auto IMessenger::create(
    Api target_api,
    IInstance *instance,
    CreateInfo info
) -> memory::Scope<IMessenger>
{
	debug::ensure(
	    info.severities != MessageSeverity::none,
	    "Failed to create vk::Messenger: severities == none"
	);

	debug::ensure(info.types != MessageType::none, "Failed to create vk::Messenger: types == none");

	debug::ensure(info.callback, "Failed to create vk::Messenger: null callback");

	switch (target_api)
	{
	case Api::vulkan: return memory::create_scope<vk::Messenger>(instance, std::move(info));
	case Api::none:
	case Api::metal:
	case Api::direct_x: throw std::runtime_error { "Invalid API" };
	}
}
