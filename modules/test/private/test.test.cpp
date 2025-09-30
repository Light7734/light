#include <test/test.hpp>

using lt::test::Case;
using lt::test::Suite;

Suite expects = "expects"_suite = []() {
	using lt::test::expect_unreachable;
	using lt::test::expect_true;
	using lt::test::expect_false;
	using lt::test::expect_eq;
	using lt::test::expect_ne;
	using lt::test::expect_le;
	using lt::test::expect_throw;

	Case { "" } = [] {
	};

	Case { "expect_unreachable" } = [] {
		auto unhappy = false;

		// clang-format off
		try { expect_unreachable(); }
		catch (const std::exception &exp) { unhappy = true; }
		// clang-format on

		if (!unhappy)
		{
			throw std::runtime_error { "expect_unreachable" };
		}
	};

	Case { "expect_true - happy" } = [] {
		auto oongaboonga = int {};
		auto *oongaboonga_ptr_here = &oongaboonga;

		expect_true(oongaboonga_ptr_here);
		expect_true(true);
		expect_true(1); // NOLINT
	};

	Case { "expect_true - unhappy" } = [] {
		auto unhappy_counter = 0u;
		auto *where_oongaboonga_ptr = (int *)nullptr;

		// clang-format off
		try { expect_true(where_oongaboonga_ptr); }
        catch (const std::exception& exp) { ++unhappy_counter; }

		try { expect_true(!true); }
        catch (const std::exception& exp) { ++unhappy_counter; }

		try { expect_true(false); }
        catch (const std::exception& exp) { ++unhappy_counter; }

		try { expect_true(0); } // NOLINT
        catch (const std::exception& exp) { ++unhappy_counter; }
		// clang-format on
	};

	Case { "expect_false - happy" } = [] {
		auto *oongaboonga_is_slacking = (int *)nullptr;

		expect_false(oongaboonga_is_slacking);
		expect_false(false);
		expect_false(0); // NOLINT
	};

	Case { "expect_false - unhappy" } = [] {
		auto oongaboonga = int {};
		auto *oonga_oonga_can_rest_now = (int *)nullptr;
		auto unhappy_counter = 0u;

		// clang-format off
		try { expect_false(oonga_oonga_can_rest_now); }
        catch (const std::exception& exp) { ++unhappy_counter; }

		try { expect_false(true); }
        catch (const std::exception& exp) { ++unhappy_counter; }

		try { expect_false(!false); }
        catch (const std::exception& exp) { ++unhappy_counter; }

		try { expect_false(1);  } // NOLINT
        catch (const std::exception& exp) { ++unhappy_counter; }
		// clang-format on
	};

	Case { "expect_true - unhappy" } = [] {
		auto unhappy_counter = 0u;
		auto *where_oongaboonga_ptr = (int *)nullptr;

		// clang-format off
		try { expect_true(where_oongaboonga_ptr); }
        catch (const std::exception& exp) { ++unhappy_counter; }

		try { expect_true(!true); }
        catch (const std::exception& exp) { ++unhappy_counter; }

		try { expect_true(false); }
        catch (const std::exception& exp) { ++unhappy_counter; }

		try { expect_true(0); } // NOLINT
        catch (const std::exception& exp) { ++unhappy_counter; }
		// clang-format on
	};

	Case { "expect_eq - happy" } = [] {
		expect_eq(5, 5);
		expect_eq(20.0, 20.0);
		expect_eq(true, 1);
	};

	Case { "expect_eq - unhappy" } = [] {
		auto unhappy = false;

		// clang-format off
		try { expect_eq(true, false); }
		catch (const std::exception &exp) { unhappy = true; }
		// clang-format on

		if (!unhappy)
		{
			throw std::runtime_error { "expect_eq unhappy" };
		}
	};

	Case { "expect_ne - happy " } = [] {
		expect_ne(5, 5.0000001);
		expect_ne(20.0, 69.0);
		expect_ne(true, 0);
	};

	Case { "expect_ne - unhappy" } = [] {
		auto unhappy_counter = 0u;

		// clang-format off
		try { expect_ne(5, 5); }
		catch (const std::exception &exp) { ++unhappy_counter; }

		try { expect_ne(20.0, 20.0); }
		catch (const std::exception &exp) { ++unhappy_counter; }

		try { expect_ne(true, 1); }
		catch (const std::exception &exp) { ++unhappy_counter; }
		// clang-format on

		if (unhappy_counter != 3)
		{
			throw std::runtime_error { "expect_ne unhappy" };
		}
	};

	Case { "expect_throw - happy" } = [] {
		expect_throw([] { throw std::runtime_error { "nonsense" }; });
	};

	Case { "expect_throw - unhappy" } = [] {
		auto unhappy = false;

		// clang-format off
		try { expect_throw([] {}); }
		catch (const std::exception &exp) { unhappy = true; }
		// clang-format on

		if (!unhappy)
		{
			throw std::runtime_error { "expect_throw - unhappy" };
		}
	};

	Case { "expect_le - happy" } = [] {
		expect_le(69, 420);
		expect_le(19.694206942069420, 20.0);
		expect_le(false, 1);
	};

	Case { "expect_le - unhappy" } = [] {
		auto unhappy_counter = 0u;

		// clang-format off
		try { expect_le(20020619 + 23, 20020619 ); }
		catch (const std::exception &exp) { ++unhappy_counter; }

		try { expect_le(420, 69); }
		catch (const std::exception &exp) { ++unhappy_counter; }

		try { expect_le(20.0, 19.694206942069420); }
		catch (const std::exception &exp) { ++unhappy_counter; }

		try { expect_le(1, false); }
		catch (const std::exception &exp) { ++unhappy_counter; }
		// clang-format on

		if (unhappy_counter != 4)
		{
			throw std::runtime_error { "expect_le - unhappy" };
		}
	};
};
