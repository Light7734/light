import test;
import math.vec2;
import math.vec3;
import math.formatter;

using vec2 = ::lt::math::vec2;
using vec3 = ::lt::math::vec3;
using ivec3 = ::lt::math::vec3_i32;

Suite raii = "vec3_raii"_suite = [] {
	Case { "happy paths" } = [] {
		ignore = vec3 {};
		ignore = vec3 { 2.0 };
		ignore = vec3 { 2.0, 4.0, 6.0 };
		ignore = vec3 { vec2 { 2.0, 4.0 }, 6.0 };
		ignore = vec3 { 2.0, vec2 { 4.0, 6.0 } };
	};

	Case { "unhappy paths" } = [] {
	};

	Case { "many" } = [] {
		for (auto idx : std::views::iota(0, 1'000'000))
		{
			ignore = idx;
			ignore = vec3 {};
			ignore = vec3 { 2.0 };
			ignore = vec3 { 2.0, 4.0, 6.0 };
			ignore = vec3 { vec2 { 2.0, 4.0 }, 6.0 };
			ignore = vec3 { 2.0, vec2 { 4.0, 6.0 } };
		}
	};

	Case { "post default construct has correct state" } = [] {
		const auto vec = vec3 {};
		expect_eq(vec.x, 0.0);
		expect_eq(vec.y, 0.0);
		expect_eq(vec.z, 0.0);
	};

	Case { "post scalar construct has correct state" } = [] {
		const auto vec = vec3 { 2.0 };
		expect_eq(vec.x, 2.0);
		expect_eq(vec.y, 2.0);
		expect_eq(vec.z, 2.0);
	};

	Case { "post construct with x,y,z has correct state" } = [] {
		const auto vec = vec3 { 1.0, 2.0, 3.0 };
		expect_eq(vec.x, 1.0);
		expect_eq(vec.y, 2.0);
		expect_eq(vec.z, 3.0);
	};

	Case { "post construct with xy,z has correct state" } = [] {
		const auto vec = vec3 { vec2 { 1.0, 2.0 }, 3.0 };
		expect_eq(vec.x, 1.0);
		expect_eq(vec.y, 2.0);
		expect_eq(vec.z, 3.0);
	};

	Case { "post construct with x,yz has correct state" } = [] {
		const auto vec = vec3 { 1.0, vec2 { 2.0, 3.0 } };
		expect_eq(vec.x, 1.0);
		expect_eq(vec.y, 2.0);
		expect_eq(vec.z, 3.0);
	};
};

Suite arithmetic_operators = "vec3_operators"_suite = [] {
	Case { "operator ==" } = [] {
		const auto lhs = vec3 { 1.0, 2.0, 3.0 };

		expect_false(lhs == vec3 { {}, 2.0, 3.0 });
		expect_false(lhs == vec3 { 1.0, {}, 3.0 });
		expect_false(lhs == vec3 { 1.0, 2.0, {} });
		expect_true(lhs == vec3 { 1.0, 2.0, 3.0 });
	};

	Case { "operator !=" } = [] {
		const auto lhs = vec3 { 1.0, 2.0, 3.0 };

		expect_true(lhs != vec3 { {}, 2.0, 3.0 });
		expect_true(lhs != vec3 { 1.0, {}, 3.0 });
		expect_true(lhs != vec3 { 1.0, 2.0, {} });
		expect_false(lhs != vec3 { 1.0, 2.0, 3.0 });
	};

	Case { "operator +" } = [] {
		const auto lhs = vec3 { 1.0, 2.0, 3.0 };
		const auto rhs = vec3 { 4.0, 5.0, 6.0 };
		expect_eq(lhs + rhs, vec3 { 5.0, 7.0, 9.0 });
	};

	Case { "operator -" } = [] {
		const auto lhs = vec3 { 1.0, 2.0, 3.0 };
		const auto rhs = vec3 { 4.0, 5.0, 7.0 };
		expect_eq(lhs - rhs, vec3 { -3.0, -3.0, -4.0 });
	};

	Case { "operator *" } = [] {
		const auto lhs = vec3 { 1.0, 2.0, 3.0 };
		const auto rhs = vec3 { 4.0, 5.0, 6.0 };
		expect_eq(lhs * rhs, vec3 { 4.0, 10.0, 18.0 });
	};

	Case { "operator /" } = [] {
		const auto lhs = vec3 { 4.0, 10.0, 30.0 };
		const auto rhs = vec3 { 1.0, 2.0, 5.0 };
		expect_eq(lhs / rhs, vec3 { 4.0, 5.0, 6.0 });
	};

	Case { "operator []" } = [] {
		auto vec = vec3 { 0.0, 1.0, 2.0 };
		expect_eq(vec.x, 0.0);
		expect_eq(vec.y, 1.0);
		expect_eq(vec.z, 2.0);
	};

	Case { "operator [] const" } = [] {
		const auto vec = vec3 { 0.0, 1.0, 2.0 };
		expect_eq(vec.x, 0.0);
		expect_eq(vec.y, 1.0);
		expect_eq(vec.z, 2.0);
	};
};

Suite utilities = "vec3_utilities"_suite = [] {
	Case { "std::format float" } = [] {
		auto str = std::format("{}", vec3 { 10.0000f, 30.0005f, 40.00005f });
		expect_eq(str, "10, 30.0005, 40.00005");
	};

	Case { "std::format int" } = [] {
		auto str = std::format("{}", ivec3 { 10, 30, 3'000'000 });
		expect_eq(str, "10, 30, 3000000");
	};
};
