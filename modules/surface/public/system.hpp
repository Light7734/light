#pragma once

#include <app/system.hpp>
#include <ecs/registry.hpp>
#include <math/vec2.hpp>
#include <memory/reference.hpp>
#include <surface/components.hpp>

namespace lt::surface {

class System: public app::ISystem
{
public:
	[[nodiscard]] System(memory::Ref<ecs::Registry> registry);

	~System() override;

	System(System &&) = default;

	System(const System &) = delete;

	auto operator=(System &&) -> System & = default;

	auto operator=(const System &) -> System & = delete;

	void on_register() override;

	void on_unregister() override;

	auto create_component(ecs::EntityId entity, SurfaceComponent::CreateInfo info)
	    -> std::optional<SurfaceComponent *>;

	void tick(app::TickInfo tick) override;

	[[nodiscard]] auto get_last_tick_result() const -> const app::TickResult & override
	{
		return m_last_tick_result;
	}

private:
	void on_surface_destruct(ecs::Registry &registry, ecs::EntityId entity);

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

	void modify_position(ecs::EntityId surface_entity, const math::ivec2 &new_size);

	void modify_position(ecs::EntityId surface_entity, const math::uvec2 &new_size);

	void set_visibility(ecs::EntityId surface_entity, bool visible);

	memory::Ref<ecs::Registry> m_registry;

	app::TickResult m_last_tick_result;
};

} // namespace lt::surface
