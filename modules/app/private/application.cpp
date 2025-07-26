#include <app/application.hpp>
#include <app/system.hpp>

namespace lt::app {

void Application::game_loop()
{
	for (auto &system : m_systems)
	{
		system->init();
	}

	while (true)
	{
		for (auto &system : m_systems)
		{
			if (system->tick())
			{
				return;
			}
		}

		for (auto &system : m_systems_to_be_removed)
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
	m_systems_to_be_removed.emplace_back(std::move(system));
}

} // namespace lt::app
