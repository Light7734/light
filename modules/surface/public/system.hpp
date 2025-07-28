#pragma once

#include <app/system.hpp>
#include <ecs/entity.hpp>
#include <ecs/scene.hpp>
#include <surface/components.hpp>

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

	void on_register() override
	{
	}

	void on_unregister() override
	{
	}

	auto tick() -> bool override;

	void set_title(ecs::Entity surface_entity, std::string_view new_title);

	void set_size(ecs::Entity surface_entity, const math::uvec2 &new_size);

	void set_v_sync(ecs::Entity surface_entity, bool vsync);

	void set_visibility(ecs::Entity surface_entity, bool visible);

	void add_event_listener(ecs::Entity surface_entity, SurfaceComponent::EventCallback callback);

private:
	void on_surface_construct(entt::registry &registry, entt::entity entity);

	void on_surface_update(entt::registry &registry, entt::entity entity);

	void on_surface_destroy(entt::registry &registry, entt::entity entity);

	Ref<ecs::Registry> m_registry;
};


} // namespace lt::surface
