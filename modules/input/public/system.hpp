#pragma once

#include <app/system.hpp>
#include <ecs/registry.hpp>
#include <surface/components.hpp>
#include <surface/events/keyboard.hpp>
#include <surface/events/mouse.hpp>

namespace lt::input {

class System: public app::ISystem
{
public:
	System(Ref<ecs::Registry> registry);

	auto tick() -> bool override;

	void on_register() override;

	void on_unregister() override;

private:
	void handle_event(const surface::SurfaceComponent::Event &event);

	void on_surface_lost_focus();

	void on_key_press(const lt::surface::KeyPressedEvent &event);

	void on_key_release(const lt::surface::KeyReleasedEvent &event);

	void on_pointer_move(const lt::surface::MouseMovedEvent &event);

	void on_button_press(const lt::surface::ButtonPressedEvent &event);

	void on_button_release(const lt::surface::ButtonReleasedEvent &event);

	Ref<ecs::Registry> m_registry;

	std::array<bool, 512> m_keys {};

	std::array<bool, 512> m_buttons {};

	math::vec2 m_pointer_position;
};


} // namespace lt::input
