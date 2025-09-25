#include <ranges>
#include <renderer/vk/context/context.hpp>
#include <renderer/vk/pipeline.hpp>
#include <surface/system.hpp>
#include <test/test.hpp>

using namespace lt;

using std::ignore;
using test::Case;
using test::expect_throw;
using test::expect_true;
using test::Suite;

using renderer::vk::Context;
using renderer::vk::Pipeline;

constexpr auto resolution = math::uvec2 { 800, 600 };

class VkPipelineTest
{
public:
	VkPipelineTest()
	{
		m_registry = create_ref<ecs::Registry>();

		m_surface_system = create_ref<surface::System>(m_registry);

		m_surface_entity = create_scope<ecs::Entity>(m_registry, m_registry->create_entity());
		m_surface_entity->add<surface::SurfaceComponent>(surface::SurfaceComponent::CreateInfo {
		    .title = "",
		    .resolution = resolution,
		});

		m_context = create_ref<Context>(*m_surface_entity, m_stats);
	}

	[[nodiscard]] auto context() -> Ref<Context>
	{
		return m_context;
	}

	[[nodiscard]] auto device() -> VkDevice
	{
		return m_context->device().vk();
	}

private:
	Ref<app::SystemStats> m_stats;

	Ref<ecs::Registry> m_registry;

	Ref<surface::System> m_surface_system;

	Scope<ecs::Entity> m_surface_entity;

	Ref<Context> m_context;
};

Suite raii = [] {
	Case { "happy path won't throw" } = [] {
		auto fixture = VkPipelineTest {};
		std::ignore = Pipeline { { .context = fixture.context() } };
	};

	Case { "unhappy path throws" } = [] {
		expect_throw([] { std::ignore = Pipeline { { .context = nullptr } }; });
	};
};
