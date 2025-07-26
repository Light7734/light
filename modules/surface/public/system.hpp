#pragma once

#include <app/system.hpp>
#include <ecs/entity.hpp>
#include <ecs/scene.hpp>
#include <surface/components.hpp>
#include <surface/events/keyboard.hpp>
#include <surface/events/mouse.hpp>
#include <surface/events/surface.hpp>

namespace lt::surface {

class System: public app::ISystem
{
public:
	using Event = std::variant<
	    // surface events
	    ClosedEvent,
	    MovedEvent,
	    ResizedEvent,
	    LostFocusEvent,
	    GainFocusEvent,

	    // keyboard events
	    KeyPressedEvent,
	    KeyRepeatEvent,
	    KeyReleasedEvent,
	    KeySetCharEvent,

	    // mouse events
	    MouseMovedEvent,
	    WheelScrolledEvent,
	    ButtonPressedEvent,
	    ButtonReleasedEvent>;

	using EventCallback = std::function<bool(const Event &)>;

	System(Ref<ecs::Registry> registry);

	~System() override;

	System(System &&) = default;

	System(const System &) = delete;

	auto operator=(System &&) -> System & = default;

	auto operator=(const System &) -> System & = delete;

	void init() override
	{
	}

	auto tick() -> bool override;

	void set_title(ecs::Entity surface_entity, std::string_view new_title);

	void set_size(ecs::Entity surface_entity, const math::uvec2 &new_size);

	void set_v_sync(ecs::Entity surface_entity, bool vsync);

	void set_visibility(ecs::Entity surface_entity, bool visible);

	void add_event_listener(EventCallback callback)
	{
		m_event_callbacks.emplace_back(std::move(callback));
	}

private:
	void on_surface_construct(entt::registry &registry, entt::entity entity);

	void on_surface_destroy(entt::registry &registry, entt::entity entity);

	Ref<ecs::Registry> m_registry;

	std::vector<EventCallback> m_event_callbacks;
};


} // namespace lt::surface
