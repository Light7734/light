export module renderer.frontend;

import preliminary;
import renderer.data;
import renderer.components;
import bitwise;
import math.components;
import assets.shader;
import ecs.entity;
import math.vec2;

export namespace lt::renderer {

/** The target rendering backend.
 *
 * Vulkan is available universally, version 1.4 is used.
 * DirextX is available only on Windows, version 12 is used.
 * Metal is available only on MacOS, currently unsupported.
 */
enum class Api : u8
{
	none = 0u,

	vulkan,
	direct_x,
	metal,
};

/** An instance of an implementatoin of the target graphics API.
 *
 * @note NO_COPY NO_MOVE
 */
class IInstance
{
public:
	IInstance() = default;

	IInstance(IInstance &&) = delete;

	IInstance(const IInstance &) = delete;

	auto operator=(IInstance &&) -> IInstance & = delete;

	auto operator=(const IInstance &) -> IInstance & = delete;

	virtual ~IInstance() = default;
};

/** A physical device capable of performing rendering operations.
 *
 * @note NO_COPY MOVABLE
 */
class IGpu
{
public:
	IGpu() = default;

	IGpu(IGpu &&) = default;

	IGpu(const IGpu &) = delete;

	auto operator=(IGpu &&) -> IGpu & = default;

	auto operator=(const IGpu &) -> IGpu & = delete;

	virtual ~IGpu() = default;
};

/** Performs majority of the logical operatoins using a physical device.
 *
 * @note NO_COPY MOVABLE
 */
class IDevice
{
public:
	IDevice() = default;

	IDevice(IDevice &&) = default;

	IDevice(const IDevice &) = delete;

	auto operator=(IDevice &&) -> IDevice & = default;

	auto operator=(const IDevice &) -> IDevice & = delete;

	virtual ~IDevice() = default;

	virtual void wait_idle() = 0;
};

/** Somewhere to put our rendered pixels on.
 *
 * @note NO_COPY MOVABLE
 */
class ISurface
{
public:
	ISurface() = default;

	ISurface(ISurface &&) = default;

	ISurface(const ISurface &) = delete;

	auto operator=(ISurface &&) -> ISurface & = default;

	auto operator=(const ISurface &) -> ISurface & = delete;

	virtual ~ISurface() = default;

	[[nodiscard]] virtual auto get_framebuffer_size() const -> math::vec2_u32 = 0;
};

/** A small series of renderable images to be represented to a surface, by swapping the old image
 * with a new rendered image.
 *
 * @note NO_COPY MOVABLE
 *
 * @warn Does not guarantee double buffering
 */
class ISwapchain
{
public:
	ISwapchain() = default;

	ISwapchain(ISwapchain &&) = default;

	ISwapchain(const ISwapchain &) = delete;

	auto operator=(ISwapchain &&) -> ISwapchain & = default;

	auto operator=(const ISwapchain &) -> ISwapchain & = delete;

	virtual ~ISwapchain() = default;
};

/** A buffer of arbitrary rendering-related data.
 *
 * @note NO_COPY MOVABLE
 */
class IBuffer
{
public:
	IBuffer() = default;

	IBuffer(IBuffer &&) = default;

	IBuffer(const IBuffer &) = delete;

	auto operator=(IBuffer &&) -> IBuffer & = default;

	auto operator=(const IBuffer &) -> IBuffer & = delete;

	virtual ~IBuffer() = default;

	[[nodiscard]] virtual auto map() -> std::span<byte> = 0;

	virtual void unmap() = 0;

	[[nodiscard]] virtual auto get_size() const -> size_t = 0;

private:
};

/** Holds the state required for the IRenderer class to invoke draw calls.
 * eg, pipelines, pipeline states, descriptors, layouts, etc.
 *
 * @note NO_COPY MOVABLE
 */
class IPass
{
public:
	IPass() = default;

	IPass(IPass &&) = default;

	IPass(const IPass &) = delete;

	auto operator=(IPass &&) -> IPass & = default;

	auto operator=(const IPass &) -> IPass & = delete;

	virtual ~IPass() = default;
};

/** Responsible for drawing a frame using renderer components.
 *
 * @ref: components::Sprite
 *
 * @note NO_COPY MOVABLE
 */
class IRenderer
{
public:
	static constexpr auto frames_in_flight_upper_limit = 5u;

	static constexpr auto frames_in_flight_lower_limit = 1u;

	IRenderer() = default;

	IRenderer(IRenderer &&) = default;

	IRenderer(const IRenderer &) = delete;

	auto operator=(IRenderer &&) -> IRenderer & = default;

	auto operator=(const IRenderer &) -> IRenderer & = delete;

	virtual ~IRenderer() = default;

	virtual auto frame(u32 frame_idx, std::function<void()> submit_scene) -> Result = 0;

	virtual void replace_swapchain(class ISwapchain *swapchain) = 0;

	virtual void set_frame_constants(FrameConstants constants) = 0;

	virtual void submit_sprite(
	    const components::Sprite &sprite,
	    const math::components::Transform &transform
	) = 0;
};

/** Utility for printing diagnostic messages from the backend debugging tools.
 * eg, validation layers in Vulkan.
 *
 * @note NO_COPY MOVABLE
 */
class IDebugger
{
public:
	IDebugger() = default;

	IDebugger(IDebugger &&) = default;

	IDebugger(const IDebugger &) = delete;

	auto operator=(IDebugger &&) -> IDebugger & = default;

	auto operator=(const IDebugger &) -> IDebugger & = delete;

	virtual ~IDebugger() = default;
};

} // namespace lt::renderer
