import test;

import preliminary;

struct Widget
{
	i32 value = 42;

	[[nodiscard]] auto get_value() const -> i32
	{
		return value;
	}

	void set_value(i32 v)
	{
		value = v;
	}
};

Suite raii = "raii"_suite = [] {
	Case { "construction from a valid raw pointer succeeds" } = [] {
		auto value = i32 { 5 };

		auto nonull = not_null<i32 *>(&value);
		expect_eq(nonull.get(), &value);
	};

	Case { "constructing from a null raw pointer throws" } = [] {
		auto *null_ptr = (i32 *) { nullptr };
		expect_throw([&] { not_null<i32 *> { null_ptr }; });
	};

	Case { "constructing from a null shared_ptr throws" } = [] {
		auto shared_ptr = std::shared_ptr<i32> {};
		expect_throw([&] { not_null<std::shared_ptr<i32>> { shared_ptr }; });
	};

	Case { "exception carries a meaningful message" } = [] {
		auto *null_ptr = (i32 *) { nullptr };

		try
		{
			auto nonull = not_null<i32 *> { null_ptr };
			expect_unreachable();
		}
		catch (const std::exception &exp)
		{
			expect_str_contains(exp.what(), "nullptr");
		}
	};

	/* Compile-time guarantees,
	 * checked via type traits rather than runtime behavior, since these are meant to be *compile*
	 * errors
	 */
	Case { "nullptr_t is rejected at compile time, not just at runtime" } = [] {
		static_assert(!(std::is_constructible_v<not_null<i32 *>, std::nullptr_t>));
		static_assert(!(std::is_assignable_v<not_null<i32 *> &, std::nullptr_t>));
	};

	Case { "there is no default constructor" } = [] {
		static_assert(!(std::is_default_constructible_v<not_null<i32 *>>));
	};
};

Suite access_and_conversion = "access and conversion"_suite = [] {
	Case { "implicit conversion back to T works" } = [] {
		auto value = i32 { 7 };
		auto nonull = not_null<i32 *> { &value };

		expect_eq((i32 *) { nonull }, &value);
	};

	Case { "passing not_null where a raw T parameter is expected" } = [] {
		auto value = i32 { 9 };
		auto nonull = not_null<i32 *> { &value };

		constexpr auto takes_raw = [](const i32 *p) -> i32 {
			return *p;
		};

		expect_eq(takes_raw(nonull), 9);
	};

	Case { "contextual boolean conversion is always true for a valid not_null" } = [] {
		auto value = i32 { 1 };
		auto nonull = not_null<i32 *> { &value };

		expect_true(static_cast<bool>(nonull));
	};

	Case { "operator-> forwards member access" } = [] {
		auto widget = Widget {};

		auto nonull = not_null<Widget *> { &widget };
		expect_eq(nonull->get_value(), 42);

		nonull->set_value(100);
		expect_eq(widget.value, 100);
	};

	Case { "operator* dereferences to the pointee and allows mutation" } = [] {
		auto value = i32 { 3 };

		auto nonull = not_null<i32 *> { &value };
		expect_eq(*nonull, 3);

		*nonull = 10;
		expect_eq(value, 10);
	};

	Case { "const not_null objects remain fully usable" } = [] {
		auto widget = Widget {};

		const auto nonull = not_null<Widget *> { &widget };
		expect_eq(nonull->get_value(), 42);
		expect_eq((*nonull).value, 42);

		auto *raw_ptr = (Widget *) { nonull };
		expect_eq(raw_ptr, &widget);
	};
};

Suite copy_move_assignment = "copy, move, and assigment"_suite = [] {
	Case { "copy construction and copy assignment preserve the pointee" } = [] {
		auto value_a_b = i32 { 1 };

		auto ptr_a = not_null<i32 *>(&value_a_b);
		auto ptr_b = not_null<i32 *>(ptr_a);
		expect_eq(ptr_b.get(), &value_a_b);

		auto value_c = i32 { 2 };
		auto c = not_null<i32 *> { &value_c };

		c = ptr_a;
		expect_eq(c.get(), &value_a_b);
	};

	Case { "move construction and move assignment compile for move-only T" } = [] {
		auto unique_ptr = std::make_unique<i32>(55);
		auto ptr_a = not_null<std::unique_ptr<i32>> { std::move(unique_ptr) };

		auto new_unique_ptr = std::make_unique<i32>(56);
		auto ptr_b = not_null<std::unique_ptr<i32>>(std::move(new_unique_ptr));

		auto ptr_c = not_null<std::unique_ptr<i32>>(std::move(ptr_b));
		expect_eq(*ptr_c.get(), 56);
	};
};

Suite comparisons = "comparisons"_suite = [] {
	Case { "equality and inequality compare the underlying pointee" } = [] {
		auto value_a_b = i32 { 1 };
		auto value_c = i32 { 2 };

		auto ptr_a = not_null<i32 *> { &value_a_b };
		auto ptr_b = not_null<i32 *> { &value_a_b };

		auto ptr_c = not_null<i32 *> { &value_c };

		expect_true(ptr_a == ptr_b);
		expect_false(ptr_a != ptr_b);

		expect_true(ptr_a != ptr_c);
		expect_false(ptr_a == ptr_c);
	};

	Case { "comparison works across related but distinct pointer types" } = [] {
		auto value = i32 { 1 };

		auto lhs = not_null<i32 *> { &value };
		auto rhs = not_null<const i32 *> { &value };

		expect_true(lhs == rhs);
	};
};


Suite pointers_and_containers = "interop with smart pointers and containers"_suite = [] {
	Case { "works with shared_ptr, including operator-> chaining" } = [] {
		auto shared_ptr = std::make_shared<Widget>();
		auto nonull = not_null<std::shared_ptr<Widget>> { shared_ptr };

		expect_eq(nonull->get_value(), 42);
		expect_eq(nonull.get().use_count(), 2);
		nonull->set_value(7);
		expect_eq(shared_ptr->value, 7);
	};

	Case { "can be stored in standard containers" } = [] {
		std::array<i32, 3> nums = { 1, 2, 3 };
		auto vec = std::vector<not_null<i32 *>> {};

		vec.push_back(not_null<i32 *>(&nums[0])); // NOLINT(modernize-use-emplace)
		vec.push_back(not_null<i32 *>(&nums[1])); // NOLINT(modernize-use-emplace)
		vec.emplace_back(&nums[2]);

		expect_eq(vec.size(), 3);
		expect_eq(*vec[0], 1);
		expect_eq(*vec[1], 2);
		expect_eq(*vec[2], 3);
	};
};
