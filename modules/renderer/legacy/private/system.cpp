#include <lt_debug/assertions.hpp>
#include <renderer/system.hpp>

namespace lt::renderer {

System::System(InitRequirements requirements): m_registry(std::move(requirements.registry))
{
	ensure(m_registry, "null registry");
}

System::~System() = default;

void System::tick(TickRequirements requirements)
{
}

} // namespace lt::renderer
