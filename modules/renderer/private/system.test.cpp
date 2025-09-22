#include <ranges>
#include <renderer/system.hpp>
#include <surface/system.hpp>
#include <test/test.hpp>

using namespace lt;
using std::ignore;
using test::Case;
using test::expect_eq;
using test::expect_ne;
using test::expect_not_nullptr;
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
	Ref<ecs::Registry> registry;
	System system;
};

[[nodiscard]] auto create_surface() -> SurfaceContext
{
	using surface::SurfaceComponent;

	auto surface_registry = create_ref<ecs::Registry>();
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

[[nodiscard]] auto create_system() -> std::pair<RendererContext, SurfaceContext>
{
	auto surface_context = create_surface();
	auto &[surface_system, surface_entity] = surface_context;
	auto registry = create_ref<ecs::Registry>();
	auto stats = create_ref<app::SystemStats>();

	return {
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

		std::move(surface_context),
	};
}

Suite raii = [] {
	Case { "happy path won't throw" } = [&] {
		std::ignore = create_system();
	};

	Case { "happy path has no validation errors" } = [&] {
		auto [renderer, surface] = create_system();
		expect_true(renderer.system.get_stats().empty_diagnosis());
	};

	Case { "unhappy path throws" } = [] {
		auto [surface_system, surface_entity] = create_surface();
		auto empty_registry = create_ref<ecs::Registry>();
		auto empty_entity = ecs::Entity { empty_registry, empty_registry->create_entity() };
		auto registry = create_ref<ecs::Registry>();
		auto stats = create_ref<app::SystemStats>();

		expect_throw([&] {
			std::ignore = System(
			    {
			        .registry = {},
			        .surface_entity = surface_entity,
			        .system_stats = stats,
			    }
			);
		});

		expect_throw([&] {
			std::ignore = System(
			    System::CreateInfo {
			        .registry = surface_entity.get_registry(),
			        .surface_entity = empty_entity,
			        .system_stats = stats,
			    }
			);
		});

		expect_throw([&] {
			std::ignore = System(
			    System::CreateInfo {
			        .registry = surface_entity.get_registry(),
			        .surface_entity = surface_entity,
			        .system_stats = {},
			    }
			);
		});
	};
};
