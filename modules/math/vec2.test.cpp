import test;
import math.vec2;

using vec2 = ::lt::math::vec2;
using ivec2 = ::lt::math::vec2_i32;

Suite static_tests = "vec3_static_checks"_suite = [] {
	constexpr auto num_elements = lt::math::vec2::num_elements;

	static_assert(num_elements == 2u);
	static_assert(std::is_same_v<lt::math::vec2, lt::math::vec2_f32>);

	static_assert(sizeof(lt::math::vec2_f32) == sizeof(f32) * num_elements);
	static_assert(sizeof(lt::math::vec2_f64) == sizeof(f64) * num_elements);

	static_assert(sizeof(lt::math::vec2_i8) == sizeof(i8) * num_elements);
	static_assert(sizeof(lt::math::vec2_i16) == sizeof(i16) * num_elements);
	static_assert(sizeof(lt::math::vec2_i32) == sizeof(i32) * num_elements);
	static_assert(sizeof(lt::math::vec2_i64) == sizeof(i64) * num_elements);

	static_assert(sizeof(lt::math::vec2_u8) == sizeof(u8) * num_elements);
	static_assert(sizeof(lt::math::vec2_u16) == sizeof(u16) * num_elements);
	static_assert(sizeof(lt::math::vec2_u32) == sizeof(u32) * num_elements);
	static_assert(sizeof(lt::math::vec2_u64) == sizeof(u64) * num_elements);
};

Suite raii = "vec2_raii"_suite = [] {
	Case { "happy paths" } = [] {
		ignore = vec2 {};
		ignore = vec2 { 2.0 };
		ignore = vec2 { 2.0, 4.0 };
	};

	Case { "unhappy paths" } = [] {
	};

	Case { "many" } = [] {
		for (auto idx : std::views::iota(0, 1'000'000))
		{
			ignore = idx;
			ignore = vec2 {};
			ignore = vec2 { 2.0 };
			ignore = vec2 { 2.0, 4.0 };
		}
	};

	Case { "post default construct has correct state" } = [] {
		const auto vec = vec2 {};
		expect_eq(vec.x, 0.0);
		expect_eq(vec.y, 0.0);
	};

	Case { "post scalar construct has correct state" } = [] {
		const auto vec = vec2 { 2.0 };
		expect_eq(vec.x, 2.0);
		expect_eq(vec.y, 2.0);
	};

	Case { "post construct with x,y has correct state" } = [] {
		const auto vec = vec2 { 2.0, 3.0 };
		expect_eq(vec.x, 2.0);
		expect_eq(vec.y, 3.0);
	};
};

Suite arithmetic_operators = "vec2_operators"_suite = [] {
	Case { "operator ==" } = [] {
		const auto lhs = vec2 { 1.0, 2.0 };

		expect_false(lhs == vec2 { {}, 2.0 });
		expect_false(lhs == vec2 { 1.0, {} });
		expect_true(lhs == vec2 { 1.0, 2.0 });
	};

	Case { "operator !=" } = [] {
		const auto lhs = vec2 { 1.0, 2.0 };

		expect_true(lhs != vec2 { {}, 2.0 });
		expect_true(lhs != vec2 { 1.0, {} });
		expect_false(lhs != vec2 { 1.0, 2.0 });
	};

	Case { "operator +" } = [] {
		const auto lhs = vec2 { 2.0, 3.0 };
		const auto rhs = vec2 { 4.0, 5.0 };
		expect_eq(lhs + rhs, vec2 { 6.0, 8.0 });
	};

	Case { "operator -" } = [] {
		const auto lhs = vec2 { 2.0, 3.0 };
		const auto rhs = vec2 { 4.0, 6.0 };
		expect_eq(lhs - rhs, vec2 { -2.0, -3.0 });
	};

	Case { "operator *" } = [] {
		const auto lhs = vec2 { 2.0, 3.0 };
		const auto rhs = vec2 { 10.0, 20.0 };
		expect_eq(lhs * rhs, vec2 { 20.0, 60.0 });
	};

	Case { "operator /" } = [] {
		const auto lhs = vec2 { 10.0, 20.0 };
		const auto rhs = vec2 { 2.0, 20.0 };
		expect_eq(lhs / rhs, vec2 { 5.0, 1.0 });
	};

	Case { "operator []" } = [] {
		auto vec = vec2 { 0.0, 1.0 };
		expect_eq(vec[0], 0.0);
		expect_eq(vec[1], 1.0);
	};

	Case { "operator [] const" } = [] {
		const auto vec = vec2 { 0.0, 1.0 };
		expect_eq(vec[0], 0.0);
		expect_eq(vec[1], 1.0);
	};
};

Suite utilities = "vec2_utilities"_suite = [] {
	Case { "std::format float" } = [] {
		auto str = std::format("{}", vec2 { 10.0000f, 30.0005f });
		expect_eq(str, "10, 30.0005");
	};

	Case { "std::format int" } = [] {
		auto str = std::format("{}", ivec2 { 10, 30 });
		expect_eq(str, "10, 30");
	};
};
