export module renderer.frontend;

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

} // namespace lt::renderer
