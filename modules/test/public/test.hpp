#pragma once

#include <concepts>
#include <test/expects.hpp>

namespace lt::test {

namespace details {

class Registry
{
public:
	using FuzzFunction = int32_t (*)(const uint8_t *, size_t);
	using SuiteFunction = void (*)();

	static void register_suite(SuiteFunction suite)
	{
		instance().m_suites.emplace_back(suite);
	}

	static void register_fuzz_harness(FuzzFunction suite)
	{
		if (instance().m_fuzz_harness)
		{
			throw std::logic_error {
				"Attempting to register fuzz harness while one is already registered",
			};
		}

		instance().m_fuzz_harness = suite;
	}

	static auto run_all() -> int32_t
	{
		for (auto &test : instance().m_suites)
		{
			test();
		}

		std::cout << "Ran " << instance().m_failed_count + instance().m_pasesed_count << " tests:\n"
		          << "\tpassed: " << instance().m_pasesed_count << '\n'
		          << "\tfailed: " << instance().m_failed_count << '\n';
		std::cout << "________________________________________________________________\n\n\n";

		return instance().m_failed_count;
	}

	static auto process_fuzz_input(const uint8_t *data, size_t size) -> int32_t
	{
		if (!instance().m_fuzz_harness)
		{
			throw std::logic_error {
				"Attempting to process fuzz input with no active harness",
			};
		}

		return instance().m_fuzz_harness(data, size);
	}

	static void increment_passed_count()
	{
		++instance().m_pasesed_count;
	}

	static void increment_failed_count()
	{
		++instance().m_failed_count;
	}

private:
	Registry()
	{
		std::cout << "________________________________________________________________\n";
	}

	[[nodiscard]] static auto instance() -> Registry &
	{
		static auto registry = Registry {};
		return registry;
	}

	std::vector<SuiteFunction> m_suites;

	FuzzFunction m_fuzz_harness {};

	int32_t m_pasesed_count {};
	int32_t m_failed_count {};
};


} // namespace details

struct Case
{
	auto operator=(std::invocable auto test) -> void // NOLINT
	{
		std::cout << "[Running-----------] --> ";
		std::cout << name << '\n';

		try
		{
			test();
		}
		catch (const std::exception &exp)
		{
			std::cout << exp.what() << "\n";
			std::cout << "[-----------FAIL !!]" << "\n\n";
			details::Registry::increment_failed_count();
			return; // TODO(Light): Should we run the remaining tests after a failure?
		}

		details::Registry::increment_passed_count();
		std::cout << "[--------SUCCESS :D]" << "\n\n";
	}

	std::string_view name;
};

struct TestSuite
{
	template<class TSuite>
	constexpr TestSuite(TSuite suite)
	{
#ifndef LIGHT_SKIP_TESTS
		details::Registry::register_suite(+suite);
#endif
	}
};

struct TestFuzzHarness
{
	template<class TestFuzzHarness>
	constexpr TestFuzzHarness(TestFuzzHarness suite)
	{
#ifndef LIGHT_SKIP_FUZZ_TESTS
		details::Registry::register_fuzz_harness(+suite);
#endif
	}
};

using Suite = const TestSuite;
using FuzzHarness = const TestFuzzHarness;

} // namespace lt::test
