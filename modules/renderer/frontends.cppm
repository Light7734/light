export module renderer.frontend;

import ecs.entity;
import math.vec2;
import renderer.api;
import memory.scope;

export namespace lt::renderer {

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

} // namespace lt::renderer
