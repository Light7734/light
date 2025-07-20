#include <test/test.hpp>

auto main() -> int32_t
try
{
	using namespace ::lt::test;
	using namespace ::lt::test::details;

	return Registry::run_all();
}
catch (const std::exception &exp)
{
	std::cout << "Terminated after uncaught exception:\n"; // NOLINT
	std::cout << "exception.what: " << exp.what();
}
