export module time;

import preliminary;

export namespace lt::time {

/** Simple timer class to keep track of the elapsed time. */
class Timer
{
public:
	using Clock = std::chrono::steady_clock;

	using Duration = std::chrono::duration<f64>;

	using Timepoint = std::chrono::time_point<std::chrono::steady_clock>;

	Timer(Timepoint start = Clock::now());

	void reset(Timepoint start = Clock::now());

	[[nodiscard]] auto elapsed_time() const -> Duration;

private:
	Timepoint m_start;
};

} // namespace lt::time

module :private;
namespace lt::time {

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

} // namespace lt::time
