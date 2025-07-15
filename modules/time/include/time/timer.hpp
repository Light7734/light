#pragma once

#include <chrono>

namespace lt {

/** Simple timer class to keep track of the elapsed time */
class Timer
{
public:
	using Timepoint = std::chrono::time_point<std::chrono::steady_clock>;
	using Duration = std::chrono::duration<double>;
	using Clock = std::chrono::steady_clock;

	Timer(Timepoint start = Clock::now());

	void reset(Timepoint start = Clock::now());

	[[nodiscard]] auto elapsed_time() const -> Duration;

private:
	Timepoint m_start;
};

} // namespace lt
