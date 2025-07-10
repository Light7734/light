#include <time/timer.hpp>

namespace lt {

Timer::Timer(): m_start(std::chrono::steady_clock::now())
{
}

} // namespace lt
