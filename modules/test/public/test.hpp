#pragma once

#include <concepts>
#include <test/expects.hpp>

namespace lt::test {

namespace concepts {

template<typename T>
concept printable = requires(std::ostream &os, T t) {
	{ os << t } -> std::same_as<std::ostream &>;
};

// clang-format off
template<class T, auto expr = []{}>
concept test = requires(T test) {
	{ test.name } -> printable;
	{ test = expr } -> std::same_as<void>;
};
// clang-format on

} // namespace concepts

namespace details {

class Registry
{
public:
	using Suite = void (*)();

	static void register_suite(Suite suite)
	{
		instance().m_suites.emplace_back(suite);
	}

	static auto run_all() -> int32_t
	{
		for (auto &test : instance().m_suites)
		{
			test();
		}

		std::cout << "_________________________[TEST RESULTS]_________________________\n";
		std::cout << "Ran " << instance().m_failed_count + instance().m_pasesed_count << " tests:\n"
		          << "\tpassed: " << instance().m_pasesed_count << '\n'
		          << "\tfailed: " << instance().m_failed_count << '\n';

		return instance().m_failed_count;
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
	Registry() = default;

	[[nodiscard]] static auto instance() -> Registry &
	{
		static auto registry = Registry {};
		return registry;
	}

	std::vector<void (*)()> m_suites;

	int32_t m_pasesed_count {};
	int32_t m_failed_count {};
};


} // namespace details

struct Case
{
	auto operator=(std::invocable auto test) -> void // NOLINT
	{
		std::cout << "Running... " << name;

		try
		{
			test();
		}
		catch (const std::exception &exp)
		{
			std::cout << " --> FAIL !" << '\n';
			std::cout << exp.what() << "\n\n";
			details::Registry::increment_failed_count();
			return; // TODO(Light): Should we run the remaining tests after a failure?
		}

		details::Registry::increment_passed_count();
		std::cout << " --> SUCCESS :D" << "\n";
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

using Suite = const TestSuite;

} // namespace lt::test
