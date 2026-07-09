import test;

import memory.not_null;

using lt::memory::NotNull;

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

		auto not_null = NotNull<i32 *>(&value);
		expect_true(not_null.get() == &value);
	};

	Case { "constructing from a null raw pointer throws" } = [] {
		auto *null_ptr = (i32 *) { nullptr };
		expect_throw([&] { NotNull<i32 *> { null_ptr }; });
	};

	Case { "constructing from a null shared_ptr throws" } = [] {
		auto shared_ptr = std::shared_ptr<i32> {};
		expect_throw([&] { NotNull<std::shared_ptr<i32>> { shared_ptr }; });
	};

	Case { "exception carries a meaningful message" } = [] {
		auto *null_ptr = (i32 *) { nullptr };

		try
		{
			auto not_null = NotNull<i32 *> { null_ptr };
			expect_unreachable();
		}
		catch (const std::exception &exp)
		{
			expect_true(std::string(exp.what()).contains("nullptr"));
		}
	};

	/* Compile-time guarantees,
	 * checked via type traits rather than runtime behavior, since these are meant to be *compile*
	 * errors
	 */
	Case { "nullptr_t is rejected at compile time, not just at runtime" } = [] {
		expect_false(std::is_constructible_v<NotNull<i32 *>, std::nullptr_t>);
		expect_false(std::is_assignable_v<NotNull<i32 *> &, std::nullptr_t>);
	};

	Case { "there is no default constructor" } = [] {
		expect_false(std::is_default_constructible_v<NotNull<i32 *>>);
	};
};

Suite access_and_conversion = "access and conversion"_suite = [] {
	Case { "implicit conversion back to T works" } = [] {
		auto value = i32 { 7 };
		auto not_null = NotNull<i32 *> { &value };

		expect_true((i32 *) { not_null } == &value);
	};

	Case { "passing NotNull where a raw T parameter is expected" } = [] {
		auto value = i32 { 9 };
		auto not_null = NotNull<i32 *> { &value };

		constexpr auto takes_raw = [](const i32 *p) -> i32 {
			return *p;
		};

		expect_true(takes_raw(not_null) == 9);
	};

	Case { "contextual boolean conversion is always true for a valid NotNull" } = [] {
		auto value = i32 { 1 };
		auto not_null = NotNull<i32 *> { &value };

		expect_true(static_cast<bool>(not_null));
	};

	Case { "operator-> forwards member access" } = [] {
		auto widget = Widget {};

		auto not_null = NotNull<Widget *> { &widget };
		expect_true(not_null->get_value() == 42);

		not_null->set_value(100);
		expect_true(widget.value == 100);
	};

	Case { "operator* dereferences to the pointee and allows mutation" } = [] {
		auto value = i32 { 3 };

		auto not_null = NotNull<i32 *> { &value };
		expect_true(*not_null == 3);

		*not_null = 10;
		expect_true(value == 10);
	};

	Case { "const NotNull objects remain fully usable" } = [] {
		auto widget = Widget {};

		const auto not_null = NotNull<Widget *> { &widget };
		expect_true(not_null->get_value() == 42);
		expect_true((*not_null).value == 42);

		auto *raw_ptr = (Widget *) { not_null };
		expect_true(raw_ptr == &widget);
	};
};

Suite copy_move_assignment = "copy, move, and assigment"_suite = [] {
	Case { "copy construction and copy assignment preserve the pointee" } = [] {
		auto value_a_b = i32 { 1 };

		auto ptr_a = NotNull<i32 *>(&value_a_b);
		auto ptr_b = NotNull<i32 *>(ptr_a);
		expect_true(ptr_b.get() == &value_a_b);

		auto value_c = i32 { 2 };
		auto c = NotNull<i32 *> { &value_c };

		c = ptr_a;
		expect_true(c.get() == &value_a_b);
	};

	Case { "assigning a raw pointer goes through the validating constructor" } = [] {
		auto value_a = i32 { 1 };
		auto value_b = i32 { 2 };

		auto not_null = NotNull<i32 *> { &value_a };

		not_null = &value_b; // implicit conversion + assignment
		expect_true(not_null.get() == &value_b);

		auto *null_ptr = (i32 *) { nullptr };
		expect_throw([&] { not_null = null_ptr; });
		expect_true(not_null.get() == &value_b); // failed assignment must not have side effects
	};

	Case { "move construction and move assignment compile for move-only T" } = [] {
		auto unique_ptr = std::make_unique<i32>(55);
		auto ptr_a = NotNull<std::unique_ptr<i32>> { std::move(unique_ptr) };

		auto new_unique_ptr = std::make_unique<i32>(56);
		auto ptr_b = NotNull<std::unique_ptr<i32>>(std::move(new_unique_ptr));

		auto ptr_c = NotNull<std::unique_ptr<i32>>(std::move(ptr_b));
		expect_eq(*ptr_c.get_by_ref(), 56);

		// IMPORTANT:
		// `ptr_b` is left wrapping a moved-from (null) unique_ptr here. NotNull only checks its
		// invariant at construction time, so this is a real sharp edge with move-only T!
		(void)ptr_b; // NOLINT(bugprone-use-after-move)
	};
};

Suite comparisons = "comparisons"_suite = [] {
	Case { "equality and inequality compare the underlying pointee" } = [] {
		auto value_a_b = i32 { 1 };
		auto value_c = i32 { 2 };

		auto ptr_a = NotNull<i32 *> { &value_a_b };
		auto ptr_b = NotNull<i32 *> { &value_a_b };

		auto ptr_c = NotNull<i32 *> { &value_c };

		expect_true(ptr_a == ptr_b);
		expect_false(ptr_a != ptr_b);

		expect_true(ptr_a != ptr_c);
		expect_false(ptr_a == ptr_c);
	};

	Case { "comparison works across related but distinct pointer types" } = [] {
		auto value = i32 { 1 };

		auto lhs = NotNull<i32 *> { &value };
		auto rhs = NotNull<const i32 *> { &value };

		expect_true(lhs == rhs);
	};
};


Suite pointers_and_containers = "interop with smart pointers and containers"_suite = [] {
	Case { "works with shared_ptr, including operator-> chaining" } = [] {
		auto shared_ptr = std::make_shared<Widget>();
		auto not_null = NotNull<std::shared_ptr<Widget>> { shared_ptr };

		expect_true(not_null->get_value() == 42);
		// use_count is 3, not 2: sp + nn's internal copy + the temporary that
		// get() itself returns by value (another consequence of accessors
		// returning T by value instead of by reference).
		expect_true(not_null.get().use_count() == 3);
		not_null->set_value(7);
		expect_true(shared_ptr->value == 7);
	};

	Case { "can be stored in standard containers" } = [] {
		std::array<i32, 3> nums = { 1, 2, 3 };
		auto vec = std::vector<NotNull<i32 *>> {};

		vec.push_back(NotNull<i32 *>(&nums[0])); // NOLINT(modernize-use-emplace)
		vec.push_back(NotNull<i32 *>(&nums[1])); // NOLINT(modernize-use-emplace)
		vec.emplace_back(&nums[2]);

		expect_true(vec.size() == 3);
		expect_true(*vec[0] == 1);
		expect_true(*vec[1] == 2);
		expect_true(*vec[2] == 3);
	};
};
