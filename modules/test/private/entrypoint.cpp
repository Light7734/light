#include <test/test.hpp>

using namespace ::lt::test;
using namespace ::lt::test::details;

void parse_option(std::string_view option, Registry::Options &options)
{
	if (option == "--stop-on-fail")
	{
		options.stop_on_fail = true;
		return;
	}

	throw std::invalid_argument { std::format("Invalid argument: {}", option) };
}

void print_help()
{
	std::println("Options: ");
	std::println("--stop-on-fail --> Stops executing the remaining tests on first failure");
	std::println("--stats        --> Print statistics about the tests without running any");
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
	}

	return Registry::run_all(options);
}
catch (const std::exception &exp)
{
	std::cout << "Terminated after uncaught exception:\n";
	std::cout << "exception.what: " << exp.what();
}
