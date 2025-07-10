#pragma once

#include <chrono>


namespace lt {

class Timer
{
public:
	Timer();

	[[nodiscard]] auto get_elapsed_time() const -> float
	{
		using std::chrono::duration_cast;
		using std::chrono::milliseconds;
		using std::chrono::steady_clock;

		auto rep = duration_cast<milliseconds>(steady_clock::now() - m_start).count();
		return static_cast<float>(rep) / 1000.f;
	}

	void reset()
	{
		m_start = std::chrono::steady_clock::now();
	}

private:
	std::chrono::time_point<std::chrono::steady_clock> m_start;
};

} // namespace lt
