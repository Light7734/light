#include <renderer/vk/context/context.hpp>
#include <renderer/vk/pipeline.hpp>
#include <renderer/vk/test_utils.hpp>
#include <surface/system.hpp>
#include <test/test.hpp>

using namespace lt;

using renderer::vk::Context;
using renderer::vk::Pipeline;

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
		    .resolution = constants::resolution,
		});

		m_context = create_ref<Context>(*m_surface_entity);
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
	Ref<ecs::Registry> m_registry;

	Ref<surface::System> m_surface_system;

	Scope<ecs::Entity> m_surface_entity;

	Ref<Context> m_context;
};

Suite raii = "raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		auto fixture = VkPipelineTest {};
		std::ignore = Pipeline { { .context = fixture.context() } };
	};

	Case { "unhappy path throws" } = [] {
		expect_throw([] { std::ignore = Pipeline { { .context = nullptr } }; });
	};
};
