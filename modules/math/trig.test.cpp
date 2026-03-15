#include <numbers>

import test;
import math.trig;

Suite conversions = "trig_conversions"_suite = [] {
	using ::lt::math::to_degrees;
	using ::lt::math::to_radians;

	Case { "to_radians <f32>" } = [] {
		expect_eq(to_radians(f32 { 0.0f }), f32 { 0.0f });
		expect_eq(to_radians(f32 { 90.0f }), f32 { 1.5707963267948966f });
		expect_eq(to_radians(f32 { 180.0f }), std::numbers::pi_v<f32>);
		expect_eq(to_radians(f32 { 360.0f }), f32 { 6.2831853071795864f });
	};

	Case { "to_radians <f64>" } = [] {
		expect_eq(to_radians(f64 { 0.0 }), f64 { 0.0 });
		expect_eq(to_radians(f64 { 90.0 }), f64 { 1.5707963267948966 });
		expect_eq(to_radians(f64 { 180.0 }), std::numbers::pi);
		expect_eq(to_radians(f64 { 360.0 }), f64 { 6.2831853071795864 });
	};

	Case { "to_degrees <f32>" } = [] {
		expect_eq(to_degrees(f32 { 0.0f }), f32 { 0.0f });
		expect_eq(to_degrees(f32 { 1.5707963267948966f }), f32 { 90.0f });
		expect_eq(to_degrees(std::numbers::pi_v<f32>), f32 { 180.0f });
		expect_eq(to_degrees(f32 { 6.2831853071795864f }), f32 { 360.0f });
	};

	Case { "to_degrees <f64>" } = [] {
		expect_eq(to_degrees(f64 { 0.0 }), f64 { 0.0 });
		expect_eq(to_degrees(f64 { 1.5707963267948966 }), f64 { 90.0 });
		expect_eq(to_degrees(std::numbers::pi), f64 { 180.0 });
		expect_eq(to_degrees(f64 { 6.2831853071795864 }), f64 { 360.0 });
	};

	Case { "to_degrees -> to_radians -> to_degrees <f32>" } = [] {
		expect_eq(to_degrees(to_radians(f32 { 45.0f })), f32 { 45.0f });
	};

	Case { "to_degrees -> to_radians -> to_degrees <f64>" } = [] {
		expect_eq(to_degrees(to_radians(f64 { 45.0 })), f64 { 45.0 });
	};
};
