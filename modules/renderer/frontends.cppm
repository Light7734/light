export module renderer.frontend;
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
	// [[nodiscard]] static auto get(Api target_api) -> IInstance *;
	IInstance() = default;

	virtual ~IInstance() = default;

	IInstance(IInstance &&) = default;

	IInstance(const IInstance &) = delete;

	auto operator=(IInstance &&) -> IInstance & = default;

	auto operator=(const IInstance &) -> IInstance & = delete;
};

class IGpu
{
public:
	IGpu() = default;

	virtual ~IGpu() = default;

	IGpu(IGpu &&) = default;

	IGpu(const IGpu &) = delete;

	auto operator=(IGpu &&) -> IGpu & = default;

	auto operator=(const IGpu &) -> IGpu & = delete;
};

class IDevice
{
public:
	IDevice() = default;

	virtual ~IDevice() = default;

	IDevice(IDevice &&) = default;

	IDevice(const IDevice &) = delete;

	auto operator=(IDevice &&) -> IDevice & = default;

	auto operator=(const IDevice &) -> IDevice & = delete;
};

class ISurface
{
public:
	ISurface() = default;

	virtual ~ISurface() = default;

	ISurface(ISurface &&) = default;

	ISurface(const ISurface &) = delete;

	auto operator=(ISurface &&) -> ISurface & = default;

	auto operator=(const ISurface &) -> ISurface & = delete;

	[[nodiscard]] virtual auto get_framebuffer_size() const -> math::uvec2 = 0;
};

class ISwapchain
{
public:
	ISwapchain() = default;

	virtual ~ISwapchain() = default;

	ISwapchain(ISwapchain &&) = default;

	ISwapchain(const ISwapchain &) = delete;

	auto operator=(ISwapchain &&) -> ISwapchain & = default;

	auto operator=(const ISwapchain &) -> ISwapchain & = delete;
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

	[[nodiscard]] static auto create(
	    Api target_api,
	    class IDevice *device,
	    class IGpu *gpu,
	    const CreateInfo &info
	) -> memory::Scope<IBuffer>;

	IBuffer() = default;

	virtual ~IBuffer() = default;

	IBuffer(IBuffer &&) = default;

	IBuffer(const IBuffer &) = delete;

	auto operator=(IBuffer &&) -> IBuffer & = default;

	auto operator=(const IBuffer &) -> IBuffer & = delete;

	[[nodiscard]] virtual auto map() -> std::span<std::byte> = 0;

	virtual void unmap() = 0;

	[[nodiscard]] virtual auto get_size() const -> std::size_t = 0;

private:
};

class IPass
{
public:
	[[nodiscard]] static auto create(
	    lt::renderer::Api target_api,
	    class IDevice *device,
	    const class lt::assets::ShaderAsset &vertex_shader,
	    const class lt::assets::ShaderAsset &fragment_shader
	) -> memory::Scope<IPass>;

	IPass() = default;

	virtual ~IPass() = default;

	IPass(IPass &&) = default;

	IPass(const IPass &) = delete;

	auto operator=(IPass &&) -> IPass & = default;

	auto operator=(const IPass &) -> IPass & = delete;
};

// class IRenderer
// {
// public:
// 	static constexpr auto frames_in_flight_upper_limit = 5u;
//
// 	static constexpr auto frames_in_flight_lower_limit = 1u;
//
// 	enum class Result : uint8_t
// 	{
// 		success = 0,
// 		invalid_swapchain,
// 		error,
// 	};
//
// 	[[nodiscard]] static auto create(
// 	    Api target_api,
// 	    class IGpu *gpu,
// 	    class IDevice *device,
// 	    class ISwapchain *swapchain,
// 	    uint32_t max_frames_in_flight
// 	) -> memory::Scope<IRenderer>;
//
// 	IRenderer() = default;
//
// 	virtual ~IRenderer() = default;
//
// 	IRenderer(IRenderer &&) = default;
//
// 	IRenderer(const IRenderer &) = delete;
//
// 	auto operator=(IRenderer &&) -> IRenderer & = default;
//
// 	auto operator=(const IRenderer &) -> IRenderer & = delete;
//
// 	virtual auto frame(uint32_t frame_idx, std::function<void()> submit_scene) -> Result = 0;
//
// 	virtual void replace_swapchain(class ISwapchain *swapchain) = 0;
//
// 	virtual void set_frame_constants(FrameConstants constants) = 0;
//
// 	virtual void submit_sprite(
// 	    const components::Sprite &sprite,
// 	    const math::components::Transform &transform
// 	) = 0;
// };


// class IDebugger
// {
// public:
// 	enum class MessageSeverity : std::uint8_t
// 	{
// 		none = 0u,
//
// 		verbose = bitwise::bit(0u),
// 		info = bitwise::bit(1u),
// 		warning = bitwise::bit(2u),
// 		error = bitwise::bit(3u),
//
// 		all = verbose | info | warning | error,
// 	};
//
// 	enum class MessageType : std::uint8_t
// 	{
// 		none = 0u,
// 		general = bitwise::bit(0u),
// 		validation = bitwise::bit(1u),
// 		performance = bitwise::bit(2u),
//
// 		all = general | validation | performance,
// 	};
//
// 	struct MessageData
// 	{
// 		std::string message;
// 	};
//
// 	using Callback_T = std::function<void(
// 	    MessageSeverity message_severity,
// 	    MessageType message_type,
// 	    const MessageData &data,
// 	    std::any &user_data
// 	)>;
//
// 	struct CreateInfo
// 	{
// 		MessageSeverity severities;
//
// 		MessageType types;
//
// 		Callback_T callback;
//
// 		std::any user_data;
// 	};
//
// 	[[nodiscard]] static auto create(Api target_api, class IInstance *instance, CreateInfo info)
// 	    -> memory::Scope<IDebugger>;
//
// 	IDebugger() = default;
//
// 	virtual ~IDebugger() = default;
//
// 	IDebugger(IDebugger &&) = default;
//
// 	IDebugger(const IDebugger &) = delete;
//
// 	auto operator=(IDebugger &&) -> IDebugger & = default;
//
// 	auto operator=(const IDebugger &) -> IDebugger & = delete;
// };

} // namespace lt::renderer
