#pragma once

#include <ecs/entity.hpp>
#include <math/vec2.hpp>
#include <memory/scope.hpp>
#include <renderer/api.hpp>

namespace lt::renderer {

class ISurface
{
public:
	[[nodiscard]] static auto create(
	    Api target_api,
	    class IInstance *instance,
	    const ecs::Entity &surface_entity
	) -> memory::Scope<ISurface>;

	ISurface() = default;

	virtual ~ISurface() = default;

	ISurface(ISurface &&) = default;

	ISurface(const ISurface &) = delete;

	auto operator=(ISurface &&) -> ISurface & = default;

	auto operator=(const ISurface &) -> ISurface & = delete;

	[[nodiscard]] virtual auto get_framebuffer_size() const -> math::uvec2 = 0;
};

} // namespace lt::renderer
