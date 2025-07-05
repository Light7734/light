#pragma once

#include <chrono>
#include <engine/base/base.hpp>

namespace Light {

class Timer
{
private:
	std::chrono::time_point<std::chrono::steady_clock> m_start;

public:
	Timer();

	inline float get_elapsed_time() const
	{
		return (std::chrono::duration_cast<std::chrono::milliseconds>(
		            std::chrono::steady_clock::now() - m_start
		       )
		            .count())
		       / 1000.;
	}

	inline void reset()
	{
		m_start = std::chrono::steady_clock::now();
	}
};

class DeltaTimer
{
private:
	Timer timer;

	float m_previous_frame;
	float m_delta_time;

public:
	DeltaTimer();

	void update();

	inline float get_delta_time() const
	{
		return m_delta_time;
	}
};

} // namespace Light
