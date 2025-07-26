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

	auto *window = static_cast<GLFWwindow *>(lt::Window::create([](auto &&PH1) {})->get_handle());

	Case { "happy" } = [=] {
		std::ignore = System { {
			.glfw_window_handle = window,
			.registry = create_ref<ecs::Registry>(),
		} };
	};

	Case { "unhappy" } = [=] {
		expect_throw([=] {
			std::ignore = System { {
				.glfw_window_handle = window,
				.registry = {},
			} };
		});

		expect_throw([=] {
			std::ignore = System { {
				.glfw_window_handle = {},
				.registry = create_ref<ecs::Registry>(),
			} };
		});
	};

	Case { "plenty" } = [=] {
		for (auto idx : std::views::iota(0, 100'001))
		{
			std::ignore = System { {
				.glfw_window_handle = window,
				.registry = create_ref<ecs::Registry>(),
			} };
		}
	};
};
