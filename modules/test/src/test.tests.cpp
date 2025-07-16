#include <test/test.hpp>

lt::test::Suite meta = []() {
	using lt::test::expect_eq;

	lt::test::Case { "test_1" } = [] {
		expect_eq(5, 5);
	};

	lt::test::Case { "test_2" } = [] {
		expect_eq(20.0, 20.0);
	};

	lt::test::Case { "test_3" } = [] {
		expect_eq(true, false);
	};

	lt::test::Case { "test_4" } = [] {
		expect_eq(true, 1);
	};

	lt::test::Case { "test_5" } = [] {
		throw std::runtime_error("Uncaught std exception!");
	};
};
