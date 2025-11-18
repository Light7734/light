export module test.test;

import test.expects;
import test.registry;
import std;
import lsd;

///////////////////////////////////////
// ----------* INTERFACE *--------- //
/////////////////////////////////////
namespace lt::test {

class TestCase
{
public:
	TestCase(lsd::str_view name);

	// NOLINTNEXTLINE(misc-unconventional-assign-operator)
	auto operator=(lsd::invocable auto test) const -> void;

private:
	void run_normal(lsd::invocable auto test) const;

private:
	lsd::str_view m_name;
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

///////////////////////////////////////
// * IMPLEMENTATION -- TEMPLATES *  //
/////////////////////////////////////

// NOLINTNEXTLINE(misc-unconventional-assign-operator)
auto TestCase::operator=(lsd::invocable auto test) const -> void
{
	using enum Registry::ExecutionPolicy;

	switch (Registry::get_options().execution_policy)
	{
	case normal: run_normal(lsd::move(test)); break;
	case stats: Registry::increment_total_case_count(); break;
	}
}

void TestCase::run_normal(lsd::invocable auto test) const
{
	Registry::increment_total_case_count();

	// NOLINTNEXTLINE
	if (!std::regex_search(m_name.data(), Registry::get_case_regex()))
	{
		Registry::increment_skipped_case_count();
		return;
	}
	Registry::increment_matched_case_count();

	lsd::println("[Running-----------] --> ");
	lsd::println("{}", m_name);
	try
	{
		test();
	}
	catch (const std::exception &exp)
	{
		lsd::println("{}", exp.what());
		lsd::println("[-----------FAIL !!]");
		Registry::increment_failed_case_count();

		if (Registry::should_return_on_failure())
		{
			throw;
		}

		return;
	}

	Registry::increment_passed_case_count();
	lsd::println("[--------SUCCESS :D]");
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
	Registry::set_last_suite_name(name);
	return {};
}

} // namespace lt::test

//////////////////////////////////////
// -------* IMPLEMENTATION *------- //
/////////////////////////////////////
module :private;
namespace lt::test {

TestCase::TestCase(lsd::str_view name): m_name(name)
{
}

} // namespace lt::test
