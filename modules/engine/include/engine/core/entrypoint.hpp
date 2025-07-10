#pragma once

#include <engine/engine.hpp>

int main(int argc, char *argv[]) // NOLINT
try
{
	std::ignore = argc;
	std::ignore = argv;

	auto application = lt::Scope<lt::Application> {};

	application = lt::create_application();

	lt::ensure(application, "Failed to create application");
	lt::ensure(application->sanity_check(), "Failed to verify the sanity of the application");

	application->game_loop();

	return EXIT_SUCCESS;
}
catch (const std::exception &exp)
{
	log_crt("Terminating due to uncaught exception:");
	log_crt("\texception.what(): {}", exp.what());
	return EXIT_FAILURE;
}
