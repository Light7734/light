import test;
import test.registry;

void parse_option(std::string_view argument, lt::test::Registry::Options &options)
{
	constexpr auto case_str = std::string_view { "--case=" };
	constexpr auto suite_str = std::string_view { "--suite=" };

	if (argument == "--stop-on-fail")
	{
		options.stop_on_fail = true;
		return;
	}

	if (argument.starts_with("--mode=") && argument.substr(7ul) == "stats")
	{
		options.execution_policy = lt::test::Registry::ExecutionPolicy::stats;
		return;
	}

	if (argument.starts_with("--verbosity="))
	{
		if (argument.substr(12ul) == "trace")
		{
			lt::log::set_severity(lt::log::Level::trace);
			std::println("Log level overriden to: trace");
			return;
		}

		if (argument.substr(12ul) == "debug")
		{
			lt::log::set_severity(lt::log::Level::debug);
			std::println("Log level overriden to: debug");
			return;
		}

		if (argument.substr(12ul) == "info")
		{
			lt::log::set_severity(lt::log::Level::info);
			std::println("Log level overriden to: info");
			return;
		}

		if (argument.substr(12ul) == "warn")
		{
			lt::log::set_severity(lt::log::Level::warn);
			std::println("Log level overriden to: warn");
			return;
		}

		if (argument.substr(12ul) == "error")
		{
			lt::log::set_severity(lt::log::Level::error);
			std::println("Log level overriden to: error");
			return;
		}

		if (argument.substr(12ul) == "critical")
		{
			lt::log::set_severity(lt::log::Level::critical);
			std::println("Log level overriden to: critical");
			return;
		}

		if (argument.substr(12ul) == "test")
		{
			lt::log::set_severity(lt::log::Level::test);
			std::println("Log level overriden to: test (this was not necessary...)");
			return;
		}
	}

	if (argument.starts_with(suite_str) && argument.length() > suite_str.size())
	{
		options.suite_regex = argument.substr(suite_str.length());
		std::println("SUITE REGEX: {}", options.suite_regex);
		return;
	}

	if (argument.starts_with(case_str) && argument.length() > case_str.size())
	{
		options.case_regex = argument.substr(case_str.length());
		std::println("CASE REGEX: {}", options.case_regex);
		return;
	}

	throw std::invalid_argument { std::format("Invalid argument: {}", argument) };
}

void print_help()
{
	std::println("Options: ");
	std::println("--verbosity=??? --> Sets the verbosity level of the logger");
	std::println(
	    "\t---> trace: Lowest and most vebose log level, for tracing execution paths and events"
	);
	std::println("\t---> debug: Vebose log level, for enabling temporarily to debug");
	std::println("\t---> info: General information");
	std::println("\t---> warn: Things we should to be aware of and edge cases");
	std::println("\t---> error: Defects, bugs and undesired behaviour");
	std::println("\t---> critical: Unrecoverable errors (on a module level)");
	std::println("\t---> test (default): No logs from the program, only test results");
	std::println("--stop-on-fail --> Stops executing the remaining tests on first failure");
	std::println("--suite        --> Regex for running specific suite(s)");
	std::println("--case         --> Regex for running specific test(s)");
	std::println("--mode=???   --> Executes tests with an alternative policy");
	std::println("\t---> (default): Runs normally");
	std::println("\t---> stats: Print statistics about the tests without running any");
	std::println("--help | -h    --> ~You just used it! :D");
}

auto main(i32 argc, char **argv) -> i32

try
{
	lt::log::set_severity(lt::log::Level::test);
	auto raw_arguments = std::span<char *>(argv, argc);

	auto options = lt::test::Registry::Options {};
	for (auto idx = 0; auto &raw_argument : raw_arguments)
	{
		// First argument is the "cwd'
		if (idx++ == 0)
		{
			continue;
		}

		auto argument = std::string_view(raw_argument);

		if (argument == "-h" || argument == "--help")
		{
			print_help();
			return 0;
		}

		if (argument.starts_with("--") || argument.starts_with("-"))
		{
			parse_option(argument, options);
		}
		else
		{
			throw std::invalid_argument { std::format("Invalid argument: {}", argument) };
		}
	}

	return lt::test::Registry::run_all(options);
}
catch (const std::exception &exp)
{
	std::cout << "Terminated due to uncaught exception:\n\twhat: " << exp.what();
	return 1;
}
catch (...)
{
	std::cout << "Terminated due to uncaught non-std exception!";
	return 1;
}
