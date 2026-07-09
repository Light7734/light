export module test.test;

import test.expects;
import test.registry;
import preliminary;
import logger;

namespace lt::test {

class TestCase
{
public:
	TestCase(std::string name);

	// NOLINTNEXTLINE(misc-unconventional-assign-operator)
	auto operator=(std::invocable auto test) const -> void;

private:
	void run_normal(std::invocable auto test) const;

	std::string m_name {};
};

struct TestSuite
{
	TestSuite(auto body);
	TestSuite() = default;
};

struct TestFuzzHarness
{
	constexpr TestFuzzHarness(auto body);
};

export using Case = const TestCase;
export using Suite = const TestSuite;
export using FuzzHarness = const TestFuzzHarness;
export auto operator""_suite(const char *name, size_t size) -> TestSuite;

// NOLINTNEXTLINE(misc-unconventional-assign-operator)
auto TestCase::operator=(std::invocable auto test) const -> void
{
	using enum Registry::ExecutionPolicy;

	switch (Registry::get_options().execution_policy)
	{
	case normal: run_normal(std::move(test)); break;
	case stats: Registry::increment_total_case_count(); break;
	}
}

void TestCase::run_normal(std::invocable auto test) const
{
	Registry::increment_total_case_count();

	// NOLINTNEXTLINE
	if (!std::regex_search(m_name.data(), Registry::get_case_regex()))
	{
		Registry::increment_skipped_case_count();
		return;
	}
	Registry::increment_matched_case_count();

	auto padding = std::string {};
	padding.resize(79 - m_name.size());
	for (auto &ch : padding)
	{
		ch = ' ';
	}

	try
	{
		test();
	}
	catch (const std::exception &exp)
	{
		log::test(
		    "\033[1;31m{}{} | {}\033[0m",
		    std::string_view { m_name },
		    std::string { padding },
		    std::string { exp.what() }
		);

		Registry::increment_failed_case_count();

		if (Registry::should_return_on_failure())
		{
			throw;
		}

		return;
	}

	Registry::increment_passed_case_count();


	log::test("{}{} | \033[1;32mpass\033[0m", std::string_view { m_name }, std::string { padding });
}

TestSuite::TestSuite(auto body)
{
#ifndef LIGHT_SKIP_TESTS
	Registry::register_suite(+body);
#endif
}

constexpr TestFuzzHarness::TestFuzzHarness(auto body)
{
#ifndef LIGHT_SKIP_FUZZ_TESTS
	Registry::register_fuzz_harness(+body);
#endif
};

auto operator""_suite(const char *name, size_t size) -> TestSuite
{
	// TODO(Light): do we need the size parameter?
	ignore = size;

	Registry::set_last_suite_name(name);
	return {};
}

} // namespace lt::test

namespace lt::test {

TestCase::TestCase(std::string name): m_name(std::move(name))
{
	if (m_name.size() > 79u)
	{
		m_name.resize(79u - 3);
		m_name.append("...");
	}
}

} // namespace lt::test
