#include <test/test.hpp>

namespace lt::test {

auto process_fuzz_input(const uint8_t *data, size_t size) -> int32_t
try
{
	return details::Registry::process_fuzz_input(data, size);
}
catch (const std::exception &exp)
{
	std::println("Fuzz input resulted in uncaught exception:");
	std::println("\twhat: {}", exp.what());
	std::println("\tinput size: {}", size);

	return EXIT_FAILURE;
}

}; // namespace lt::test

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	return lt::test::process_fuzz_input(data, size);
}
