#pragma once

#include <app/system.hpp>
#include <ecs/scene.hpp>

namespace lt::surface {

class System: public app::ISystem
{
public:
	[[nodiscard]] System(Ref<ecs::Registry> registry);

	~System() override;

	System(System &&) = default;

	System(const System &) = delete;

	auto operator=(System &&) -> System & = default;

	auto operator=(const System &) -> System & = delete;

	void on_register() override;

	void on_unregister() override;

	auto tick() -> bool override;

private:
	void on_surface_construct(entt::registry &registry, entt::entity entity);

	void on_surface_update(entt::registry &registry, entt::entity entity);

	void on_surface_destroy(entt::registry &registry, entt::entity entity);

	void handle_requests(struct SurfaceComponent &surface);

	void handle_events(struct SurfaceComponent &surface);

	void modify_title(struct SurfaceComponent &surface, const struct ModifyTitleRequest &request);

	void modify_resolution(
	    struct SurfaceComponent &surface,
	    const struct ModifyResolutionRequest &request
	);

	void modify_position(
	    struct SurfaceComponent &surface,
	    const struct ModifyPositionRequest &request
	);

	void modify_visiblity(
	    struct SurfaceComponent &surface,
	    const struct ModifyVisibilityRequest &request
	);

	void modify_position(ecs::Entity surface_entity, const math::ivec2 &new_size);

	void modify_position(ecs::Entity surface_entity, const math::uvec2 &new_size);

	void set_visibility(ecs::Entity surface_entity, bool visible);

	Ref<ecs::Registry> m_registry;
};

} // namespace lt::surface
