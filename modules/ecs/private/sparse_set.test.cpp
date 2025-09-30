#include <ecs/sparse_set.hpp>
#include <ranges>
#include <test/expects.hpp>
#include <test/test.hpp>

using lt::test::Case;
using lt::test::Suite;

using lt::test::expect_eq;
using lt::test::expect_false;
using lt::test::expect_ne;
using lt::test::expect_throw;
using lt::test::expect_true;

using Set = lt::ecs::SparseSet<int>;
constexpr auto capacity = 100;

Suite raii = "raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		std::ignore = Set {};
		std::ignore = Set { Set::max_capacity };
	};

	Case { "unhappy path throws" } = [] {
		expect_throw([] { std::ignore = Set { Set::max_capacity + 1 }; });
	};

	Case { "post construct has correct state" } = [&] {
		auto set = Set { capacity };
		expect_eq(set.get_size(), 0);
		expect_eq(set.get_capacity(), capacity);
	};
};

Suite element_raii = "element_raii"_suite = [] {
	Case { "many inserts/removes won't freeze/throw" } = [] {
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
			expect_throw([&] { std::ignore = set.at(idx); });
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
			expect_eq(identifier, value);
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

		set.insert(set.get_size(), {});
		expect_ne(set.get_capacity(), 10'000);
	};

	Case { "at throws with out of bound access" } = [] {
		auto set = Set {};

		for (auto idx : std::views::iota(0, 50))
		{
			expect_throw([&] {
				set.insert(idx, {});
				std::ignore = set.at(50);
			});
		}

		set.insert(50, {});
		std::ignore = set.at(50); // should not throw
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
	};
};
