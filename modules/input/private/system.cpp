#include <input/components.hpp>
#include <input/system.hpp>
#include <memory/reference.hpp>

namespace lt::input {

template<class... Ts>
struct overloads: Ts...
{
	using Ts::operator()...;
};

System::System(memory::Ref<ecs::Registry> registry): m_registry(std::move(registry))
{
	ensure(m_registry, "Failed to initialize input system: null registry");
}

void System::tick(app::TickInfo tick)
{
	for (auto &[entity, surface] : m_registry->view<surface::SurfaceComponent>())
	{
		for (const auto &event : surface.peek_events())
		{
			handle_event(event);
		}
	}

	for (auto &[entity, input] : m_registry->view<InputComponent>())
	{
		// TODO(Light): instead of iterating over all actions each frame,
		// make a list of "dirty" actions to reset
		// and a surface_input->input_action mapping to get to action through input
		// instead of brute-force checking all of them.
		for (auto &action : input.m_actions)
		{
			auto code = action.trigger.mapped_keycode;
			if (code < m_keys.size() && m_keys[code])
			{
				if (action.state == InputAction::State::triggered)
				{
					action.state = InputAction::State::active;
				}
				else if (action.state == InputAction::State::inactive)
				{
					action.state = InputAction::State::triggered;
				}
			}
			else
			{
				action.state = InputAction::State::inactive;
			}
		}
	}

	const auto now = std::chrono::steady_clock::now();
	m_last_tick_result = app::TickResult {
		.info = tick,
		.duration = now - tick.start_time,
		.end_time = now,
	};
}

void System::on_register()
{
}

void System::on_unregister()
{
}

void System::handle_event(const surface::SurfaceComponent::Event &event)
{
	const auto visitor = overloads {
		[this](const surface::ClosedEvent &) { on_surface_lost_focus(); },
		[this](const surface::LostFocusEvent &) { on_surface_lost_focus(); },
		[this](const surface::KeyPressedEvent &event) { on_key_press(event); },
		[this](const surface::KeyReleasedEvent &event) { on_key_release(event); },
		[this](const surface::MouseMovedEvent &event) { on_pointer_move(event); },
		[this](const surface::ButtonPressedEvent &event) { on_button_press(event); },
		[this](const surface::ButtonReleasedEvent &event) { on_button_release(event); },
		[this](auto) {},
	};

	std::visit(visitor, event);
}

void System::on_surface_lost_focus()
{
	for (auto &key : m_keys)
	{
		key = false;
	}

	for (auto &button : m_buttons)
	{
		button = false;
	}
}

void System::on_key_press(const lt::surface::KeyPressedEvent &event)
{
	if (event.get_key() > m_keys.size())
	{
		log_dbg(
		    "Key code larger than key container size, implement platform-dependant "
		    "key-code-mapping!"
		);

		return;
	}

	m_keys[event.get_key()] = true;
}

void System::on_key_release(const lt::surface::KeyReleasedEvent &event)
{
	if (event.get_key() > m_keys.size())
	{
		log_dbg(
		    "Key code larger than key container size, implement platform-dependant "
		    "key-code-mapping!"
		);

		return;
	}

	m_keys[event.get_key()] = false;
}

void System::on_pointer_move(const lt::surface::MouseMovedEvent &event)
{
	m_pointer_position = event.get_position();
}

void System::on_button_press(const lt::surface::ButtonPressedEvent &event)
{
	m_buttons[event.get_button()] = true;
}

void System::on_button_release(const lt::surface::ButtonReleasedEvent &event)
{
	m_buttons[event.get_button()] = false;
}

} // namespace lt::input
