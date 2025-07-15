#pragma once

#include <concepts>
#include <test/expects.hpp>

namespace lt::test {

namespace concepts {

template<typename T>
concept printable = requires(std::ostream &os, T t) {
	{ os << t } -> std::same_as<std::ostream &>;
};

template<
    class T,
    auto expr =
        [] {
        }>
concept test = requires(T test) {
	{ test.name } -> printable;

	{ test = expr } -> std::same_as<void>;
};

} // namespace concepts


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
			return; // TODO(Light): Should we run the remaining tests after a failure?
		}

		std::cout << " --> SUCCESS :D" << "\n";
	}

	std::string_view name;
};

namespace details {


class Registry
{
public:
	using Suite = void (*)();

	static void register_suite(Suite suite)
	{
		instance().m_suites.emplace_back(suite);
	}

	static void run_all()
	{
		for (auto &test : instance().m_suites)
		{
			test();
		}
	}

private:
	Registry() = default;

	[[nodiscard]] static auto instance() -> Registry &
	{
		static auto registry = Registry {};
		return registry;
	}

	std::vector<void (*)()> m_suites;
};


} // namespace details

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
