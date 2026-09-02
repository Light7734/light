import preliminary;

import app;
import app.system;
import std;
import logger;
import mirror.system;

auto main(i32 argc, char *argv[]) -> i32
try
{
	ignore = argc;
	ignore = argv;

	auto application = create_scope<lt::Mirror>();
	if (!application)
	{
		throw std::runtime_error { "Failed to create application\n" };
	}

	application->game_loop();
	return 0;
}
catch (const std::exception &exp)
{
	std::cout << "Terminating due to uncaught exception:\n\texception.what(): " << exp.what();
	return 1;
}
