#pragma once

#ifdef LIGHT_PLATFORM_WINDOWS

	#include <LightEngine.hpp>

// to be defined in client project
extern Light::Application *Light::CreateApplication();

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
		application = Light::CreateApplication();
		ASSERT(application, "Light::Application is not intialized");

		for (int i = 0; i < argc; i++)
			LOG(info, "argv[{}]: {}", i, argv[i]);

		application->GameLoop();
	}
	// failed engine assertion
	catch (Light::FailedAssertion)
	{
		LOG(critical, "Terminating due to unhandled 'FailedEngineAssertion'");
		exitCode = -1;
	}
	// gl exception
	catch (Light::glException)
	{
		LOG(critical, "Terminating due to unhandled 'glException'");
		exitCode = -3;
	}
	// dx exception
	catch (Light::dxException)
	{
		LOG(critical, "Terminating due to unhandled 'dxException'");
		exitCode = -4;
	}

	delete application;
	return exitCode;
}

#elif defined(LIGHT_PLATFORM_LINUX)

	#include <engine/engine.hpp>

// to be defined in client project
extern Light::Application *Light::CreateApplication();

// #todo: use linux specific stuff
int main(int argc, char *argv[])
{
	Light::Application *application = nullptr;
	int exitCode = 0;

	try
	{
		application = Light::CreateApplication();
		ASSERT(application, "Light::Application is not intialized");

		application->GameLoop();
	}
	// failed engine assertion
	catch (Light::FailedAssertion)
	{
		LOG(critical, "Exitting due to unhandled 'FailedEngineAssertion'");
		exitCode = -1;
	}
	// gl exception
	catch (Light::glException)
	{
		LOG(critical, "main: exitting due to unhandled 'glException'");
		exitCode = -3;
	}

	delete application;
	return exitCode;
}

#endif
