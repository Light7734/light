export module test.registry;

import logger;
import preliminary;
import test.expects;

namespace lt::test {

export class Registry
{
public:
	enum class ExecutionPolicy : u8
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

	using FuzzFunction = i32 (*)(const u8 *, size_t);

	using SuiteFunction = void (*)();

	static void register_suite(SuiteFunction suite);

	static void register_fuzz_harness(FuzzFunction suite);

	static auto run_all(Options options) -> i32;

	static auto process_fuzz_input(const u8 *data, size_t size) -> i32;

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
	Registry() = default;

	[[nodiscard]] static auto instance() -> Registry &;

	auto run_all_impl() -> i32;

	Options m_options {};

	std::vector<std::pair<SuiteFunction, const char *>> m_suites;

	FuzzFunction m_fuzz_harness {};

	i32 m_total_case_count {};

	i32 m_passed_case_count {};

	i32 m_failed_case_count {};

	i32 m_matched_case_count {};

	i32 m_skipped_case_count {};

	i32 m_total_suite_count {};

	i32 m_passed_suite_count {};

	i32 m_failed_suite_count {};

	i32 m_matched_suite_count {};

	i32 m_skipped_suite_count {};

	std::regex m_case_regex;
};

} // namespace lt::test

namespace lt::test {

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

/* static */ auto Registry::run_all(Options options) -> i32
{
	instance().m_options = std::move(options);
	return instance().run_all_impl();
}

/* static */ auto Registry::process_fuzz_input(const u8 *data, size_t size) -> i32
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

/* static */ [[nodiscard]] auto Registry::should_return_on_failure() -> bool
{
	return instance().m_options.stop_on_fail;
}

/* static */ [[nodiscard]] auto Registry::get_options() -> const Options &
{
	return instance().m_options;
}

/* static */ [[nodiscard]] auto Registry::get_case_regex() -> const std::regex &
{
	return instance().m_case_regex;
}

auto Registry::run_all_impl() -> i32
{
	m_case_regex = std::regex(m_options.case_regex);

	const auto regex = std::regex(m_options.suite_regex);
	for (auto &[suite, name] : m_suites)
	{
		try
		{
			if (std::regex_search(name, regex))
			{
				auto padding_left = std::string {};
				padding_left.resize((79 - std::strlen(name)) / 2u - 1u);
				for (auto &ch : padding_left)
				{
					ch = '-';
				}

				auto padding_right = std::string {};
				padding_right.resize((79 - std::strlen(name)) / 2u);
				if (std::strlen(name) % 2 == 0)
				{
					padding_right.resize(padding_right.size() + 1);
				}
				for (auto &ch : padding_right)
				{
					ch = '-';
				}

				log::test(
				    "\033[1;33m*{}{}{}-*\033[0m",
				    std::string { padding_left },
				    std::string_view { name },
				    std::string { padding_right }
				);
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
				log::info("Quitting due to options.stop_on_fail == true");
				break;
			}

			log::test("Uncaught exception when running suite:");
			log::test("\twhat: {}", exp.what());
			break;
		}
	}

	switch (m_options.execution_policy)
	{
	case ExecutionPolicy::normal:
	{
		// log::test("[-------STATS------]");
		//
		// log::test("suites:");
		// log::test("\ttotal: {}", (i32)m_total_suite_count);
		// log::test("\tpassed: {}", (i32)m_passed_suite_count);
		// log::test("\tfailed: {}", (i32)m_failed_suite_count);
		// log::test("\tmatched: {}", (i32)m_matched_suite_count);
		// log::test("\tskipped: {}", (i32)m_skipped_suite_count);
		//
		// log::test("tests:");
		// log::test("\ttotal: {}", (i32)m_total_case_count);
		// log::test("\tpassed: {}", (i32)m_passed_case_count);
		// log::test("\tfailed: {}", (i32)m_failed_case_count);
		// log::test("\tmatched: {}", (i32)m_matched_case_count);
		// log::test("\tskipped: {}", (i32)m_skipped_case_count);

		// log::test("________________________________________________________________");

		return m_failed_case_count;
	}
	case ExecutionPolicy::stats:
	{
		log::test("[-------STATS------]");
		log::test("Total suite count: {}", m_total_suite_count);
		log::test("Total test count: {}", m_total_case_count);
		log::test("________________________________________________________________");

		return 0;
	}
	}

	std::unreachable();
}

[[nodiscard]] /* static */ auto Registry::instance() -> Registry &
{
	static auto registry = Registry {};
	return registry;
}

} // namespace lt::test
