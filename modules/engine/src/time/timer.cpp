#include <engine/time/timer.hpp>

namespace Light {

Timer::Timer(): m_start(std::chrono::steady_clock::now())
{
}

DeltaTimer::DeltaTimer(): m_previous_frame(NULL), m_delta_time(60.0f / 1000.0f)
{
}

void DeltaTimer::update()
{
	float currentFrame = timer.get_elapsed_time();
	m_delta_time = currentFrame - m_previous_frame;
	m_previous_frame = currentFrame;
}

} // namespace Light
