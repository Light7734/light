export module app;
import app.system;
import lsd;

namespace lt::app {

/** The main application class.
 * Think of this like an aggregate of systems, you register systems through this interface.
 * Then they'll tick every "application frame".
 */
export class Application
{
public:
	Application(const Application &) = delete;

	Application(Application &&) = delete;

	auto operator=(const Application &) -> Application & = delete;

	auto operator=(Application &&) -> Application & = delete;

	virtual ~Application() = default;

	void game_loop();

	void register_system(lsd::ref<app::ISystem> system);

	void unregister_system(lsd::ref<app::ISystem> system);

protected:
	Application() = default;

private:
	lsd::vec<lsd::ref<app::ISystem>> m_systems;

	lsd::vec<lsd::ref<app::ISystem>> m_systems_to_be_unregistered;

	lsd::vec<lsd::ref<app::ISystem>> m_systems_to_be_registered;
};

} // namespace lt::app

module :private;
namespace lt::app {

void Application::game_loop()
{
	while (true)
	{
		for (auto &system : m_systems)
		{
			const auto &last_tick = system->get_last_tick_result();
			const auto now = lsd::chrono::steady_clock::now();

			system->tick(TickInfo {
			    .delta_time = now - last_tick.end_time,
			    .budget = lsd::chrono::milliseconds { 10 },
			    .start_time = now,
			});
		}

		for (auto &system : m_systems_to_be_registered)
		{
			m_systems.emplace_back(system)->on_register();
		}

		for (auto &system : m_systems_to_be_unregistered)
		{
			m_systems.erase(
			    lsd::remove(m_systems.begin(), m_systems.end(), system),
			    m_systems.end()
			);
		}

		if (m_systems.empty())
		{
			return;
		}
	}
}

void Application::register_system(lsd::ref<app::ISystem> system)
{
	m_systems.emplace_back(lsd::move(system));
}

void Application::unregister_system(lsd::ref<app::ISystem> system)
{
	m_systems_to_be_unregistered.emplace_back(lsd::move(system));
}

} // namespace lt::app
