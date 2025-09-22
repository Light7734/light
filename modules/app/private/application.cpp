#include <app/application.hpp>
#include <app/system.hpp>

namespace lt::app {

void Application::game_loop()
{
	while (true)
	{
		for (auto &system : m_systems)
		{
			const auto &last_tick = system->get_last_tick_result();
			const auto now = std::chrono::steady_clock::now();

			system->tick(
			    TickInfo {
			        .delta_time = now - last_tick.end_time,
			        .budget = std::chrono::milliseconds { 10 },
			        .start_time = now,
			    }
			);
		}

		for (auto &system : m_systems_to_be_registered)
		{
			m_systems.emplace_back(system)->on_register();
		}

		for (auto &system : m_systems_to_be_unregistered)
		{
			m_systems.erase(
			    std::remove(m_systems.begin(), m_systems.end(), system),
			    m_systems.end()
			);
		}

		if (m_systems.empty())
		{
			return;
		}
	}
}

void Application::register_system(Ref<app::ISystem> system)
{
	m_systems.emplace_back(std::move(system));
}

void Application::unregister_system(Ref<app::ISystem> system)
{
	m_systems_to_be_unregistered.emplace_back(std::move(system));
}

} // namespace lt::app
