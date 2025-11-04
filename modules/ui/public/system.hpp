#pragma once

#include <app/system.hpp>
#include <ecs/registry.hpp>
#include <input/components.hpp>
#include <input/system.hpp>
#include <memory/reference.hpp>

namespace lt::ui {

struct ButtonComponent
{
	std::function<void()> on_activate;

	std::function<void(bool)> on_hover;
};

struct TransformComponent
{
	float x, y;

	float w, h;
};

class System: public app::ISystem
{
public:
	System(memory::Ref<ecs::Registry> registry): m_registry(std::move(registry))
	{
		m_registry->each<ButtonComponent, TransformComponent>(
		    [](auto id, auto &button, auto &transform) {
			    // trigger `button`'s callbacksbased on input's state...
		    }
		);
	}

private:
	memory::Ref<ecs::Registry> m_registry;

	input::InputAction button_press_action;
};

} // namespace lt::ui
