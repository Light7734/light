import test;
import ecs.sparse_set;

using Value_T = i32;
using Set = lt::ecs::SparseSet<Value_T>;

constexpr auto capacity = 100;

Suite raii = "raii"_suite = [] {
	Case { "happy paths" } = [] {
		ignore = Set {};
		ignore = Set { Set::max_capacity };
	};

	Case { "unhappy paths" } = [] {
		expect_throw([] { ignore = Set { Set::max_capacity + 1 }; });
	};

	Case { "many" } = [] {
		for (auto idx : std::views::iota(0, 1'000))
		{
			ignore = Set { static_cast<size_t>(idx) };
		}
	};

	Case { "post construct has correct state" } = [&] {
		auto set = Set { capacity };
		expect_eq(set.get_size(), 0);
		expect_eq(set.get_capacity(), capacity);
	};
};

Suite element_raii = "element_raii"_suite = [] {
	Case { "happy paths" } = [] {
		auto set = Set { capacity };
		set.insert(0, {});
		set.remove(0);
	};

	Case { "unhappy paths" } = [] {
		expect_throw([] {
			auto set = Set { capacity };
			set.insert(Set::max_capacity + 1, {});
		});

		expect_throw([] {
			auto set = Set { capacity };
			set.insert(0, {});
			set.insert(1, {});
			set.insert(2, {});

			set.remove(3);
		});
	};

	Case { "many" } = [] {
		auto set = Set {};
		for (auto idx : std::views::iota(0, 10'000))
		{
			set.insert(idx, {});
		}

		for (auto idx : std::views::iota(0, 10'000))
		{
			set.remove(idx);
		}
	};

	Case { "insert returns reference to inserted value" } = [] {
		auto set = Set {};
		for (auto idx : std::views::iota(0, 10'000))
		{
			const auto val = Set::Dense_T { idx, {} };
			expect_eq(set.insert(val.first, val.second), val);
		}
	};

	Case { "post insert/remove has correct state" } = [] {
		auto set = Set {};
		for (auto idx : std::views::iota(0, 10'000))
		{
			set.insert(idx, idx * 2);
			expect_eq(set.get_size(), idx + 1);
			expect_eq(set.at(idx), Set::Dense_T { idx, idx * 2 });
			expect_true(set.contains(idx));
		}

		for (auto idx : std::views::iota(0, 10'000))
		{
			expect_eq(set.at(idx), Set::Dense_T { idx, idx * 2 });
			expect_true(set.contains(idx));
		}

		for (auto idx : std::views::iota(0, 10'000))
		{
			set.remove(idx);

			expect_eq(set.get_size(), 10'000 - (idx + 1));
			expect_false(set.contains(idx));
			expect_throw([&] { ignore = set.at(idx); });
		}
	};

	Case { "removed elements won't be iterated again" } = [] {
		auto set = Set {};

		for (auto idx : std::views::iota(0, 10'000))
		{
			set.insert(idx, idx);
		}

		set.remove(0);
		set.remove(32);
		set.remove(69);
		set.remove(420);
		set.remove(9'999);

		for (auto &[identifier, value] : set)
		{
			expect_eq(static_cast<Value_T>(identifier), value);
			expect_ne(value, 0);
			expect_ne(value, 32);
			expect_ne(value, 69);
			expect_ne(value, 420);
			expect_ne(value, 9'999);
		}
	};
};

Suite getters = "getters"_suite = [] {
	Case { "get_size returns correct values" } = [] {
		auto set = Set {};
		for (auto idx : std::views::iota(0, 10'000))
		{
			expect_eq(set.get_size(), idx);
			set.insert(idx, {});
		}

		expect_eq(set.get_size(), 10'000);
	};

	Case { "get_capacity returns correct values" } = [] {
		auto set = Set { 10'000 };
		for (auto idx : std::views::iota(0, 10'000))
		{
			expect_eq(set.get_capacity(), 10'000); // are we testing std::vector's implementation?
			set.insert(idx, {});
		}

		expect_eq(set.get_capacity(), 10'000);

		set.insert(static_cast<Value_T>(set.get_size()), {});
		expect_ne(set.get_capacity(), 10'000);
	};

	Case { "at throws with out of bound access" } = [] {
		auto set = Set {};

		for (auto idx : std::views::iota(0, 50))
		{
			expect_throw([&] {
				set.insert(idx, {});
				ignore = set.at(50);
			});
		}

		set.insert(50, {});
		ignore = set.at(50); // should not throw
	};
};

Suite clear = "clear"_suite = [] {
	Case { "post clear has correct state" } = [] {
		auto set = Set { 0 };
		for (auto idx : std::views::iota(0, 10'000))
		{
			set.insert(idx, {});
		}

		set.clear();
		expect_eq(set.get_size(), 0);

		for (auto idx : std::views::iota(0, 10'000))
		{
			expect_throw([&] { ignore = set.at(idx); });
		}
	};
};
