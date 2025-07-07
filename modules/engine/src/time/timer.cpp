#include <engine/time/timer.hpp>

namespace Light {

Timer::Timer(): m_start(std::chrono::steady_clock::now())
{
}

} // namespace Light
