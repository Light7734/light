export module renderer.frontend;
import renderer.data;
import renderer.components;
import bitwise;
import math.components;
import assets.shader;
import ecs.entity;
import math.vec2;
import memory.scope;
import std;

export namespace lt::renderer {

enum class Api : std::uint8_t
{
	none = 0u,

	vulkan,
	direct_x,
	metal,
};

class IInstance
{
public:
	IInstance() = default;

	virtual ~IInstance() = default;
};

class IGpu
{
public:
	IGpu() = default;

	virtual ~IGpu() = default;
};

class IDevice
{
public:
	IDevice() = default;

	virtual ~IDevice() = default;
};

class ISurface
{
public:
	ISurface() = default;

	virtual ~ISurface() = default;

	[[nodiscard]] virtual auto get_framebuffer_size() const -> math::uvec2 = 0;
};

class ISwapchain
{
public:
	ISwapchain() = default;

	virtual ~ISwapchain() = default;
};

class IBuffer
{
public:
	enum class Usage : std::uint8_t
	{
		vertex,

		index,

		storage,

		staging,
	};

	struct CreateInfo
	{
		Usage usage;

		std::size_t size;

		std::string debug_name;
	};

	struct CopyInfo
	{
		std::size_t offset;

		std::size_t size;
	};

	IBuffer() = default;

	virtual ~IBuffer() = default;

	[[nodiscard]] virtual auto map() -> std::span<std::byte> = 0;

	virtual void unmap() = 0;

	[[nodiscard]] virtual auto get_size() const -> std::size_t = 0;

private:
};

class IPass
{
public:
	IPass() = default;

	virtual ~IPass() = default;
};

class IRenderer
{
public:
	static constexpr auto frames_in_flight_upper_limit = 5u;

	static constexpr auto frames_in_flight_lower_limit = 1u;

	enum class Result : std::uint8_t
	{
		success = 0,
		invalid_swapchain,
		error,
	};

	IRenderer() = default;

	virtual ~IRenderer() = default;

	virtual auto frame(std::uint32_t frame_idx, std::function<void()> submit_scene) -> Result = 0;

	virtual void replace_swapchain(class ISwapchain *swapchain) = 0;

	virtual void set_frame_constants(FrameConstants constants) = 0;

	virtual void submit_sprite(
	    const components::Sprite &sprite,
	    const math::components::Transform &transform
	) = 0;
};

class IDebugger
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

	IDebugger() = default;

	virtual ~IDebugger() = default;
};

} // namespace lt::renderer
