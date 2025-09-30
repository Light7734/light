#include <test/test.hpp>

using namespace ::lt::test;
using namespace ::lt::test::details;

void parse_option(std::string_view argument, Registry::Options &options)
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
		options.execution_policy = Registry::ExecutionPolicy::stats;
		return;
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
	std::println("--stop-on-fail --> Stops executing the remaining tests on first failure");
	std::println("--suite        --> Regex for running specific suite(s)");
	std::println("--case         --> Regex for running specific test(s)");
	std::println("--mode=stats   --> Executes tests with an alternative policy");
	std::println("\t---> stats: Print statistics about the tests without running any");
	std::println("--help | -h    --> ~You just used it! :D");
}

auto main(int32_t argc, char **argv) -> int32_t
try
{
	auto raw_arguments = std::span<char *>(argv, argc);

	auto options = Registry::Options {};
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

	return static_cast<int32_t>(Registry::run_all(options));
}
catch (const std::exception &exp)
{
	std::println("Terminated due to uncaught exception:");
	std::println("\twhat: {}", exp.what());

	return EXIT_FAILURE;
}
catch (...)
{
	std::println("Terminated due to uncaught non-std exception!");

	return EXIT_FAILURE;
}
