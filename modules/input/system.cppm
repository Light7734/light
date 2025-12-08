export module input.system;
export import :components;
import logger;
import app.system;
import debug.assertions;
import ecs.registry;
import memory.reference;
import surface.system;
import surface.events;
import math.vec2;
import std;

namespace lt::input {

export class System: public app::ISystem
{
public:
	System(memory::Ref<ecs::Registry> registry);

	void tick(app::TickInfo tick) override;

	void on_register() override;

	void on_unregister() override;

	[[nodiscard]] auto get_last_tick_result() const -> const app::TickResult & override
	{
		return m_last_tick_result;
	}

private:
	void handle_event(const surface::SurfaceComponent::Event &event);

	void on_surface_lost_focus();

	void on_key_press(const lt::surface::KeyPressedEvent &event);

	void on_key_release(const lt::surface::KeyReleasedEvent &event);

	void on_pointer_move(const lt::surface::MouseMovedEvent &event);

	void on_button_press(const lt::surface::ButtonPressedEvent &event);

	void on_button_release(const lt::surface::ButtonReleasedEvent &event);

	memory::Ref<ecs::Registry> m_registry;

	std::array<bool, 512> m_keys {};

	std::array<bool, 512> m_buttons {};

	math::vec2 m_pointer_position;

	app::TickResult m_last_tick_result {};
};


} // namespace lt::input


module :private;
namespace lt::input {

template<class... Ts>
struct overloads: Ts...
{
	using Ts::operator()...;
};

System::System(memory::Ref<ecs::Registry> registry): m_registry(std::move(registry))
{
	debug::ensure(m_registry, "Failed to initialize input system: null registry");
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
			auto code = std::to_underlying(action.trigger.mapped_keycode);
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
	if (std::to_underlying(event.get_key()) > m_keys.size())
	{
		log::debug("Key code larger than key container size, implement platform-dependant "
		           "key-code-mapping!");

		return;
	}

	m_keys[std::to_underlying(event.get_key())] = true;
}

void System::on_key_release(const lt::surface::KeyReleasedEvent &event)
{
	if (std::to_underlying(event.get_key()) > m_keys.size())
	{
		log::debug("Key code larger than key container size, implement platform-dependant "
		           "key-code-mapping!");

		return;
	}

	m_keys[std::to_underlying(event.get_key())] = false;
}

void System::on_pointer_move(const lt::surface::MouseMovedEvent &event)
{
	m_pointer_position = event.get_position();
}

void System::on_button_press(const lt::surface::ButtonPressedEvent &event)
{
	m_buttons[std::to_underlying(event.get_button())] = true;
}

void System::on_button_release(const lt::surface::ButtonReleasedEvent &event)
{
	m_buttons[std::to_underlying(event.get_button())] = false;
}

} // namespace lt::input
