#pragma once

#include <chrono>
#include <engine/base/base.hpp>

namespace Light {

class Timer
{
public:
	Timer();

	auto get_elapsed_time() const -> float
	{
		return (std::chrono::duration_cast<std::chrono::milliseconds>(
		            std::chrono::steady_clock::now() - m_start
		       )
		            .count())
		       / 1000.;
	}

	void reset()
	{
		m_start = std::chrono::steady_clock::now();
	}

private:
	std::chrono::time_point<std::chrono::steady_clock> m_start;
};

class DeltaTimer
{
public:
	DeltaTimer();

	void update();

	auto get_delta_time() const -> float
	{
		return m_delta_time;
	}

private:
	Timer timer;

	float m_previous_frame;

	float m_delta_time;
};

} // namespace Light
