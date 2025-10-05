#include <memory/reference.hpp>
#include <surface/system.hpp>
#include <utility>

namespace lt::surface {

System::System(
    memory::Ref<ecs::Registry> registry,
    memory::Ref<app::EventMediator> event_mediator
)
    : m_registry(std::move(registry))
    , m_event_mediator(std::move(event_mediator))
{
	ensure(m_registry, "Failed to initialize surface system: null registry");

	ensure(
	    m_registry->view<SurfaceComponent>().size() == 0,
	    "Failed to initialize surface system: registry has surface component(s)"
	);

	m_registry->get_entt_registry()
	    .on_construct<SurfaceComponent>()
	    .connect<&System::on_surface_construct>(this);

	m_registry->get_entt_registry()
	    .on_update<SurfaceComponent>()
	    .connect<&System::on_surface_update>(this);

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
	    .on_update<SurfaceComponent>()
	    .connect<&System::on_surface_update>(this);

	m_registry->get_entt_registry()
	    .on_destroy<SurfaceComponent>()
	    .disconnect<&System::on_surface_destroy>(this);


	m_registry->view<SurfaceComponent>().each([&](const entt::entity entity, SurfaceComponent &) {
		m_registry->get_entt_registry().remove<SurfaceComponent>(entity);
	});
}

void System::on_surface_construct(entt::registry &registry, entt::entity entity)
{
	try
	{
		auto &surface = registry.get<SurfaceComponent>(entity);
		const auto &resolution = surface.get_resolution();
		const auto &position = surface.get_position();
		ensure_component_sanity(surface);
	}
	catch (...)
	{
		registry.remove<SurfaceComponent>(entity);
		throw;
	}
}

void System::on_surface_update(entt::registry &registry, entt::entity entity)
{
	auto &surface = registry.get<SurfaceComponent>(entity);
}

void System::on_surface_destroy(entt::registry &registry, entt::entity entity)
{
	auto &surface = registry.get<SurfaceComponent>(entity);
}

void System::set_title(ecs::Entity entity, std::string_view new_title)
{
	auto &surface = entity.get_component<SurfaceComponent>();

	surface.m_title = new_title;
}

auto System::tick() -> bool
{
	return false;
}

void System::set_size(ecs::Entity surface_entity, const math::uvec2 &new_size)
{
	auto &surface = surface_entity.get_component<SurfaceComponent>();
	surface.m_resolution = new_size;
}

void System::set_v_sync(ecs::Entity surface_entity, bool vsync)
{
	auto &surface = surface_entity.get_component<SurfaceComponent>();
	surface.m_vsync = vsync;
}

void System::set_visibility(ecs::Entity surface_entity, bool visible)
{
	auto &surface = surface_entity.get_component<SurfaceComponent>();
	surface.m_visible = visible;

	if (visible)
	{
	}
	else
	{
	}
}

void System::ensure_component_sanity(const SurfaceComponent &component)
{
	auto [width, height] = component.get_resolution();

	ensure(width != 0u, "Received bad values for surface component: width({}) == 0", width);

	ensure(height != 0u, "Received bad values for surface component: height({}) == 0", height);

	ensure(
	    width < SurfaceComponent::max_dimension,
	    "Received bad values for surface component: width({}) > max_dimension({})",
	    width,
	    SurfaceComponent::max_dimension
	);

	ensure(
	    height < SurfaceComponent::max_dimension,
	    "Received bad values for surface component: height({}) > max_dimension({})",
	    height,
	    SurfaceComponent::max_dimension
	);

	ensure(
	    component.get_title().size() < SurfaceComponent::max_title_length,
	    "Received bad values for surface component: title.size({}) > max_title_length({})",
	    component.get_title().size(),
	    SurfaceComponent::max_title_length
	);
}

} // namespace lt::surface

namespace lt {

} // namespace lt
