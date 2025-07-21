#include <test/test.hpp>

lt::test::Suite meta = []() {
	using lt::test::expect_eq;
	using lt::test::expect_true;

	lt::test::Case { "test_1" } = [] {
		expect_eq(5, 5);
	};

	lt::test::Case { "test_2" } = [] {
		expect_eq(20.0, 20.0);
	};

	lt::test::Case { "test_3" } = [] {
		auto exception_thrown = false;

		try
		{
			expect_eq(true, false);
		}
		catch (const std::exception &exp)
		{
			exception_thrown = true;
		}

		expect_true(exception_thrown);
	};

	lt::test::Case { "test_4" } = [] {
		expect_eq(true, 1);
	};

	lt::test::Case { "test_5" } = [] {
	};
};
