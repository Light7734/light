#pragma once

#include <app/application.hpp>

auto main(int argc, char *argv[]) -> int32_t
try
{
	std::ignore = argc;
	std::ignore = argv;

	auto application = lt::Scope<lt::app::Application> {};

	application = lt::app::create_application();
	if (!application)
	{
		throw std::runtime_error { "Failed to create application\n" };
	}

	application->game_loop();
	return EXIT_SUCCESS;
}
catch (const std::exception &exp)
{
	log_crt("Terminating due to uncaught exception:");
	log_crt("\texception.what(): {}", exp.what());
	return EXIT_FAILURE;
}
