import test;
import math.vec3;
import math.mat4;

using vec3 = ::lt::math::vec3;
using mat4 = ::lt::math::mat4;

Suite static_tests = "mat4_static_checks"_suite = [] {
	constexpr auto num_elements = lt::math::mat4::num_elements;

	static_assert(num_elements == 4u * 4u);
	static_assert(std::is_same_v<lt::math::mat4, lt::math::mat4_f32>);

	static_assert(sizeof(lt::math::mat4_f32) == sizeof(f32) * num_elements);
	static_assert(sizeof(lt::math::mat4_f64) == sizeof(f64) * num_elements);

	static_assert(sizeof(lt::math::mat4_i8) == sizeof(i8) * num_elements);
	static_assert(sizeof(lt::math::mat4_i16) == sizeof(i16) * num_elements);
	static_assert(sizeof(lt::math::mat4_i32) == sizeof(i32) * num_elements);
	static_assert(sizeof(lt::math::mat4_i64) == sizeof(i64) * num_elements);

	static_assert(sizeof(lt::math::mat4_u8) == sizeof(u8) * num_elements);
	static_assert(sizeof(lt::math::mat4_u16) == sizeof(u16) * num_elements);
	static_assert(sizeof(lt::math::mat4_u32) == sizeof(u32) * num_elements);
	static_assert(sizeof(lt::math::mat4_u64) == sizeof(u64) * num_elements);
};

Suite raii = "mat4_raii"_suite = [] {
	Case { "happy paths" } = [] {
		ignore = mat4 {};
		ignore = mat4 { 1.0 };
		ignore = mat4 {
			1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
		};
		ignore = mat4 {
			mat4::Column_T { 1.0, 2.0, 3.0, 4.0 },
			mat4::Column_T { 5.0, 6.0, 7.0, 8.0 },
			mat4::Column_T { 9.0, 10.0, 11.0, 12.0 },
			mat4::Column_T { 13.0, 14.0, 15.0, 16.0 },
		};
	};

	Case { "unhappy paths" } = [] {
	};

	Case { "many" } = [] {
		for (auto idx : std::views::iota(0, 1'000'000))
		{
			ignore = idx;
			ignore = mat4 {};
			ignore = mat4 { 1.0 };
			ignore = mat4 {
				1.0, 2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
				9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
			};
			ignore = mat4 {
				mat4::Column_T { 1.0, 2.0, 3.0, 4.0 },
				mat4::Column_T { 5.0, 6.0, 7.0, 8.0 },
				mat4::Column_T { 9.0, 10.0, 11.0, 12.0 },
				mat4::Column_T { 13.0, 14.0, 15.0, 16.0 },
			};
		}
	};

	Case { "post default construct has correct state" } = [] {
		const auto [x, y, z, w] = mat4 {}.values;

		expect_eq(x[0], mat4::Underlying_T {});
		expect_eq(x[1], mat4::Underlying_T {});
		expect_eq(x[2], mat4::Underlying_T {});
		expect_eq(x[3], mat4::Underlying_T {});

		expect_eq(y[0], mat4::Underlying_T {});
		expect_eq(y[1], mat4::Underlying_T {});
		expect_eq(y[2], mat4::Underlying_T {});
		expect_eq(y[3], mat4::Underlying_T {});

		expect_eq(z[0], mat4::Underlying_T {});
		expect_eq(z[1], mat4::Underlying_T {});
		expect_eq(z[2], mat4::Underlying_T {});
		expect_eq(z[3], mat4::Underlying_T {});

		expect_eq(w[0], mat4::Underlying_T {});
		expect_eq(w[1], mat4::Underlying_T {});
		expect_eq(w[2], mat4::Underlying_T {});
		expect_eq(w[3], mat4::Underlying_T {});
	};

	Case { "post scalar construct has correct state" } = [] {
		const auto [x, y, z, w] = mat4 { 69.0 }.values;

		expect_eq(x[0], mat4::Underlying_T { 69.0 });
		expect_eq(x[1], mat4::Underlying_T { 69.0 });
		expect_eq(x[2], mat4::Underlying_T { 69.0 });
		expect_eq(x[3], mat4::Underlying_T { 69.0 });

		expect_eq(y[0], mat4::Underlying_T { 69.0 });
		expect_eq(y[1], mat4::Underlying_T { 69.0 });
		expect_eq(y[2], mat4::Underlying_T { 69.0 });
		expect_eq(y[3], mat4::Underlying_T { 69.0 });

		expect_eq(z[0], mat4::Underlying_T { 69.0 });
		expect_eq(z[1], mat4::Underlying_T { 69.0 });
		expect_eq(z[2], mat4::Underlying_T { 69.0 });
		expect_eq(z[3], mat4::Underlying_T { 69.0 });

		expect_eq(w[0], mat4::Underlying_T { 69.0 });
		expect_eq(w[1], mat4::Underlying_T { 69.0 });
		expect_eq(w[2], mat4::Underlying_T { 69.0 });
		expect_eq(w[3], mat4::Underlying_T { 69.0 });
	};

	Case { "post construct with all values has correct state" } = [] {
		const auto [x, y, z, w] = mat4 {
			1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
		}.values;

		expect_eq(x[0], mat4::Underlying_T { 1.0 });
		expect_eq(x[1], mat4::Underlying_T { 2.0 });
		expect_eq(x[2], mat4::Underlying_T { 3.0 });
		expect_eq(x[3], mat4::Underlying_T { 4.0 });

		expect_eq(y[0], mat4::Underlying_T { 5.0 });
		expect_eq(y[1], mat4::Underlying_T { 6.0 });
		expect_eq(y[2], mat4::Underlying_T { 7.0 });
		expect_eq(y[3], mat4::Underlying_T { 8.0 });

		expect_eq(z[0], mat4::Underlying_T { 9.0 });
		expect_eq(z[1], mat4::Underlying_T { 10.0 });
		expect_eq(z[2], mat4::Underlying_T { 11.0 });
		expect_eq(z[3], mat4::Underlying_T { 12.0 });

		expect_eq(w[0], mat4::Underlying_T { 13.0 });
		expect_eq(w[1], mat4::Underlying_T { 14.0 });
		expect_eq(w[2], mat4::Underlying_T { 15.0 });
		expect_eq(w[3], mat4::Underlying_T { 16.0 });
	};

	Case { "post construct with columns has correct state" } = [] {
		const auto [x, y, z, w] = mat4 {
			mat4::Column_T { 1.0, 2.0, 3.0, 4.0 },
			mat4::Column_T { 5.0, 6.0, 7.0, 8.0 },
			mat4::Column_T { 9.0, 10.0, 11.0, 12.0 },
			mat4::Column_T { 13.0, 14.0, 15.0, 16.0 },
		}.values;

		expect_eq(x[0], mat4::Underlying_T { 1.0 });
		expect_eq(x[1], mat4::Underlying_T { 2.0 });
		expect_eq(x[2], mat4::Underlying_T { 3.0 });
		expect_eq(x[3], mat4::Underlying_T { 4.0 });

		expect_eq(y[0], mat4::Underlying_T { 5.0 });
		expect_eq(y[1], mat4::Underlying_T { 6.0 });
		expect_eq(y[2], mat4::Underlying_T { 7.0 });
		expect_eq(y[3], mat4::Underlying_T { 8.0 });

		expect_eq(z[0], mat4::Underlying_T { 9.0 });
		expect_eq(z[1], mat4::Underlying_T { 10.0 });
		expect_eq(z[2], mat4::Underlying_T { 11.0 });
		expect_eq(z[3], mat4::Underlying_T { 12.0 });

		expect_eq(w[0], mat4::Underlying_T { 13.0 });
		expect_eq(w[1], mat4::Underlying_T { 14.0 });
		expect_eq(w[2], mat4::Underlying_T { 15.0 });
		expect_eq(w[3], mat4::Underlying_T { 16.0 });
	};

	Case { "post construct identity matrix has correct state" } = [] {
		const auto [x, y, z, w] = mat4::identity().values;

		expect_eq(x[0], mat4::Underlying_T { 1 });
		expect_eq(x[1], mat4::Underlying_T {});
		expect_eq(x[2], mat4::Underlying_T {});
		expect_eq(x[3], mat4::Underlying_T {});

		expect_eq(y[0], mat4::Underlying_T {});
		expect_eq(y[1], mat4::Underlying_T { 1 });
		expect_eq(y[2], mat4::Underlying_T {});
		expect_eq(y[3], mat4::Underlying_T {});

		expect_eq(z[0], mat4::Underlying_T {});
		expect_eq(z[1], mat4::Underlying_T {});
		expect_eq(z[2], mat4::Underlying_T { 1 });
		expect_eq(z[3], mat4::Underlying_T {});

		expect_eq(w[0], mat4::Underlying_T {});
		expect_eq(w[1], mat4::Underlying_T {});
		expect_eq(w[2], mat4::Underlying_T {});
		expect_eq(w[3], mat4::Underlying_T { 1 });
	};
};

Suite arithmetic_operators = "mat4_arithmetic_operators"_suite = [] {
	Case { "operator *" } = [] {
		const auto lhs = mat4 {
			mat4::Column_T { 1.0, 2.0, 3.0, 4.0 },
			mat4::Column_T { 5.0, 6.0, 7.0, 8.0 },
			mat4::Column_T { 9.0, 10.0, 11.0, 12.0 },
			mat4::Column_T { 13.0, 14.0, 15.0, 16.0 },
		};

		const auto rhs = mat4 {
			mat4::Column_T { 17.0, 18.0, 19.0, 20.0 },
			mat4::Column_T { 21.0, 22.0, 23.0, 24.0 },
			mat4::Column_T { 25.0, 26.0, 27.0, 28.0 },
			mat4::Column_T { 29.0, 30.0, 31.0, 32.0 },
		};

		const auto [x, y, z, w] = (lhs * rhs).values;

		expect_eq(x[0], 538.0);
		expect_eq(x[1], 612.0);
		expect_eq(x[2], 686.0);
		expect_eq(x[3], 760.0);

		expect_eq(y[0], 650.0);
		expect_eq(y[1], 740.0);
		expect_eq(y[2], 830.0);
		expect_eq(y[3], 920.0);

		expect_eq(z[0], 762.0);
		expect_eq(z[1], 868.0);
		expect_eq(z[2], 974.0);
		expect_eq(z[3], 1080.0);

		expect_eq(w[0], 874.0);
		expect_eq(w[1], 996.0);
		expect_eq(w[2], 1118.0);
		expect_eq(w[3], 1240.0);
	};
};

Suite access_operators = "mat4_access_operators"_suite = [] {
	Case { "operator []" } = [] {
		auto mat = mat4 {
			1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
		};

		expect_eq(mat[0][0], 1.0);
		expect_eq(mat[0][1], 2.0);
		expect_eq(mat[0][2], 3.0);
		expect_eq(mat[0][3], 4.0);

		expect_eq(mat[1][0], 5.0);
		expect_eq(mat[1][1], 6.0);
		expect_eq(mat[1][2], 7.0);
		expect_eq(mat[1][3], 8.0);

		expect_eq(mat[2][0], 9.0);
		expect_eq(mat[2][1], 10.0);
		expect_eq(mat[2][2], 11.0);
		expect_eq(mat[2][3], 12.0);

		expect_eq(mat[3][0], 13.0);
		expect_eq(mat[3][1], 14.0);
		expect_eq(mat[3][2], 15.0);
		expect_eq(mat[3][3], 16.0);
	};

	Case { "operator [] const" } = [] {
		const auto mat = mat4 {
			1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
		};

		expect_eq(mat[0][0], 1.0);
		expect_eq(mat[0][1], 2.0);
		expect_eq(mat[0][2], 3.0);
		expect_eq(mat[0][3], 4.0);

		expect_eq(mat[1][0], 5.0);
		expect_eq(mat[1][1], 6.0);
		expect_eq(mat[1][2], 7.0);
		expect_eq(mat[1][3], 8.0);

		expect_eq(mat[2][0], 9.0);
		expect_eq(mat[2][1], 10.0);
		expect_eq(mat[2][2], 11.0);
		expect_eq(mat[2][3], 12.0);

		expect_eq(mat[3][0], 13.0);
		expect_eq(mat[3][1], 14.0);
		expect_eq(mat[3][2], 15.0);
		expect_eq(mat[3][3], 16.0);
	};
};

Suite transformations = "mat4_transformations"_suite = [] {
	Case { "translate" } = [] {
		const auto &[x, y, z, w] = mat4::translate(vec3 { 1, 2, 3 }).values;

		// identity basis
		expect_eq(x[0], 1);
		expect_eq(x[1], 0);
		expect_eq(x[2], 0);
		expect_eq(x[3], 0);
		expect_eq(y[0], 0);
		expect_eq(y[1], 1);
		expect_eq(y[2], 0);
		expect_eq(y[3], 0);
		expect_eq(z[0], 0);
		expect_eq(z[1], 0);
		expect_eq(z[2], 1);
		expect_eq(z[3], 0);

		// translation column
		expect_eq(w[0], 1);
		expect_eq(w[1], 2);
		expect_eq(w[2], 3);
		expect_eq(w[3], 1);
	};

	Case { "scale" } = [] {
		const auto [x, y, z, w] = mat4::scale(vec3 { 2, 3, 4 }).values;

		expect_eq(x[0], 2);
		expect_eq(x[1], 0);
		expect_eq(x[2], 0);
		expect_eq(x[3], 0);
		expect_eq(y[0], 0);
		expect_eq(y[1], 3);
		expect_eq(y[2], 0);
		expect_eq(y[3], 0);
		expect_eq(z[0], 0);
		expect_eq(z[1], 0);
		expect_eq(z[2], 4);
		expect_eq(z[3], 0);
		expect_eq(w[0], 0);
		expect_eq(w[1], 0);
		expect_eq(w[2], 0);
		expect_eq(w[3], 1);
	};

	Case { "scale -> translate" } = [] {
		const auto scale = mat4::scale(vec3 { 2, 2, 2 });
		const auto translate = mat4::translate(vec3 { 1, 2, 3 });
		const auto [x, y, z, w] = (scale * translate).values;

		// scaled basis
		expect_eq(x[0], 2);
		expect_eq(x[1], 0);
		expect_eq(x[2], 0);
		expect_eq(x[3], 0);
		expect_eq(y[0], 0);
		expect_eq(y[1], 2);
		expect_eq(y[2], 0);
		expect_eq(y[3], 0);
		expect_eq(z[0], 0);
		expect_eq(z[1], 0);
		expect_eq(z[2], 2);
		expect_eq(z[3], 0);

		// translation is scaled (local-space translation)
		expect_eq(w[0], 2); // 1 * 2
		expect_eq(w[1], 4); // 2 * 2
		expect_eq(w[2], 6); // 3 * 2
		expect_eq(w[3], 1);
	};

	Case { "transpose" } = [] {
		const auto mat = mat4 {
			mat4::Column_T { 1, 2, 3, 4 },
			mat4::Column_T { 5, 6, 7, 8 },
			mat4::Column_T { 9, 10, 11, 12 },
			mat4::Column_T { 13, 14, 15, 16 },
		};
		const auto [x, y, z, w] = mat4::transpose(mat).values;

		// rows become columns
		expect_eq(x[0], 1);
		expect_eq(x[1], 5);
		expect_eq(x[2], 9);
		expect_eq(x[3], 13);
		expect_eq(y[0], 2);
		expect_eq(y[1], 6);
		expect_eq(y[2], 10);
		expect_eq(y[3], 14);
		expect_eq(z[0], 3);
		expect_eq(z[1], 7);
		expect_eq(z[2], 11);
		expect_eq(z[3], 15);
		expect_eq(w[0], 4);
		expect_eq(w[1], 8);
		expect_eq(w[2], 12);
		expect_eq(w[3], 16);
	};

	Case { "transpose twice" } = [] {
		const auto mat = mat4 {
			mat4::Column_T { 1, 2, 3, 4 },
			mat4::Column_T { 5, 6, 7, 8 },
			mat4::Column_T { 9, 10, 11, 12 },
			mat4::Column_T { 13, 14, 15, 16 },
		};
		const auto [x, y, z, w] = mat4::transpose(mat4::transpose(mat)).values;

		expect_eq(x[0], 1);
		expect_eq(x[1], 2);
		expect_eq(x[2], 3);
		expect_eq(x[3], 4);
		expect_eq(y[0], 5);
		expect_eq(y[1], 6);
		expect_eq(y[2], 7);
		expect_eq(y[3], 8);
		expect_eq(z[0], 9);
		expect_eq(z[1], 10);
		expect_eq(z[2], 11);
		expect_eq(z[3], 12);
		expect_eq(w[0], 13);
		expect_eq(w[1], 14);
		expect_eq(w[2], 15);
		expect_eq(w[3], 16);
	};
};
