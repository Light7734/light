import test;
import math.vec2;
import math.vec3;
import math.vec4;
import math.formatter;
import logger;

using vec2 = ::lt::math::vec2;
using vec3 = ::lt::math::vec3;
using vec4 = ::lt::math::vec4;
using ivec4 = ::lt::math::vec4_i32;

Suite raii = "vec4_raii"_suite = [] {
	Case { "happy paths" } = [] {
		ignore = vec4 {};
		ignore = vec4 { 2.0 };
		ignore = vec4 { 2.0, 4.0, 6.0, 8.0 };
		ignore = vec4 { vec2 { 2.0, 4.0 }, 6.0, 8.0 };
		ignore = vec4 { 2.0, 4.0, vec2 { 6.0, 8.0 } };
		ignore = vec4 { vec2 { 2.0, 4.0 }, vec2 { 6.0, 8.0 } };
		ignore = vec4 { vec3 { 2.0, 4.0, 6.0 }, 8.0 };
		ignore = vec4 { 2.0, vec3 { 4.0, 6.0, 8.0 } };
	};

	Case { "unhappy paths" } = [] {
	};

	Case { "many" } = [] {
		for (auto idx : std::views::iota(0, 1'000'000))
		{
			ignore = idx;
			ignore = vec4 {};
			ignore = vec4 { 2.0 };
			ignore = vec4 { 2.0, 4.0, 6.0, 8.0 };
			ignore = vec4 { vec2 { 2.0, 4.0 }, 6.0, 8.0 };
			ignore = vec4 { 2.0, 4.0, vec2 { 6.0, 8.0 } };
			ignore = vec4 { vec2 { 2.0, 4.0 }, vec2 { 6.0, 8.0 } };
			ignore = vec4 { vec3 { 2.0, 4.0, 6.0 }, 8.0 };
			ignore = vec4 { 2.0, vec3 { 4.0, 6.0, 8.0 } };
		}
	};

	Case { "post default construct has correct state" } = [] {
		const auto vec = vec4 {};
		expect_eq(vec.x, 0.0);
		expect_eq(vec.y, 0.0);
		expect_eq(vec.z, 0.0);
		expect_eq(vec.w, 0.0);
	};

	Case { "post scalar construct has correct state" } = [] {
		const auto vec = vec4 { 2.0 };
		expect_eq(vec.x, 2.0);
		expect_eq(vec.y, 2.0);
		expect_eq(vec.z, 2.0);
		expect_eq(vec.w, 2.0);
	};

	Case { "post construct with x,y,z,w has correct state" } = [] {
		const auto vec = vec4 { 1.0, 2.0, 3.0, 4.0 };
		expect_eq(vec.x, 1.0);
		expect_eq(vec.y, 2.0);
		expect_eq(vec.z, 3.0);
		expect_eq(vec.w, 4.0);
	};

	Case { "post construct with xy,z,w has correct state" } = [] {
		const auto vec = vec4 { vec2 { 1.0, 2.0 }, 3.0, 4.0 };
		expect_eq(vec.x, 1.0);
		expect_eq(vec.y, 2.0);
		expect_eq(vec.z, 3.0);
		expect_eq(vec.w, 4.0);
	};

	Case { "post construct with x,y,zw has correct state" } = [] {
		const auto vec = vec4 { 1.0, 2.0, vec2 { 3.0, 4.0 } };
		expect_eq(vec.x, 1.0);
		expect_eq(vec.y, 2.0);
		expect_eq(vec.z, 3.0);
		expect_eq(vec.w, 4.0);
	};

	Case { "post construct with x,yz,w has correct state" } = [] {
		const auto vec = vec4 { 1.0, vec2 { 2.0, 3.0 }, 4.0 };
		expect_eq(vec.x, 1.0);
		expect_eq(vec.y, 2.0);
		expect_eq(vec.z, 3.0);
		expect_eq(vec.w, 4.0);
	};

	Case { "post construct with x,y,zw has correct state" } = [] {
		const auto vec = vec4 { 1.0, 2.0, vec2 { 3.0, 4.0 } };
		expect_eq(vec.x, 1.0);
		expect_eq(vec.y, 2.0);
		expect_eq(vec.z, 3.0);
		expect_eq(vec.w, 4.0);
	};

	Case { "post construct with xy,zw has correct state" } = [] {
		const auto vec = vec4 { vec2 { 1.0, 2.0 }, vec2 { 3.0, 4.0 } };
		expect_eq(vec.x, 1.0);
		expect_eq(vec.y, 2.0);
		expect_eq(vec.z, 3.0);
		expect_eq(vec.w, 4.0);
	};

	Case { "post construct with xyz,w has correct state" } = [] {
		const auto vec = vec4 { vec3 { 1.0, 2.0, 3.0 }, 4.0 };
		expect_eq(vec.x, 1.0);
		expect_eq(vec.y, 2.0);
		expect_eq(vec.z, 3.0);
		expect_eq(vec.w, 4.0);
	};

	Case { "post construct with x,yzw has correct state" } = [] {
		const auto vec = vec4 { 1.0, vec3 { 2.0, 3.0, 4.0 } };
		expect_eq(vec.x, 1.0);
		expect_eq(vec.y, 2.0);
		expect_eq(vec.z, 3.0);
		expect_eq(vec.w, 4.0);
	};
};

Suite arithmetic_operators = "vec4_operators"_suite = [] {
	Case { "operator ==" } = [] {
		const auto lhs = vec4 { 1.0, 2.0, 3.0, 4.0 };

		expect_false(lhs == vec4 { {}, 2.0, 3.0, 4.0 });
		expect_false(lhs == vec4 { 1.0, {}, 3.0, 4.0 });
		expect_false(lhs == vec4 { 1.0, 2.0, {}, 4.0 });
		expect_false(lhs == vec4 { 1.0, 2.0, 3.0, {} });
		expect_true(lhs == vec4 { 1.0, 2.0, 3.0, 4.0 });
	};

	Case { "operator !=" } = [] {
		const auto lhs = vec4 { 1.0, 2.0, 3.0, 4.0 };

		expect_true(lhs != vec4 { {}, 2.0, 3.0, 4.0 });
		expect_true(lhs != vec4 { 1.0, {}, 3.0, 4.0 });
		expect_true(lhs != vec4 { 1.0, 2.0, {}, 4.0 });
		expect_true(lhs != vec4 { 1.0, 2.0, 3.0, {} });
		expect_false(lhs != vec4 { 1.0, 2.0, 3.0, 4.0 });
	};

	Case { "operator +" } = [] {
		const auto lhs = vec4 { 1.0, 2.0, 3.0, 4.0 };
		const auto rhs = vec4 { 5.0, 6.0, 7.0, 8.0 };
		expect_eq(lhs + rhs, vec4 { 6.0, 8.0, 10.0, 12.0 });
	};

	Case { "operator -" } = [] {
		const auto lhs = vec4 { 1.0, 2.0, 3.0, 4.0 };
		const auto rhs = vec4 { 5.0, 10.0, 15.0, 20.0 };
		expect_eq(lhs - rhs, vec4 { -4.0, -8.0, -12.0, -16.0 });
	};

	Case { "operator *" } = [] {
		const auto lhs = vec4 { 1.0, 2.0, 3.0, 4.0 };
		const auto rhs = vec4 { 5.0, 6.0, 7.0, 8.0 };
		expect_eq(lhs * rhs, vec4 { 5.0, 12.0, 21.0, 32.0 });
	};

	Case { "operator /" } = [] {
		const auto lhs = vec4 { 5.0, 6.0, 30.0, 8.0 };
		const auto rhs = vec4 { 1.0, 2.0, 3.0, 4.0 };
		expect_eq(lhs / rhs, vec4 { 5.0, 3.0, 10.0, 2.0 });
	};

	Case { "operator []" } = [] {
		auto vec = vec4 { 0.0, 1.0, 2.0, 3.0 };
		expect_eq(vec.x, 0.0);
		expect_eq(vec.y, 1.0);
		expect_eq(vec.z, 2.0);
		expect_eq(vec.w, 3.0);
	};

	Case { "operator [] const" } = [] {
		const auto vec = vec4 { 0.0, 1.0, 2.0, 3.0 };
		expect_eq(vec.x, 0.0);
		expect_eq(vec.y, 1.0);
		expect_eq(vec.z, 2.0);
		expect_eq(vec.w, 3.0);
	};
};

Suite utilities = "vec4_utilities"_suite = [] {
	Case { "std::format float" } = [] {
		auto str = std::format("{}", vec4 { 10.0000f, 30.0005f, 40.00005f, 0.0 });
		expect_eq(str, "10, 30.0005, 40.00005, 0");
	};

	Case { "std::format int" } = [] {
		auto str = std::format("{}", ivec4 { 10, 30, 3'000'000, 13 });
		expect_eq(str, "10, 30, 3000000, 13");
	};
};
