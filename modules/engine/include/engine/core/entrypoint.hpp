#pragma once

#ifdef LIGHT_PLATFORM_WINDOWS

	#include <engine/engine.hpp>

// to be defined in client project
extern auto lt::create_application() -> lt::Scope<lt::Application>;

// #todo: use windows specific stuff
int main(int argc, char *argv[])
{
	auto application = lt::Scope<lt::Application> {};
	int exitCode = 0;

	std::vector<std::string> args;

	if (argc > 1)
		args.assign(argv + 1, argv + argc);

	try
	{
		application = lt::create_application();
		lt_assert(application, "lt::Application is not intialized");

		for (int i = 0; i < argc; i++)
			log_inf("argv[{}]: {}", i, argv[i]);

		application->game_loop();
	}
	// failed engine assertion
	catch (lt::FailedAssertion)
	{
		log_crt("Terminating due to unhandled 'FailedEngineAssertion'");
		exitCode = -1;
	}
	// gl exception
	catch (lt::glException)
	{
		log_crt("Terminating due to unhandled 'glException'");
		exitCode = -3;
	}
	// dx exception
	catch (lt::dxException)
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
extern auto lt::create_application() -> lt::Scope<lt::Application>;

// #todo: use linux specific stuff
int main(int  /*argc*/, char * /*argv*/[])
{
	auto application = lt::Scope<lt::Application> {};
	int exitCode = 0;

	try
	{
		application = lt::create_application();
		lt_assert(application, "lt::Application is not intialized");

		application->game_loop();
	}
	// failed engine assertion
	catch (lt::FailedAssertion)
	{
		log_crt("Exitting due to unhandled 'FailedEngineAssertion'");
		exitCode = -1;
	}
	// gl exception
	catch (lt::glException)
	{
		log_crt("main: exitting due to unhandled 'glException'");
		exitCode = -3;
	}

	return exitCode;
}

#endif
