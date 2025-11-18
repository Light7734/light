export module time;
import lsd;

namespace lt::time {

/** Simple timer class to keep track of the elapsed time. */
export class Timer
{
public:
	using Clock = lsd::chrono::steady_clock;

	using Duration = lsd::chrono::duration<f64>;

	using Timepoint = lsd::chrono::time_point<lsd::chrono::steady_clock>;

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
	return { lsd::chrono::steady_clock::now() - m_start };
}

} // namespace lt::time
