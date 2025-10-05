#include <memory/reference.hpp>
#include <renderer/vk/context/surface.hpp>
#include <renderer/vk/debug/messenger.hpp>
#include <renderer/vk/test_utils.hpp>
#include <surface/components.hpp>
#include <surface/system.hpp>
#include <test/test.hpp>

using ::lt::ecs::Entity;
using ::lt::ecs::Registry;
using ::lt::renderer::vk::Surface;
using ::lt::surface::SurfaceComponent;
using ::lt::surface::System;

Suite raii = "surface"_suite = [] {
	Case { "happy path won't throw" } = [&] {
		auto observer = ValidationObserver {};

		auto registry = lt::memory::create_ref<Registry>();
		auto entity = Entity { registry, registry->create_entity() };
		auto surface_system = System(registry);

		entity.add<SurfaceComponent>(SurfaceComponent::CreateInfo {
		    .title = "",
		    .resolution = constants::resolution,
		    .visible = true,
		});

		const auto surface = Surface { entity };
		const auto &[x, y] = surface.get_framebuffer_size();

		expect_eq(x, constants::resolution.x);
		expect_eq(y, constants::resolution.y);
		expect_not_nullptr(surface.vk());
		expect_false(observer.had_any_messages());
	};

	Case { "unhappy path throws" } = [&] {
		auto observer = ValidationObserver {};
		auto registry = lt::memory::create_ref<Registry>();
		auto entity = Entity { registry, registry->create_entity() };

		entity.add<SurfaceComponent>(SurfaceComponent::CreateInfo {
		    .title = "",
		    .resolution = constants::resolution,
		    .visible = true,
		});

		expect_throw([&] { Surface { entity }; });
		expect_false(observer.had_any_messages());
	};
};
