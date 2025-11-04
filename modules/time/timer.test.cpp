import time;
import test.test;
import test.expects;
import std;

using ::lt::test::Case;
using ::lt::test::expect_le;
using ::lt::test::operator""_suite;
using ::lt::test::Suite;
using ::lt::time::Timer;

// error margin is high since run-time may slow down extremely due to
// sanitization/debugging or execution through valgrind...
//
// <1us error margin is tested manually in release builds and it works fine.
constexpr auto max_error_margin = std::chrono::milliseconds { 1 };

Suite raii = "raii"_suite = [] {
	using std::chrono::microseconds;

	Case { "default" } = [] {
		Timer {};
	};

	Case { "unhappy path throws" } = [] {
	};

	Case { "plenty" } = [] {
		for (auto idx : std::views::iota(0, 100'001))
		{
			Timer {};
		}
	};
};

Suite reset_and_elapsed_time = "reset_and_elapsed_time"_suite = [] {
	using std::chrono::hours;
	using std::chrono::microseconds;

	Case { "won't throw" } = [] {
		Timer {}.reset();
		std::ignore = Timer {}.elapsed_time();
	};

	Case { "elapsed time is sane" } = [] {
		expect_le(Timer {}.elapsed_time(), max_error_margin);
	};

	Case { "elapsed time is sane - constructed with old now" } = [] {
		const auto timepoint = Timer::Clock::now() - hours { 1 };

		// This fails sometimes in debug if error-range is under 10us
		expect_le(Timer { timepoint }.elapsed_time(), hours { 1 } + max_error_margin);
	};

	Case { "reset -> elapsed time is sane - constructed with old now" } = [] {
		auto timer = Timer { Timer::Clock::now() - microseconds { 100 } };
		const auto old_elapsed_time = timer.elapsed_time();
		timer.reset();

		expect_le(timer.elapsed_time() - old_elapsed_time, microseconds { 100 } + max_error_margin);
	};

	Case { "reset -> elapsed time is sane - reset with future now" } = [] {
		auto timer = Timer {};
		const auto old_elapsed_time = timer.elapsed_time();
		timer.reset(Timer::Clock::now() + microseconds { 100 });

		expect_le(timer.elapsed_time() - old_elapsed_time, microseconds { 100 } + max_error_margin);
	};
};
