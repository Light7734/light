#include <ranges>
#include <renderer/vk/context/device.hpp>
#include <renderer/vk/context/surface.hpp>
#include <surface/components.hpp>
#include <surface/system.hpp>
#include <test/test.hpp>

using namespace lt;
using renderer::vk::Device;
using renderer::vk::Surface;
using test::Case;
using test::expect_ne;
using test::expect_throw;
using test::Suite;

constexpr auto resolution = math::uvec2 { 800u, 600u };

Suite raii = "device_raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		auto registry = create_ref<ecs::Registry>();
		auto surface_system = surface::System { registry };
		auto entity = ecs::Entity { registry, registry->create_entity() };
		entity.add<surface::SurfaceComponent>(surface::SurfaceComponent::CreateInfo {
		    .resolution = resolution,
		    .visible = true,
		});

		auto surface = Surface { entity };
		auto device = Device { surface };
	};

	Case { "many won't freeze/throw" } = [] {
		auto registry = create_ref<ecs::Registry>();
		auto surface_system = surface::System { registry };
		auto entity = ecs::Entity { registry, registry->create_entity() };
		entity.add<surface::SurfaceComponent>(surface::SurfaceComponent::CreateInfo {
		    .resolution = resolution,
		    .visible = true,
		});
		auto surface = Surface { entity };

		// it takes a loong time to initialize vulkan + setup device
		for (auto idx : std::views::iota(0, 10))
		{
			Device { surface };
		}
	};

	Case { "unhappy path throws" } = [] {
		auto registry = create_ref<ecs::Registry>();
		auto surface_system = surface::System { registry };
		auto entity = ecs::Entity { registry, registry->create_entity() };
		entity.add<surface::SurfaceComponent>(surface::SurfaceComponent::CreateInfo {
		    .resolution = resolution,
		    .visible = true,
		});

		auto moved_out_surface = Surface { entity };
		auto surface = std::move(moved_out_surface);

		expect_throw([&] { Device { moved_out_surface }; });
	};

	Case { "post construct has correct state" } = [] {
		auto registry = create_ref<ecs::Registry>();
		auto surface_system = surface::System { registry };
		auto entity = ecs::Entity { registry, registry->create_entity() };
		entity.add<surface::SurfaceComponent>(surface::SurfaceComponent::CreateInfo {
		    .resolution = resolution,
		    .visible = true,
		});

		auto surface = Surface { entity };
		auto device = Device { surface };

		for (auto &index : device.get_family_indices())
		{
			expect_ne(index, VK_QUEUE_FAMILY_IGNORED);
		}
		test::expect_true(device.physical());
		test::expect_true(device.vk());
	};

	Case { "post destruct has correct state" } = [] {
		auto registry = create_ref<ecs::Registry>();
		auto surface_system = surface::System { registry };
		auto entity = ecs::Entity { registry, registry->create_entity() };
		entity.add<surface::SurfaceComponent>(surface::SurfaceComponent::CreateInfo {
		    .resolution = resolution,
		    .visible = true,
		});

		auto surface = Surface { entity };

		{
			auto device = Device { surface };
		}
	};
};
