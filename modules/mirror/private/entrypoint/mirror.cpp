#include <X11/keysym.h>
#include <app/application.hpp>
#include <app/entrypoint.hpp>
#include <app/system.hpp>
#include <ecs/entity.hpp>
#include <input/components.hpp>
#include <input/system.hpp>
#include <math/vec2.hpp>
#include <memory/reference.hpp>
#include <memory/scope.hpp>
#include <renderer/components/messenger.hpp>
#include <renderer/system.hpp>
#include <surface/events/keyboard.hpp>
#include <surface/events/surface.hpp>
#include <surface/system.hpp>
#include <time/timer.hpp>

namespace lt {

void renderer_callback(
    renderer::MessageSeverity message_severity,
    renderer::MessageType message_type,
    renderer::MessageData data,
    std::any &user_data
)
{
	log_dbg("RENDERER CALLBACK: {}", data.message);
}

class MirrorSystem: public lt::app::ISystem
{
public:
	MirrorSystem(
	    memory::Ref<ecs::Registry> registry,
	    lt::input::InputAction::Key quit_action_key,
	    std::array<lt::input::InputAction::Key, 4> debug_action_keys
	)
	    : m_registry(std::move(registry))
	    , m_quit_action_key(quit_action_key)
	    , m_debug_action_keys(debug_action_keys)
	{
		using Surface = lt::surface::SurfaceComponent;


		using Input = lt::input::InputComponent;

		for (auto &[entity, surface, input] : m_registry->view<Surface, Input>())
		{
		}
	}

	void tick(app::TickInfo tick) override
	{
		using Surface = lt::surface::SurfaceComponent;
		using Input = lt::input::InputComponent;

		std::this_thread::sleep_for(std::chrono::milliseconds { 10 });
		auto should_quit = false;
		for (auto &[entity, surface, input] : m_registry->view<Surface, Input>())
		{
			using State = lt::input::InputAction::State;
			const auto &[x, y] = surface.get_position();
			const auto &[width, height] = surface.get_resolution();

			if (input.get_action(m_quit_action_key).state == State::active)
			{
				should_quit = true;
			}
			if (input.get_action(m_debug_action_keys[0]).state == State::active)
			{
				surface.push_request(surface::ModifyPositionRequest({ x + 5, y + 5 }));
			}

			if (input.get_action(m_debug_action_keys[1]).state == State::active)
			{
				surface.push_request(surface::ModifyPositionRequest({ x - 5, y - 5 }));
			}

			if (input.get_action(m_debug_action_keys[2]).state == State::active)
			{
				surface.push_request(surface::ModifyResolutionRequest({ width + 5, height + 5 }));
			}

			if (input.get_action(m_debug_action_keys[3]).state == State::active)
			{
				surface.push_request(surface::ModifyResolutionRequest({ width - 5, height - 5 }));
			}
		}

		const auto now = std::chrono::steady_clock::now();
		m_last_tick_result = app::TickResult {
			.info = tick,
			.duration = now - tick.start_time,
			.end_time = now,
		};
	}

	void on_register() override
	{
	}

	void on_unregister() override
	{
	}

	[[nodiscard]] auto get_last_tick_result() const -> const app::TickResult & override
	{
		return m_last_tick_result;
	}

private:
	memory::Ref<ecs::Registry> m_registry;


	lt::input::InputAction::Key m_quit_action_key;

	std::array<lt::input::InputAction::Key, 4> m_debug_action_keys {};

	app::TickResult m_last_tick_result {};
};

class Mirror: public app::Application
{
public:
	Mirror()
	{
		m_editor_registry = memory::create_ref<ecs::Registry>();

		setup_window_system();
		setup_input_system();

		register_systems();
	}

	void on_window_close()
	{
		log_inf("Window close requested...");

		unregister_system(m_input_system);
		unregister_system(m_surface_system);
		unregister_system(m_renderer_system);
		unregister_system(m_mirror_system);
	}

	void setup_window_system()
	{
		using lt::input::InputComponent;
		using lt::surface::SurfaceComponent;
		m_surface_system = memory::create_ref<lt::surface::System>(m_editor_registry);

		m_window = m_editor_registry->create_entity();
		m_surface_system->create_surface_component(
		    m_window,
		    SurfaceComponent::CreateInfo {
		        .title = "Editor Window",
		        .resolution = { 400u, 400u },
		        .vsync = true,
		        .visible = true,
		    }
		);

		auto &input = m_editor_registry->add<InputComponent>(m_window, {});
		auto quit_action_key = input.add_action(
		    input::InputAction {
		        .name = "quit",
		        .trigger = input::Trigger { .mapped_keycode = XK_q },
		    }
		);

		auto debug_action_keys = std::array<lt::input::InputAction::Key, 4> {};
		debug_action_keys[0] = input.add_action(
		    input::InputAction {
		        .name = "debug_1",
		        .trigger = input::Trigger { .mapped_keycode = XK_1 },
		    }
		);

		debug_action_keys[1] = input.add_action(
		    input::InputAction {
		        .name = "debug_2",
		        .trigger = input::Trigger { .mapped_keycode = XK_2 },
		    }
		);

		debug_action_keys[2] = input.add_action(
		    input::InputAction {
		        .name = "debug_3",
		        .trigger = input::Trigger { .mapped_keycode = XK_3 },
		    }
		);

		debug_action_keys[3] = input.add_action(
		    input::InputAction {
		        .name = "debug_4",
		        .trigger = input::Trigger { .mapped_keycode = XK_4 },
		    }
		);

		m_input_system = memory::create_ref<input::System>(m_editor_registry);
		m_mirror_system = memory::create_ref<MirrorSystem>(
		    m_editor_registry,
		    quit_action_key,
		    debug_action_keys
		);

		auto entity = ecs::Entity { m_editor_registry, m_window };
		memory::Ref<app::SystemStats> system_stats = nullptr;

		m_renderer_system = std::make_shared<renderer::System>(renderer::System::CreateInfo {
		    .config = { .target_api = renderer::Api::vulkan, .max_frames_in_flight = 3u },
		    .registry = m_editor_registry,
		    .surface_entity = entity,
		});

		std::ignore = m_renderer_system->create_messenger_component(
		    m_window,
		    renderer::MessengerComponent::CreateInfo {
		        .severities = renderer::MessageSeverity::all,
		        .types = renderer::MessageType::all,
		        .callback = &renderer_callback,
		        .user_data = this,
		    }
		);
	}

	void setup_input_system()
	{
	}

	void register_systems()
	{
		register_system(m_surface_system);
		register_system(m_input_system);
		register_system(m_renderer_system);
		register_system(m_mirror_system);
	}

private:
	memory::Ref<ecs::Registry> m_editor_registry;

	memory::Ref<lt::surface::System> m_surface_system;

	memory::Ref<lt::input::System> m_input_system;

	memory::Ref<lt::renderer::System> m_renderer_system;

	memory::Ref<MirrorSystem> m_mirror_system;

	lt::ecs::EntityId m_window = lt::ecs::null_entity;
};

auto app::create_application() -> memory::Scope<app::Application>
{
	return memory::create_scope<Mirror>();
}

} // namespace lt
