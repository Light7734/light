#include <time/timer.hpp>

namespace lt {

Timer::Timer(Timepoint start): m_start(start)
{
}

void Timer::reset(Timepoint start)
{
	m_start = start;
}

[[nodiscard]] auto Timer::elapsed_time() const -> Duration
{
	return { std::chrono::steady_clock::now() - m_start };
}

} // namespace lt
