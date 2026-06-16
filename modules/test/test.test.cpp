import test;

Suite expects = "expects"_suite = []() {
	// should be truncated...
	Case { "berryyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy "
		   "long name" } = [] {
	};

	Case { "this emptiness machine" } = [] {
	};

	Case { "expect_unreachable" } = [] {
		auto unhappy = false;

		// clang-format off
		try { expect_unreachable(); }
		catch (const std::exception &) { unhappy = true; }
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
        catch (const std::exception&) { ++unhappy_counter; }

		try { expect_true(!true); }
        catch (const std::exception&) { ++unhappy_counter; }

		try { expect_true(false); }
        catch (const std::exception&) { ++unhappy_counter; }

		try { expect_true(0); } // NOLINT
        catch (const std::exception&) { ++unhappy_counter; }
		// clang-format on
	};

	Case { "expect_false - happy" } = [] {
		auto *oongaboonga_is_slacking = (int *)nullptr;

		expect_false(oongaboonga_is_slacking);
		expect_false(false);
	};

	Case { "expect_false - unhappy" } = [] {
		auto *oonga_oonga_can_rest_now = (u32 *)nullptr;
		auto unhappy_counter = 0u;
		oonga_oonga_can_rest_now = &unhappy_counter;

		// clang-format off
		try { expect_false(oonga_oonga_can_rest_now); }
        catch (const std::exception&) { ++unhappy_counter; }

		try { expect_false(true); }
        catch (const std::exception&) { ++unhappy_counter; }

		try { expect_false(!false); }
        catch (const std::exception&) { ++unhappy_counter; }

		try { expect_false(!!true);  }
        catch (const std::exception&) { ++unhappy_counter; }
		// clang-format on

		if (unhappy_counter != 4)
		{
			throw std::runtime_error { "expect_false - unhappy" };
		}
	};

	Case { "expect_true - unhappy" } = [] {
		auto unhappy_counter = 0u;
		auto *where_oongaboonga_ptr = (int *)nullptr;

		// clang-format off
		try { expect_true(where_oongaboonga_ptr); }
        catch (const std::exception&) { ++unhappy_counter; }

		try { expect_true(!true); }
        catch (const std::exception&) { ++unhappy_counter; }

		try { expect_true(false); }
        catch (const std::exception&) { ++unhappy_counter; }

		try { expect_true(!!false); } 
        catch (const std::exception&) { ++unhappy_counter; }
		// clang-format on

		if (unhappy_counter != 4)
		{
			throw std::runtime_error { "expect_true - unhappy" };
		}
	};

	Case { "expect_eq - happy" } = [] {
		expect_eq(5, 5);
		expect_eq(20.0, 20.0);
		expect_eq(true, true);
		expect_eq(false, false);
	};

	Case { "expect_eq - unhappy" } = [] {
		auto unhappy = false;

		// clang-format off
		try { expect_eq(true, false); }
		catch (const std::exception &) { unhappy = true; }
		// clang-format on

		if (!unhappy)
		{
			throw std::runtime_error { "expect_eq unhappy" };
		}
	};

	Case { "expect_ne - happy " } = [] {
		expect_ne(5, 5.0000001);
		expect_ne(20.0, 69.0);
		expect_ne(true, false);
		expect_ne(false, true);
	};

	Case { "expect_ne - unhappy" } = [] {
		auto unhappy_counter = 0u;

		// clang-format off
		try { expect_ne(5, 5); }
		catch (const std::exception &) { ++unhappy_counter; }

		try { expect_ne(20.0, 20.0); }
		catch (const std::exception &) { ++unhappy_counter; }

		try { expect_ne(true, true); }
		catch (const std::exception &) { ++unhappy_counter; }

		try { expect_ne(false, false); }
		catch (const std::exception &) { ++unhappy_counter; }
		// clang-format on

		if (unhappy_counter != 4)
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
		catch (const std::exception &) { unhappy = true; }
		// clang-format on

		if (!unhappy)
		{
			throw std::runtime_error { "expect_throw - unhappy" };
		}
	};

	Case { "expect_le - happy" } = [] {
		expect_le(69, 420);
		expect_le(19.694206942069420, 20.0);
		expect_le(false, !!true);
	};

	Case { "expect_le - unhappy" } = [] {
		auto unhappy_counter = 0u;

		// clang-format off
		try { expect_le(20020619 + 23, 20020619 ); }
		catch (const std::exception &) { ++unhappy_counter; }

		try { expect_le(420, 69); }
		catch (const std::exception &) { ++unhappy_counter; }

		try { expect_le(20.0, 19.694206942069420); }
		catch (const std::exception &) { ++unhappy_counter; }

		try { expect_le(true, false); }
		catch (const std::exception &) { ++unhappy_counter; }
		// clang-format on

		if (unhappy_counter != 4)
		{
			throw std::runtime_error { "expect_le - unhappy" };
		}
	};
};
