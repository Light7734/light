#pragma once

#include <concepts>
#include <test/expects.hpp>

namespace lt::test {

namespace details {

class Registry
{
public:
	struct Options
	{
		bool stop_on_fail = false;
	};

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

	static auto run_all(Options options) -> int32_t
	{
		instance().m_options = options;
		instance().print_options();

		for (auto &test : instance().m_suites)
		{
			try
			{
				test();
			}
			catch (const std::exception &exp)
			{
				if (options.stop_on_fail)
				{
					std::println("Quitting due to options.stop_on_fail == true");
					break;
				}

				std::println("Uncaught exception when running suite:");
				std::println("\twhat: {}", exp.what());
				break;
			}
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

	static auto should_return_on_failure() -> bool
	{
		return instance().m_options.stop_on_fail;
	}

private:
	void print_options()
	{
        std::println("stop-on-failure: {}", m_options.stop_on_fail);
	}

	Registry()
	{
		std::cout << "________________________________________________________________\n";
	}

	[[nodiscard]] static auto instance() -> Registry &
	{
		static auto registry = Registry {};
		return registry;
	}

	Options m_options {};

	std::vector<SuiteFunction> m_suites;

	FuzzFunction m_fuzz_harness {};

	int32_t m_pasesed_count {};
	int32_t m_failed_count {};
};


} // namespace details

struct Case
{
	// NOLINTNEXTLINE(misc-unconventional-assign-operator)
	auto operator=(std::invocable auto test) -> void
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

			if (details::Registry::should_return_on_failure())
			{
				throw;
			}
		}

		details::Registry::increment_passed_count();
		std::cout << "[--------SUCCESS :D]" << "\n\n";
	}

	std::string_view name;
};

struct TestSuite
{
	template<class TSuite>
	constexpr TestSuite(TSuite body)
	{
#ifndef LIGHT_SKIP_TESTS
		details::Registry::register_suite(+body);
#endif
	}
};

struct TestFuzzHarness
{
	template<class TestFuzzHarnessBody>
	constexpr TestFuzzHarness(TestFuzzHarnessBody body)
	{
#ifndef LIGHT_SKIP_FUZZ_TESTS
		details::Registry::register_fuzz_harness(+body);
#endif
	}
};

using Suite = const TestSuite;
using FuzzHarness = const TestFuzzHarness;

} // namespace lt::test
