#pragma once

#include <app/application.hpp>
#include <logger/logger.hpp>
#include <memory/scope.hpp>

auto main(int argc, char *argv[]) -> int32_t
try
{
	std::ignore = argc;
	std::ignore = argv;

	auto application = lt::memory::Scope<lt::app::Application> {};
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
	lt::log::critical("Terminating due to uncaught exception:");
	lt::log::critical("\texception.what(): {}", exp.what());
	return EXIT_FAILURE;
}
