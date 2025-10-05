#pragma once

#include <memory/reference.hpp>
#include <memory/scope.hpp>

namespace lt::app {

class ISystem;

extern memory::Scope<class Application> create_application();

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

	void register_system(memory::Ref<app::ISystem> system);

	void unregister_system(memory::Ref<app::ISystem> system);

protected:
	Application() = default;

private:
	std::vector<memory::Ref<app::ISystem>> m_systems;

	std::vector<memory::Ref<app::ISystem>> m_systems_to_be_unregistered;

	std::vector<memory::Ref<app::ISystem>> m_systems_to_be_registered;
};


} // namespace lt::app
