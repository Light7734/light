#pragma once

#ifdef LIGHT_PLATFORM_WINDOWS

	#include <engine/engine.hpp>

// to be defined in client project
extern auto Light::create_application() -> Light::Scope<Light::Application>;

// #todo: use windows specific stuff
int main(int argc, char *argv[])
{
	auto application = Light::Scope<Light::Application> {};
	int exitCode = 0;

	std::vector<std::string> args;

	if (argc > 1)
		args.assign(argv + 1, argv + argc);

	try
	{
		application = Light::create_application();
		lt_assert(application, "Light::Application is not intialized");

		for (int i = 0; i < argc; i++)
			log_inf("argv[{}]: {}", i, argv[i]);

		application->game_loop();
	}
	// failed engine assertion
	catch (Light::FailedAssertion)
	{
		log_crt("Terminating due to unhandled 'FailedEngineAssertion'");
		exitCode = -1;
	}
	// gl exception
	catch (Light::glException)
	{
		log_crt("Terminating due to unhandled 'glException'");
		exitCode = -3;
	}
	// dx exception
	catch (Light::dxException)
	{
		log_crt("Terminating due to unhandled 'dxException'");
		exitCode = -4;
	}

	delete application;
	return exitCode;
}

#elif defined(LIGHT_PLATFORM_LINUX)

	#include <engine/engine.hpp>

// to be defined in client project
extern auto Light::create_application() -> Light::Scope<Light::Application>;

// #todo: use linux specific stuff
int main(int argc, char *argv[])
{
	auto application = Light::Scope<Light::Application> {};
	int exitCode = 0;

	try
	{
		application = Light::create_application();
		lt_assert(application, "Light::Application is not intialized");

		application->game_loop();
	}
	// failed engine assertion
	catch (Light::FailedAssertion)
	{
		log_crt("Exitting due to unhandled 'FailedEngineAssertion'");
		exitCode = -1;
	}
	// gl exception
	catch (Light::glException)
	{
		log_crt("main: exitting due to unhandled 'glException'");
		exitCode = -3;
	}

	return exitCode;
}

#endif
