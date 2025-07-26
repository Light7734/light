#include <surface/system.hpp>

namespace lt::surface {

System::System(Ref<ecs::Registry> registry): m_registry(std::move(registry))
{
	m_registry->get_entt_registry()
	    .on_construct<SurfaceComponent>()
	    .connect<&System::on_surface_construct>(this);

	m_registry->get_entt_registry()
	    .on_destroy<SurfaceComponent>()
	    .connect<&System::on_surface_destroy>(this);
}

System::~System()
{
	m_registry->get_entt_registry()
	    .on_construct<SurfaceComponent>()
	    .disconnect<&System::on_surface_construct>(this);

	m_registry->get_entt_registry()
	    .on_destroy<SurfaceComponent>()
	    .disconnect<&System::on_surface_destroy>(this);
}

} // namespace lt::surface
