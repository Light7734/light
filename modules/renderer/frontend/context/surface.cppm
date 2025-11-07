export module renderer.frontend.surface;
import ecs.entity;
import math.vec2;
import renderer.api;
import memory.scope;

namespace lt::renderer {

export class ISurface
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
