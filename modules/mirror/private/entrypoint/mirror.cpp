#include <app/application.hpp>
#include <app/entrypoint.hpp>
#include <app/system.hpp>
#include <math/vec2.hpp>
#include <surface/system.hpp>

namespace lt {

template<class... Ts>
struct overloads: Ts...
{
	using Ts::operator()...;
};

class Mirror: public app::Application
{
public:
	Mirror()
	{
		m_editor_registry = create_ref<ecs::Registry>();

		setup_window_system();
		register_systems();

		m_window_system->add_event_listener(
		    m_window,
		    [&](const surface::SurfaceComponent::Event &event) {
			    const auto visitor = overloads {
				    [&](const lt::surface::KeyPressedEvent &event) {
				        std::cout << "key pressed: " << event.to_string() << std::endl;

				        if (event.get_key() == 81)
				        {
					        unregister_system(m_window_system);
					        log_inf("Quitting...");
				        }
				        return true;
				    },
				    [](const auto &) { return false; },
			    };

			    return std::visit(visitor, event);
		    }
		);
	}

	void setup_window_system()
	{
		using lt::surface::SurfaceComponent;
		m_window_system = create_ref<lt::surface::System>(m_editor_registry);

		m_window = m_editor_registry->create_entity("Editor Window");
		m_window.add_component<SurfaceComponent>(SurfaceComponent::CreateInfo {
		    .title = "Editor Window",
		    .size = { 800u, 600u },
		    .vsync = true,
		    .visible = true,
		});
	}

	void register_systems()
	{
		register_system(m_window_system);
	}

private:
	Ref<ecs::Registry> m_editor_registry;

	Ref<lt::surface::System> m_window_system;

	lt::ecs::Entity m_window;
};

auto app::create_application() -> Scope<app::Application>
{
	return create_scope<Mirror>();
}

} // namespace lt
