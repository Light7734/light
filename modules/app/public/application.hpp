#pragma once

namespace lt::app {

class ISystem;

extern Scope<class Application> create_application();

/** The main application class.
 * Think of this like an aggregate of systems, you register systems through this interface.
 * Then they'll tick every "application frame".
 */
class Application
{
public:
	Application(const Application &) = delete;

	Application(Application &&) = delete;

	auto operator=(const Application &) -> Application & = delete;

	auto operator=(Application &&) -> Application & = delete;

	virtual ~Application() = default;

	void game_loop();

	void register_system(Ref<app::ISystem> system);

	void unregister_system(Ref<app::ISystem> system);

protected:
	Application() = default;

private:
	std::vector<Ref<app::ISystem>> m_systems;

	std::vector<Ref<app::ISystem>> m_systems_to_be_removed;
};


} // namespace lt::app
