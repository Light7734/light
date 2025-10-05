#include <memory/reference.hpp>
#include <memory/scope.hpp>
#include <ranges>
#include <renderer/interface/context.hpp>
#include <renderer/vk/context/context.hpp>
#include <renderer/vk/context/surface.hpp>
#include <renderer/vk/debug/messenger.hpp>
#include <surface/components.hpp>
#include <surface/system.hpp>
#include <test/test.hpp>

using lt::renderer::API;
using lt::renderer::IContext;
using ::lt::test::Case;
using ::lt::test::expect_eq;
using ::lt::test::expect_false;
using ::lt::test::expect_not_nullptr;
using ::lt::test::expect_throw;
using ::lt::test::expect_true;
using ::lt::test::Suite;
using ::std::ignore;

namespace constants {

constexpr auto resolution = lt::math::uvec2 { 800u, 600u };

}


class Fixture
{
public:
	Fixture()
	    : m_registry(lt::memory::create_ref<lt::ecs::Registry>())
	    , m_surface_system(lt::memory::create_scope<lt::surface::System>(m_registry))
	    , m_surface_entity(m_registry, m_registry->create_entity())
	{
	}

	auto get_surface_entity() -> lt::ecs::Entity
	{
		return m_surface_entity;
	}

private:
	lt::memory::Ref<lt::ecs::Registry> m_registry;
	lt::memory::Scope<lt::surface::System> m_surface_system;
	lt::ecs::Entity m_surface_entity;
};

Suite raii = "context_raii"_suite = [] {
	Case { "Happy path won't throw" } = [] {
		auto fixture = Fixture {};
		IContext::create(API::Vulkan, fixture.get_surface_entity());
	};
};
