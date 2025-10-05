#include <memory/reference.hpp>
#include <memory/scope.hpp>
#include <ranges>
#include <renderer/system.hpp>
#include <renderer/vk/context/context.hpp>
#include <renderer/vk/renderer/renderer.hpp>
#include <surface/components.hpp>
#include <surface/system.hpp>
#include <test/test.hpp>

using namespace lt;
using std::ignore;
using test::Case;
using test::expect_throw;
using test::expect_true;
using test::Suite;

using renderer::System;

constexpr auto resolution = math::uvec2 { 800, 600 };

struct SurfaceContext
{
	surface::System system;
	ecs::Entity entity;
};

struct RendererContext
{
	memory::Ref<ecs::Registry> registry;
	System system;
};

[[nodiscard]] auto create_surface() -> SurfaceContext
{
	using surface::SurfaceComponent;

	auto surface_registry = memory::create_ref<ecs::Registry>();
	auto surface_entity = surface_registry->create_entity();
	auto surface_system = surface::System(surface_registry);
	surface_registry->add<SurfaceComponent>(
	    surface_entity,
	    SurfaceComponent::CreateInfo {
	        .title = "",
	        .resolution = resolution,
	    }
	);

	return {
		.system = std::move(surface_system),
		.entity = ecs::Entity { surface_registry, surface_entity },
	};
}

[[nodiscard]] auto create_system() -> std::pair<SurfaceContext, RendererContext>
{
	auto surface_context = create_surface();
	auto &[surface_system, surface_entity] = surface_context;
	auto registry = memory::create_ref<ecs::Registry>();
	auto stats = memory::create_ref<app::SystemStats>();

	return {
		std::move(surface_context),
		RendererContext {
		    .registry = registry,
		    .system = System(
		        {
		            .registry = registry,
		            .surface_entity = surface_entity,
		            .system_stats = stats,
		        }
		    ),
		},
	};
}

class SystemTest
{
public:
	SystemTest()
	{
		m_surface_entity->add<surface::SurfaceComponent>(surface::SurfaceComponent::CreateInfo {
		    .title = "",
		    .resolution = resolution,
		});
	}

	[[nodiscard]] auto registry() const -> memory::Ref<ecs::Registry>
	{
		return m_registry;
	}

	[[nodiscard]] auto surface_entity() const -> const ecs::Entity &
	{
		return *m_surface_entity;
	}

	[[nodiscard]] auto stats() const -> memory::Ref<app::SystemStats>
	{
		return m_stats;
	}

private:
	memory::Ref<app::SystemStats> m_stats = memory::create_ref<app::SystemStats>();

	memory::Ref<ecs::Registry> m_registry = memory::create_ref<ecs::Registry>();

	memory::Ref<surface::System> m_surface_system = memory::create_ref<surface::System>(
	    m_registry
	);

	memory::Scope<ecs::Entity> m_surface_entity = memory::create_scope<ecs::Entity>(
	    m_registry,
	    m_registry->create_entity()
	);
};

Suite raii = "raii"_suite = [] {
	Case { "happy path won't throw" } = [&] {
		ignore = create_system();
	};

	Case { "happy path has no validation errors" } = [&] {
		auto fixture = SystemTest {};
		std::ignore = System(
		    {
		        .registry = fixture.registry(),
		        .surface_entity = fixture.surface_entity(),
		        .system_stats = fixture.stats(),
		    }
		);

		expect_true(fixture.stats()->empty_diagnosis());
	};

	Case { "unhappy path throws" } = [] {
		auto fixture = SystemTest {};
		auto empty_entity = ecs::Entity { fixture.registry(), fixture.registry()->create_entity() };

		expect_throw([&] {
			ignore = System(
			    {
			        .registry = {},
			        .surface_entity = fixture.surface_entity(),
			        .system_stats = fixture.stats(),
			    }
			);
		});

		expect_throw([&] {
			ignore = System(
			    System::CreateInfo {
			        .registry = fixture.registry(),
			        .surface_entity = empty_entity,
			        .system_stats = fixture.stats(),
			    }
			);
		});

		expect_throw([&] {
			ignore = System(
			    System::CreateInfo {
			        .registry = fixture.registry(),
			        .surface_entity = fixture.surface_entity(),
			        .system_stats = {},
			    }
			);
		});
	};
};
