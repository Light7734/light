#pragma once

#include <concepts>
#include <format>
#include <regex>
#include <test/expects.hpp>

namespace lt::test {

namespace details {

class Registry
{
public:
	enum class ExecutionPolicy : uint8_t
	{
		normal,
		stats,
	};

	struct Options
	{
		bool stop_on_fail = false;

		ExecutionPolicy execution_policy = ExecutionPolicy::normal;

		std::string suite_regex;

		std::string case_regex;
	};

	using FuzzFunction = int32_t (*)(const uint8_t *, size_t);
	using SuiteFunction = void (*)();

	static void register_suite(SuiteFunction suite)
	{
		instance().m_suites.emplace_back(suite, "");
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

	static auto run_all(Options options) -> uint32_t
	{
		instance().m_options = std::move(options);
		return instance().run_all_impl();
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

	static void set_last_suite_name(const char *name)
	{
		instance().m_suites.back().second = name;
	}

	static void increment_total_suite_count()
	{
		++instance().m_total_suite_count;
	}

	static void increment_matched_suite_count()
	{
		++instance().m_matched_suite_count;
	}

	static void increment_skipped_suite_count()
	{
		++instance().m_skipped_suite_count;
	}

	static void increment_passed_suite_count()
	{
		++instance().m_passed_suite_count;
	}

	static void increment_failed_suite_count()
	{
		++instance().m_failed_suite_count;
	}

	static void increment_total_case_count()
	{
		++instance().m_total_case_count;
	}

	static void increment_matched_case_count()
	{
		++instance().m_matched_case_count;
	}

	static void increment_skipped_case_count()
	{
		++instance().m_skipped_case_count;
	}

	static void increment_passed_case_count()
	{
		++instance().m_passed_case_count;
	}

	static void increment_failed_case_count()
	{
		++instance().m_failed_case_count;
	}

	[[nodiscard]] static auto should_return_on_failure() -> bool
	{
		return instance().m_options.stop_on_fail;
	}

	[[nodiscard]] static auto get_options() -> const Options &
	{
		return instance().m_options;
	}

	[[nodiscard]] static auto get_case_regex() -> const std::regex &
	{
		return instance().m_case_regex;
	}

private:
	auto run_all_impl() -> uint32_t
	{
		print_options();
		m_case_regex = std::regex(m_options.case_regex);

		const auto regex = std::regex(m_options.suite_regex);
		for (auto &[suite, name] : m_suites)
		{
			try
			{
				if (std::regex_search(name, regex))
				{
					suite();
					increment_matched_suite_count();
				}
				else
				{
					increment_skipped_suite_count();
				}

				increment_total_suite_count();
			}
			catch (const std::exception &exp)
			{
				if (m_options.stop_on_fail)
				{
					std::println("Quitting due to options.stop_on_fail == true");
					break;
				}

				std::println("Uncaught exception when running suite:");
				std::println("\twhat: {}", exp.what());
				break;
			}
		}

		switch (m_options.execution_policy)
		{
		case ExecutionPolicy::normal:
		{
			std::println("[-------STATS------]");

			std::println("suites:");
			std::println("\ttotal: {}", m_total_suite_count);
			std::println("\tpassed: {}", m_passed_suite_count);
			std::println("\tfailed: {}", m_failed_suite_count);
			std::println("\tmatched: {}", m_matched_suite_count);
			std::println("\tskipped: {}", m_skipped_suite_count);

			std::println("tests:");
			std::println("\ttotal: {}", m_total_case_count);
			std::println("\tpassed: {}", m_passed_case_count);
			std::println("\tfailed: {}", m_failed_case_count);
			std::println("\tmatched: {}", m_matched_case_count);
			std::println("\tskipped: {}", m_skipped_case_count);

			std::println("________________________________________________________________");

			return m_failed_case_count;
		}
		case ExecutionPolicy::stats:
		{
			std::println("[-------STATS------]");
			std::println("Total suite count: {}", m_total_suite_count);
			std::println("Total test count: {}", m_total_case_count);
			std::println("________________________________________________________________");
			return EXIT_SUCCESS;
		}
		}
	}

	void print_options()
	{
		std::println("stop-on-failure: {}", m_options.stop_on_fail);
	}

	Registry()
	{
		std::println("________________________________________________________________");
	}

	[[nodiscard]] static auto instance() -> Registry &
	{
		static auto registry = Registry {};
		return registry;
	}

	Options m_options {};

	std::vector<std::pair<SuiteFunction, const char *>> m_suites;

	FuzzFunction m_fuzz_harness {};

	uint32_t m_total_case_count {};

	uint32_t m_passed_case_count {};

	uint32_t m_failed_case_count {};

	uint32_t m_matched_case_count {};

	uint32_t m_skipped_case_count {};

	uint32_t m_total_suite_count {};

	uint32_t m_passed_suite_count {};

	uint32_t m_failed_suite_count {};

	uint32_t m_matched_suite_count {};

	uint32_t m_skipped_suite_count {};

	std::regex m_case_regex;
};


} // namespace details

class Case
{
public:
	Case(std::string_view name): m_name(name)
	{
	}

	// NOLINTNEXTLINE(misc-unconventional-assign-operator)
	auto operator=(std::invocable auto test) -> void
	{
		using details::Registry;
		using enum Registry::ExecutionPolicy;

		switch (Registry::get_options().execution_policy)
		{
		case normal: run_normal(std::move(test)); break;
		case stats: Registry::increment_total_case_count(); break;
		}
	}

private:
	void run_normal(std::invocable auto test)
	{
		using details::Registry;
		Registry::increment_total_case_count();

		// NOLINTNEXTLINE
		if (!std::regex_search(m_name.data(), Registry::get_case_regex()))
		{
			Registry::increment_skipped_case_count();
			return;
		}
		Registry::increment_matched_case_count();

		std::println("[Running-----------] --> ");
		std::println("{}", m_name);
		try
		{
			test();
		}
		catch (const std::exception &exp)
		{
			std::println("{}", exp.what());
			std::println("[-----------FAIL !!]");
			Registry::increment_failed_case_count();

			if (Registry::should_return_on_failure())
			{
				throw;
			}

			return;
		}

		Registry::increment_passed_case_count();
		std::println("[--------SUCCESS :D]");
	}

	std::string_view m_name;
};

struct TestSuite
{
	template<typename TSuite>
	TestSuite(TSuite body)
	{
#ifndef LIGHT_SKIP_TESTS
		details::Registry::register_suite(+body);
#endif
	}

	TestSuite() = default;
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

inline auto operator""_suite(const char *name, size_t size) -> lt::test::TestSuite
{
	lt::test::details::Registry::set_last_suite_name(name);
	return {};
}
