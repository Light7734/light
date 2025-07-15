#include <ranges>
#include <test/test.hpp>
#include <time/timer.hpp>

namespace lt {

using lt::test::expect_le;

lt::test::Suite raii = [] {
	lt::test::Case { "default" } = [] {
		auto timer = Timer {};
	};

	lt::test::Case { "plenty" } = [] {
		for (auto i : std::views::iota(0, 101))
		{
			auto timer = Timer {};
		}
	};

	lt::test::Case { "unhappy" } = [] {
	};

	lt::test::Case { "has sane elapsed time" } = [] {
		auto elapsed_time = Timer {}.elapsed_time();
		expect_le(elapsed_time, std::chrono::seconds { 1 });
	};
};

lt::test::Suite reset = [] {
	lt::test::Case { "non-throwing" } = [] {
		auto timer = Timer {};
		timer.reset();
	};

	lt::test::Case { "resets elapsed time" } = [] {
		auto timer = Timer {};
		auto elapsed_time = timer.elapsed_time();

		timer.reset();
	};
};

} // namespace lt
