#include <engine/core/uuid.hpp>

namespace Light {

std::mt19937_64 UUID::s_Engine = std::mt19937_64(std::random_device()());
std::uniform_int_distribution<uint64_t> UUID::s_UniformDistribution;

UUID::UUID(uint64_t uuid /* = -1 */): m_UUID(uuid == -1 ? s_UniformDistribution(s_Engine) : uuid)
{
}

} // namespace Light
