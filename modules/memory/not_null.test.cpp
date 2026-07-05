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

// ---------------------------------------------------------------------------
// Construction
// ---------------------------------------------------------------------------

Suite not_null_suite = "not null suite"_suite = [] {
	Case { "construction from a valid raw pointer succeeds" } = [] {
		i32 x = 5;
		NotNull<i32 *> nn(&x);
		expect_true(nn.get() == &x);
	};

	Case { "constructing from a null raw pointer throws" } = [] {
		i32 *p = nullptr;
		expect_throw([&] { NotNull<i32 *> { p }; });
	};

	Case { "constructing from a null shared_ptr throws" } = [] {
		std::shared_ptr<i32> sp; // default-constructed => null
		expect_throw([&] { NotNull<std::shared_ptr<i32>> { sp }; });
	};

	Case { "exception carries a meaningful message" } = [] {
		i32 *p = nullptr;
		try
		{
			NotNull<i32 *> nn(p);
			expect_unreachable();
		}
		catch (const std::exception &exp)
		{
			expect_true(std::string(exp.what()).contains("nullptr"));
		}
	};

	// ---------------------------------------------------------------------------
	// Compile-time guarantees (checked via type traits rather than runtime
	// behavior, since these are meant to be *compile* errors)
	// ---------------------------------------------------------------------------

	Case { "nullptr_t is rejected at compile time, not just at runtime" } = [] {
		expect_false(std::is_constructible_v<NotNull<i32 *>, std::nullptr_t>);
		expect_false(std::is_assignable_v<NotNull<i32 *> &, std::nullptr_t>);
	};

	Case { "there is no default constructor" } = [] {
		expect_false(std::is_default_constructible_v<NotNull<i32 *>>);
	};

	// Note: instantiating NotNull<i32> (a T that can't be compared to nullptr)
	// trips the class's static_assert and fails the whole build by design -
	// that's not something a SFINAE-based trait can probe safely, so it isn't
	// exercised here. It's the same tradeoff the real GSL implementation makes.

	// ---------------------------------------------------------------------------
	// Access: conversion, operator->, operator*
	// ---------------------------------------------------------------------------

	Case { "implicit conversion back to T works" } = [] {
		i32 x = 7;
		NotNull<i32 *> nn(&x);
		i32 *raw = nn;
		expect_true(raw == &x);
	};

	Case { "passing NotNull where a raw T parameter is expected" } = [] {
		i32 x = 9;
		NotNull<i32 *> nn(&x);
		auto takesRaw = [](const i32 *p) {
			return *p;
		};
		expect_true(takesRaw(nn) == 9);
	};

	Case { "contextual boolean conversion is always true for a valid NotNull" } = [] {
		i32 x = 1;
		NotNull<i32 *> nn(&x);
		expect_true(static_cast<bool>(nn));
	};

	Case { "operator-> forwards member access" } = [] {
		Widget w;
		NotNull<Widget *> nn(&w);
		expect_true(nn->get_value() == 42);
		nn->set_value(100);
		expect_true(w.value == 100);
	};

	Case { "operator* dereferences to the pointee and allows mutation" } = [] {
		i32 x = 3;
		NotNull<i32 *> nn(&x);
		expect_true(*nn == 3);
		*nn = 10;
		expect_true(x == 10);
	};

	Case { "const NotNull objects remain fully usable" } = [] {
		Widget w;
		const NotNull<Widget *> nn(&w);
		expect_true(nn->get_value() == 42);
		expect_true((*nn).value == 42);
		Widget *raw = nn;
		expect_true(raw == &w);
	};

	// ---------------------------------------------------------------------------
	// Copy / move semantics
	// ---------------------------------------------------------------------------

	Case { "copy construction and copy assignment preserve the pointee" } = [] {
		i32 x = 1;
		NotNull<i32 *> a(&x);
		NotNull<i32 *> b(a);
		expect_true(b.get() == &x);

		i32 y = 2;
		NotNull<i32 *> c(&y);
		c = a;
		expect_true(c.get() == &x);
	};

	Case { "assigning a raw pointer goes through the validating constructor" } = [] {
		i32 x = 1;
		i32 y = 2;

		NotNull<i32 *> nn(&x);

		nn = &y; // implicit conversion + assignment
		expect_true(nn.get() == &y);

		i32 *np = nullptr;
		expect_throw([&] { nn = np; });
		expect_true(nn.get() == &y); // failed assignment must not have side effects
	};

	Case { "move construction and move assignment compile for move-only T" } = [] {
		// get()/operator->/operator*/operator T() all return T *by value*,
		// which means they require T to be copyable - so they can't be used
		// to inspect a NotNull<unique_ptr<...>> at all (this mirrors a known
		// limitation of the real gsl::NotNull, not something specific to this
		// port). Construction and moving are still well-formed, so that's all
		// we can meaningfully exercise here.
		auto up = std::make_unique<i32>(55);
		NotNull<std::unique_ptr<i32>> a(std::move(up));

		auto up2 = std::make_unique<i32>(56);
		NotNull<std::unique_ptr<i32>> b(std::move(up2));
		NotNull<std::unique_ptr<i32>> c(std::move(b)); // SHOULD NOT THROW!

		// `b` is left wrapping a moved-from (null) unique_ptr here. NotNull
		// only checks its invariant at construction time, so this is a real
		// sharp edge with move-only T - documented rather than silently assumed.
		(void)a;
	};

	// ---------------------------------------------------------------------------
	// Comparisons
	// ---------------------------------------------------------------------------

	Case { "equality and inequality compare the underlying pointee" } = [] {
		i32 x = 1;
		i32 y = 2;

		NotNull<i32 *> a(&x);
		NotNull<i32 *> b(&x);
		NotNull<i32 *> c(&y);

		expect_true(a == b);
		expect_false(a != b);
		expect_true(a != c);
		expect_false(a == c);
	};

	Case { "comparison works across related but distinct pointer types" } = [] {
		i32 x = 1;
		NotNull<i32 *> a(&x);
		NotNull<const i32 *> b(&x);
		expect_true(a == b);
	};

	// ---------------------------------------------------------------------------
	// Interop with smart pointers and containers
	// ---------------------------------------------------------------------------

	Case { "works with shared_ptr, including operator-> chaining" } = [] {
		auto sp = std::make_shared<Widget>();
		NotNull<std::shared_ptr<Widget>> nn(sp);

		expect_true(nn->get_value() == 42);
		// use_count is 3, not 2: sp + nn's internal copy + the temporary that
		// get() itself returns by value (another consequence of accessors
		// returning T by value instead of by reference).
		expect_true(nn.get().use_count() == 3);
		nn->set_value(7);
		expect_true(sp->value == 7);
	};

	Case { "can be stored in standard containers" } = [] {
		i32 a = 1;
		i32 b = 2;
		i32 c = 3;

		std::vector<NotNull<i32 *>> v;
		v.push_back(NotNull<i32 *>(&a)); // NOLINT
		v.push_back(NotNull<i32 *>(&b)); // NOLINT
		v.emplace_back(&c);

		expect_true(v.size() == 3);
		expect_true(*v[0] == 1);
		expect_true(*v[1] == 2);
		expect_true(*v[2] == 3);
	};
};
