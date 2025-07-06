#pragma once

#ifdef LIGHT_PLATFORM_WINDOWS

	#include <engine/engine.hpp>

// to be defined in client project
extern Light::Application *Light::create_application();

// #todo: use windows specific stuff
int main(int argc, char *argv[])
{
	Light::Application *application = nullptr;
	int exitCode = 0;

	std::vector<std::string> args;

	if (argc > 1)
		args.assign(argv + 1, argv + argc);

	try
	{
		application = Light::create_application();
		lt_assert(application, "Light::Application is not intialized");

		for (int i = 0; i < argc; i++)
			lt_log(info, "argv[{}]: {}", i, argv[i]);

		application->game_loop();
	}
	// failed engine assertion
	catch (Light::FailedAssertion)
	{
		lt_log(critical, "Terminating due to unhandled 'FailedEngineAssertion'");
		exitCode = -1;
	}
	// gl exception
	catch (Light::glException)
	{
		lt_log(critical, "Terminating due to unhandled 'glException'");
		exitCode = -3;
	}
	// dx exception
	catch (Light::dxException)
	{
		lt_log(critical, "Terminating due to unhandled 'dxException'");
		exitCode = -4;
	}

	delete application;
	return exitCode;
}

#elif defined(LIGHT_PLATFORM_LINUX)

	#include <engine/engine.hpp>

// to be defined in client project
extern Light::Application *Light::create_application();

// #todo: use linux specific stuff
int main(int argc, char *argv[])
{
	Light::Application *application = nullptr;
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
		lt_log(critical, "Exitting due to unhandled 'FailedEngineAssertion'");
		exitCode = -1;
	}
	// gl exception
	catch (Light::glException)
	{
		lt_log(critical, "main: exitting due to unhandled 'glException'");
		exitCode = -3;
	}

	delete application;
	return exitCode;
}

#endif
