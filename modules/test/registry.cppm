export module test.registry;

import std;
import test.expects;

///////////////////////////////////////
// ----------* INTERFACE *--------- //
/////////////////////////////////////
namespace lt::test {

export class Registry
{
public:
	enum class ExecutionPolicy : std::uint8_t
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

	using FuzzFunction = std::int32_t (*)(const std::uint8_t *, std::size_t);

	using SuiteFunction = void (*)();

	static void register_suite(SuiteFunction suite);

	static void register_fuzz_harness(FuzzFunction suite);

	static auto run_all(Options options) -> std::int32_t;

	static auto process_fuzz_input(const std::uint8_t *data, std::size_t size) -> std::int32_t;

	static void set_last_suite_name(const char *name);

	static void increment_total_suite_count();

	static void increment_matched_suite_count();

	static void increment_skipped_suite_count();

	static void increment_passed_suite_count();

	static void increment_failed_suite_count();

	static void increment_total_case_count();

	static void increment_matched_case_count();

	static void increment_skipped_case_count();

	static void increment_passed_case_count();

	static void increment_failed_case_count();

	[[nodiscard]] static auto should_return_on_failure() -> bool;

	[[nodiscard]] static auto get_options() -> const Options &;

	[[nodiscard]] static auto get_case_regex() -> const std::regex &;

private:
	Registry();

	[[nodiscard]] static auto instance() -> Registry &;

	auto run_all_impl() -> std::int32_t;

	void print_options();

	Options m_options {};

	std::vector<std::pair<SuiteFunction, const char *>> m_suites;

	FuzzFunction m_fuzz_harness {};

	std::int32_t m_total_case_count {};

	std::int32_t m_passed_case_count {};

	std::int32_t m_failed_case_count {};

	std::int32_t m_matched_case_count {};

	std::int32_t m_skipped_case_count {};

	std::int32_t m_total_suite_count {};

	std::int32_t m_passed_suite_count {};

	std::int32_t m_failed_suite_count {};

	std::int32_t m_matched_suite_count {};

	std::int32_t m_skipped_suite_count {};

	std::regex m_case_regex;
};

} // namespace lt::test

//////////////////////////////////////
// -------* IMPLEMENTATION *------- //
/////////////////////////////////////
module :private;
using namespace lt::test;

/* static */ void Registry::register_suite(SuiteFunction suite)
{
	instance().m_suites.emplace_back(suite, "");
}

/* static */ void Registry::register_fuzz_harness(FuzzFunction suite)
{
	if (instance().m_fuzz_harness)
	{
		throw std::logic_error {
			"Attempting to register fuzz harness while one is already registered",
		};
	}

	instance().m_fuzz_harness = suite;
}

/* static */ auto Registry::run_all(Options options) -> std::int32_t
{
	instance().m_options = std::move(options);
	return instance().run_all_impl();
}

/* static */ auto Registry::process_fuzz_input(const std::uint8_t *data, std::size_t size)
    -> std::int32_t
{
	if (!instance().m_fuzz_harness)
	{
		throw std::logic_error {
			"Attempting to process fuzz input with no active harness",
		};
	}

	return instance().m_fuzz_harness(data, size);
}

/* static */ void Registry::set_last_suite_name(const char *name)
{
	instance().m_suites.back().second = name;
}

/* static */ void Registry::increment_total_suite_count()
{
	++instance().m_total_suite_count;
}

/* static */ void Registry::increment_matched_suite_count()
{
	++instance().m_matched_suite_count;
}

/* static */ void Registry::increment_skipped_suite_count()
{
	++instance().m_skipped_suite_count;
}

/* static */ void Registry::increment_passed_suite_count()
{
	++instance().m_passed_suite_count;
}

/* static */ void Registry::increment_failed_suite_count()
{
	++instance().m_failed_suite_count;
}

/* static */ void Registry::increment_total_case_count()
{
	++instance().m_total_case_count;
}

/* static */ void Registry::increment_matched_case_count()
{
	++instance().m_matched_case_count;
}

/* static */ void Registry::increment_skipped_case_count()
{
	++instance().m_skipped_case_count;
}

/* static */ void Registry::increment_passed_case_count()
{
	++instance().m_passed_case_count;
}

/* static */ void Registry::increment_failed_case_count()
{
	++instance().m_failed_case_count;
}

[[nodiscard]] /* static */ auto Registry::should_return_on_failure() -> bool
{
	return instance().m_options.stop_on_fail;
}

[[nodiscard]] /* static */ auto Registry::get_options() -> const Options &
{
	return instance().m_options;
}

[[nodiscard]] /* static */ auto Registry::get_case_regex() -> const std::regex &
{
	return instance().m_case_regex;
}

auto Registry::run_all_impl() -> std::int32_t
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

		return 0;
	}
	}

	std::unreachable();
}

void Registry::print_options()
{
	std::println("stop-on-failure: {}", m_options.stop_on_fail);
}

Registry::Registry()
{
	std::println("________________________________________________________________");
}

[[nodiscard]] /* static */ auto Registry::instance() -> Registry &
{
	static auto registry = Registry {};
	return registry;
}
