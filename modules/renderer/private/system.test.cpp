#include <ranges>
#include <renderer/system.hpp>
#include <test/test.hpp>
#include <window/window.hpp>

using namespace lt;

using lt::test::Case;
using lt::test::Suite;

Suite raii = [] {
	using lt::test::expect_true;
	using lt::test::expect_throw;
	using renderer::System;

	Case { "happy" } = [=] {
		std::ignore = System { {
			.registry = create_ref<ecs::Registry>(),
		} };
	};

	Case { "unhappy" } = [=] {
		expect_throw([=] {
			std::ignore = System { {
				.registry = {},
			} };
		});

		expect_throw([=] {
			std::ignore = System { {
				.registry = create_ref<ecs::Registry>(),
			} };
		});
	};

	Case { "plenty" } = [=] {
		for (auto idx : std::views::iota(0, 100'001))
		{
			std::ignore = System { {
				.registry = create_ref<ecs::Registry>(),
			} };
		}
	};
};
