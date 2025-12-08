import app;
import app.system;
import std;
import logger;
import memory.scope;
import mirror.system;
import renderer.factory;

/** The ultimate entrypoint. */
auto main(int argc, char *argv[]) -> std::int32_t
{
	try
	{
		std::ignore = argc;
		std::ignore = argv;

		auto application = lt::memory::create_scope<lt::Mirror>();
		if (!application)
		{
			throw std::runtime_error { "Failed to create application\n" };
		}

		application->game_loop();
		return 0;
	}
	catch (const std::exception &exp)
	{
		lt::log::critical("Terminating due to uncaught exception:");
		lt::log::critical("\texception.what(): {}", exp.what());

		return 1;
	}
}
