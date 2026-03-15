import test;
import math.vec3;
import math.mat4;

using vec3 = ::lt::math::vec3;
using mat4 = ::lt::math::mat4;

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

		expect_eq(x.x, mat4::Underlying_T {});
		expect_eq(x.y, mat4::Underlying_T {});
		expect_eq(x.z, mat4::Underlying_T {});
		expect_eq(x.w, mat4::Underlying_T {});

		expect_eq(y.x, mat4::Underlying_T {});
		expect_eq(y.y, mat4::Underlying_T {});
		expect_eq(y.z, mat4::Underlying_T {});
		expect_eq(y.w, mat4::Underlying_T {});

		expect_eq(z.x, mat4::Underlying_T {});
		expect_eq(z.y, mat4::Underlying_T {});
		expect_eq(z.z, mat4::Underlying_T {});
		expect_eq(z.w, mat4::Underlying_T {});

		expect_eq(w.x, mat4::Underlying_T {});
		expect_eq(w.y, mat4::Underlying_T {});
		expect_eq(w.z, mat4::Underlying_T {});
		expect_eq(w.w, mat4::Underlying_T {});
	};

	Case { "post scalar construct has correct state" } = [] {
		const auto [x, y, z, w] = mat4 { 69.0 }.values;

		expect_eq(x.x, mat4::Underlying_T { 69.0 });
		expect_eq(x.y, mat4::Underlying_T { 69.0 });
		expect_eq(x.z, mat4::Underlying_T { 69.0 });
		expect_eq(x.w, mat4::Underlying_T { 69.0 });

		expect_eq(y.x, mat4::Underlying_T { 69.0 });
		expect_eq(y.y, mat4::Underlying_T { 69.0 });
		expect_eq(y.z, mat4::Underlying_T { 69.0 });
		expect_eq(y.w, mat4::Underlying_T { 69.0 });

		expect_eq(z.x, mat4::Underlying_T { 69.0 });
		expect_eq(z.y, mat4::Underlying_T { 69.0 });
		expect_eq(z.z, mat4::Underlying_T { 69.0 });
		expect_eq(z.w, mat4::Underlying_T { 69.0 });

		expect_eq(w.x, mat4::Underlying_T { 69.0 });
		expect_eq(w.y, mat4::Underlying_T { 69.0 });
		expect_eq(w.z, mat4::Underlying_T { 69.0 });
		expect_eq(w.w, mat4::Underlying_T { 69.0 });
	};

	Case { "post construct with all values has correct state" } = [] {
		const auto [x, y, z, w] = mat4 {
			1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
		}.values;

		expect_eq(x.x, mat4::Underlying_T { 1.0 });
		expect_eq(x.y, mat4::Underlying_T { 2.0 });
		expect_eq(x.z, mat4::Underlying_T { 3.0 });
		expect_eq(x.w, mat4::Underlying_T { 4.0 });

		expect_eq(y.x, mat4::Underlying_T { 5.0 });
		expect_eq(y.y, mat4::Underlying_T { 6.0 });
		expect_eq(y.z, mat4::Underlying_T { 7.0 });
		expect_eq(y.w, mat4::Underlying_T { 8.0 });

		expect_eq(z.x, mat4::Underlying_T { 9.0 });
		expect_eq(z.y, mat4::Underlying_T { 10.0 });
		expect_eq(z.z, mat4::Underlying_T { 11.0 });
		expect_eq(z.w, mat4::Underlying_T { 12.0 });

		expect_eq(w.x, mat4::Underlying_T { 13.0 });
		expect_eq(w.y, mat4::Underlying_T { 14.0 });
		expect_eq(w.z, mat4::Underlying_T { 15.0 });
		expect_eq(w.w, mat4::Underlying_T { 16.0 });
	};

	Case { "post construct with columns has correct state" } = [] {
		const auto [x, y, z, w] = mat4 {
			mat4::Column_T { 1.0, 2.0, 3.0, 4.0 },
			mat4::Column_T { 5.0, 6.0, 7.0, 8.0 },
			mat4::Column_T { 9.0, 10.0, 11.0, 12.0 },
			mat4::Column_T { 13.0, 14.0, 15.0, 16.0 },
		}.values;

		expect_eq(x.x, mat4::Underlying_T { 1.0 });
		expect_eq(x.y, mat4::Underlying_T { 2.0 });
		expect_eq(x.z, mat4::Underlying_T { 3.0 });
		expect_eq(x.w, mat4::Underlying_T { 4.0 });

		expect_eq(y.x, mat4::Underlying_T { 5.0 });
		expect_eq(y.y, mat4::Underlying_T { 6.0 });
		expect_eq(y.z, mat4::Underlying_T { 7.0 });
		expect_eq(y.w, mat4::Underlying_T { 8.0 });

		expect_eq(z.x, mat4::Underlying_T { 9.0 });
		expect_eq(z.y, mat4::Underlying_T { 10.0 });
		expect_eq(z.z, mat4::Underlying_T { 11.0 });
		expect_eq(z.w, mat4::Underlying_T { 12.0 });

		expect_eq(w.x, mat4::Underlying_T { 13.0 });
		expect_eq(w.y, mat4::Underlying_T { 14.0 });
		expect_eq(w.z, mat4::Underlying_T { 15.0 });
		expect_eq(w.w, mat4::Underlying_T { 16.0 });
	};

	Case { "post construct identity matrix has correct state" } = [] {
		const auto [x, y, z, w] = mat4::identity().values;

		expect_eq(x.x, mat4::Underlying_T { 1 });
		expect_eq(x.y, mat4::Underlying_T {});
		expect_eq(x.z, mat4::Underlying_T {});
		expect_eq(x.w, mat4::Underlying_T {});

		expect_eq(y.x, mat4::Underlying_T {});
		expect_eq(y.y, mat4::Underlying_T { 1 });
		expect_eq(y.z, mat4::Underlying_T {});
		expect_eq(y.w, mat4::Underlying_T {});

		expect_eq(z.x, mat4::Underlying_T {});
		expect_eq(z.y, mat4::Underlying_T {});
		expect_eq(z.z, mat4::Underlying_T { 1 });
		expect_eq(z.w, mat4::Underlying_T {});

		expect_eq(w.x, mat4::Underlying_T {});
		expect_eq(w.y, mat4::Underlying_T {});
		expect_eq(w.z, mat4::Underlying_T {});
		expect_eq(w.w, mat4::Underlying_T { 1 });
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

		expect_eq(x.x, 538.0);
		expect_eq(x.y, 612.0);
		expect_eq(x.z, 686.0);
		expect_eq(x.w, 760.0);

		expect_eq(y.x, 650.0);
		expect_eq(y.y, 740.0);
		expect_eq(y.z, 830.0);
		expect_eq(y.w, 920.0);

		expect_eq(z.x, 762.0);
		expect_eq(z.y, 868.0);
		expect_eq(z.z, 974.0);
		expect_eq(z.w, 1080.0);

		expect_eq(w.x, 874.0);
		expect_eq(w.y, 996.0);
		expect_eq(w.z, 1118.0);
		expect_eq(w.w, 1240.0);
	};
};

Suite access_operators = "mat4_access_operators"_suite = [] {
	Case { "operator []" } = [] {
		auto mat = mat4 {
			1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
		};

		expect_eq(mat[0].x, 1.0);
		expect_eq(mat[0].y, 2.0);
		expect_eq(mat[0].z, 3.0);
		expect_eq(mat[0].w, 4.0);

		expect_eq(mat[1].x, 5.0);
		expect_eq(mat[1].y, 6.0);
		expect_eq(mat[1].z, 7.0);
		expect_eq(mat[1].w, 8.0);

		expect_eq(mat[2].x, 9.0);
		expect_eq(mat[2].y, 10.0);
		expect_eq(mat[2].z, 11.0);
		expect_eq(mat[2].w, 12.0);

		expect_eq(mat[3].x, 13.0);
		expect_eq(mat[3].y, 14.0);
		expect_eq(mat[3].z, 15.0);
		expect_eq(mat[3].w, 16.0);
	};

	Case { "operator [] const" } = [] {
		const auto mat = mat4 {
			1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0,
		};

		expect_eq(mat[0].x, 1.0);
		expect_eq(mat[0].y, 2.0);
		expect_eq(mat[0].z, 3.0);
		expect_eq(mat[0].w, 4.0);

		expect_eq(mat[1].x, 5.0);
		expect_eq(mat[1].y, 6.0);
		expect_eq(mat[1].z, 7.0);
		expect_eq(mat[1].w, 8.0);

		expect_eq(mat[2].x, 9.0);
		expect_eq(mat[2].y, 10.0);
		expect_eq(mat[2].z, 11.0);
		expect_eq(mat[2].w, 12.0);

		expect_eq(mat[3].x, 13.0);
		expect_eq(mat[3].y, 14.0);
		expect_eq(mat[3].z, 15.0);
		expect_eq(mat[3].w, 16.0);
	};
};

Suite transformations = "mat4_transformations"_suite = [] {
	Case { "translate" } = [] {
		const auto &[x, y, z, w] = mat4::translate(vec3 { 1, 2, 3 }).values;

		// identity basis
		expect_eq(x.x, 1);
		expect_eq(x.y, 0);
		expect_eq(x.z, 0);
		expect_eq(x.w, 0);
		expect_eq(y.x, 0);
		expect_eq(y.y, 1);
		expect_eq(y.z, 0);
		expect_eq(y.w, 0);
		expect_eq(z.x, 0);
		expect_eq(z.y, 0);
		expect_eq(z.z, 1);
		expect_eq(z.w, 0);

		// translation column
		expect_eq(w.x, 1);
		expect_eq(w.y, 2);
		expect_eq(w.z, 3);
		expect_eq(w.w, 1);
	};

	Case { "scale" } = [] {
		const auto [x, y, z, w] = mat4::scale(vec3 { 2, 3, 4 }).values;

		expect_eq(x.x, 2);
		expect_eq(x.y, 0);
		expect_eq(x.z, 0);
		expect_eq(x.w, 0);
		expect_eq(y.x, 0);
		expect_eq(y.y, 3);
		expect_eq(y.z, 0);
		expect_eq(y.w, 0);
		expect_eq(z.x, 0);
		expect_eq(z.y, 0);
		expect_eq(z.z, 4);
		expect_eq(z.w, 0);
		expect_eq(w.x, 0);
		expect_eq(w.y, 0);
		expect_eq(w.z, 0);
		expect_eq(w.w, 1);
	};

	Case { "scale -> translate" } = [] {
		const auto scale = mat4::scale(vec3 { 2, 2, 2 });
		const auto translate = mat4::translate(vec3 { 1, 2, 3 });
		const auto [x, y, z, w] = (scale * translate).values;

		// scaled basis
		expect_eq(x.x, 2);
		expect_eq(x.y, 0);
		expect_eq(x.z, 0);
		expect_eq(x.w, 0);
		expect_eq(y.x, 0);
		expect_eq(y.y, 2);
		expect_eq(y.z, 0);
		expect_eq(y.w, 0);
		expect_eq(z.x, 0);
		expect_eq(z.y, 0);
		expect_eq(z.z, 2);
		expect_eq(z.w, 0);

		// translation is scaled (local-space translation)
		expect_eq(w.x, 2); // 1 * 2
		expect_eq(w.y, 4); // 2 * 2
		expect_eq(w.z, 6); // 3 * 2
		expect_eq(w.w, 1);
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
		expect_eq(x.x, 1);
		expect_eq(x.y, 5);
		expect_eq(x.z, 9);
		expect_eq(x.w, 13);
		expect_eq(y.x, 2);
		expect_eq(y.y, 6);
		expect_eq(y.z, 10);
		expect_eq(y.w, 14);
		expect_eq(z.x, 3);
		expect_eq(z.y, 7);
		expect_eq(z.z, 11);
		expect_eq(z.w, 15);
		expect_eq(w.x, 4);
		expect_eq(w.y, 8);
		expect_eq(w.z, 12);
		expect_eq(w.w, 16);
	};

	Case { "transpose twice" } = [] {
		const auto mat = mat4 {
			mat4::Column_T { 1, 2, 3, 4 },
			mat4::Column_T { 5, 6, 7, 8 },
			mat4::Column_T { 9, 10, 11, 12 },
			mat4::Column_T { 13, 14, 15, 16 },
		};
		const auto [x, y, z, w] = mat4::transpose(mat4::transpose(mat)).values;

		expect_eq(x.x, 1);
		expect_eq(x.y, 2);
		expect_eq(x.z, 3);
		expect_eq(x.w, 4);
		expect_eq(y.x, 5);
		expect_eq(y.y, 6);
		expect_eq(y.z, 7);
		expect_eq(y.w, 8);
		expect_eq(z.x, 9);
		expect_eq(z.y, 10);
		expect_eq(z.z, 11);
		expect_eq(z.w, 12);
		expect_eq(w.x, 13);
		expect_eq(w.y, 14);
		expect_eq(w.z, 15);
		expect_eq(w.w, 16);
	};
};
