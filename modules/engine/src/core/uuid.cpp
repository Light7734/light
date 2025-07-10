#include <engine/core/uuid.hpp>

namespace lt {

auto UUID::s_engine = std::mt19937_64(std::random_device()());
auto UUID::s_distribution = std::uniform_int_distribution<uint64_t> {};

UUID::UUID(uint64_t uuid /* = -1 */): m_uuid(uuid == -1 ? s_distribution(s_engine) : uuid)
{
}

} // namespace lt
