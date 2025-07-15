#include <ranges>
#include <test/test.hpp>
#include <time/timer.hpp>

namespace lt {

using lt::test::expect_le;

lt::test::Suite raii = [] {
	using std::chrono::microseconds;

	lt::test::Case { "default" } = [] {
		Timer {};
	};

	lt::test::Case { "unhappy path throws" } = [] {
	};

	lt::test::Case { "plenty" } = [] {
		for (auto i : std::views::iota(0, 100'001))
		{
			Timer {};
		}
	};
};

lt::test::Suite reset_and_elapsed_time = [] {
	using std::chrono::hours;
	using std::chrono::microseconds;

	lt::test::Case { "won't throw" } = [] {
		Timer {}.reset();
		std::ignore = Timer {}.elapsed_time();
	};

	lt::test::Case { "elapsed time is sane" } = [] {
		expect_le(Timer {}.elapsed_time(), microseconds { 1 });
	};

	lt::test::Case { "elapsed time is sane - constructed with old now" } = [] {
		const auto timepoint = Timer::Clock::now() - hours { 1 };

		// This fails sometimes in debug if error-range is under 10us
		expect_le(Timer { timepoint }.elapsed_time(), hours { 1 } + microseconds { 30 });
	};

	lt::test::Case { "reset -> elapsed time is sane - constructed with old now" } = [] {
		auto timer = Timer { Timer::Clock::now() - microseconds { 100 } };
		const auto old_elapsed_time = timer.elapsed_time();
		timer.reset();

		expect_le(timer.elapsed_time() - old_elapsed_time, microseconds { 101 });
	};

	lt::test::Case { "reset -> elapsed time is sane - reset with future now" } = [] {
		auto timer = Timer {};
		const auto old_elapsed_time = timer.elapsed_time();
		timer.reset(Timer::Clock::now() + microseconds { 100 });

		expect_le(timer.elapsed_time() - old_elapsed_time, microseconds { 101 });
	};
};

} // namespace lt
