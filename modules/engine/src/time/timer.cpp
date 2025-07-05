#include <engine/time/timer.hpp>

namespace Light {

Timer::Timer(): m_Start(std::chrono::steady_clock::now())
{
}

DeltaTimer::DeltaTimer(): m_PreviousFrame(NULL), m_DeltaTime(60.0f / 1000.0f)
{
}

void DeltaTimer::Update()
{
	float currentFrame = timer.GetElapsedTime();
	m_DeltaTime = currentFrame - m_PreviousFrame;
	m_PreviousFrame = currentFrame;
}

} // namespace Light
