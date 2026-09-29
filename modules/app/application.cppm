export module app;

import preliminary;
import app.system;

export namespace lt::app {

/** The main application class.
 * Think of this like an aggregate of `System`s,
 * You register a `System` with this, then it'll tick every "application frame".
 *
 * To make your own applications:
 *  - Make a subclass of `Application`,.
 *  - Do the required initialization work for your own application in its constructor.
 *  - Construct systems derived from `lt::app::System`.
 *  - Register them to be ticked via `register_system`.
 *  - Eventually, unregister every system via `unregister_system`, when wishing to exit the app.
 *  - The `gmae_loop` should terminate once all systems are unregistered
 *
 *  @note No `main` function is provided, you must implement your own, and at the end call
 *  `game_loop` to start your application/game.
 */
class Application
{
public:
	Application(const Application &) = delete;

	Application(Application &&) = delete;

	auto operator=(const Application &) -> Application & = delete;

	auto operator=(Application &&) -> Application & = delete;

	virtual ~Application() = default;

	/** Where the magic happens. */
	auto game_loop() -> i32;

	/** Adds a system to the app.
	 *
	 * This will result in system->tick() to be called on every game_loop() iteration,
	 * systems are ticked in order that they were registered.
	 *
	 * @return Whether the system was succesfully registered or not.
	 */
	auto register_system(ref<app::ISystem> system) -> bool;

	/** Removes a system from the app.
	 *
	 * This will result in system->tick() to NO LONGER be called on every game_loop() iteration.
	 *
	 * @return Whether the system was succesfully unregistered or not.
	 */

	auto unregister_system(ref<app::ISystem> system) -> bool;

protected:
	/** @warn Protected constructor, only constructible through subclasses. */
	Application() = default;

private:
	std::vector<ref<app::ISystem>> m_systems;

	std::vector<ref<app::ISystem>> m_systems_to_be_unregistered;

	std::vector<ref<app::ISystem>> m_systems_to_be_registered;
};

} // namespace lt::app

namespace lt::app {

auto Application::game_loop() -> i32
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
			return 0;
		}
	}

	return 0;
}

auto Application::register_system(ref<app::ISystem> system) -> bool
{
	m_systems.emplace_back(std::move(system));
	return true;
}

auto Application::unregister_system(ref<app::ISystem> system) -> bool
{
	m_systems_to_be_unregistered.emplace_back(std::move(system));
	return true;
}

} // namespace lt::app
