#include <surface/system.hpp>
#include <test/test.hpp>

using namespace lt;
using std::ignore;
using surface::SurfaceComponent;
using surface::System;
using test::Case;
using test::expect_eq;
using test::expect_ne;
using test::expect_not_nullptr;
using test::expect_throw;
using test::Suite;

constexpr auto title = "TestWindow";
constexpr auto width = 800u;
constexpr auto height = 600u;
constexpr auto vsync = true;
constexpr auto visible = false;

class Fixture
{
public:
	[[nodiscard]] auto registry() -> Ref<ecs::Registry>
	{
		return m_registry;
	}

	auto add_surface_component() -> SurfaceComponent &
	{
		auto entity = m_registry->create_entity("");
		return entity.add_component<SurfaceComponent>(SurfaceComponent::CreateInfo {
		    .title = title,
		    .size = { width, height },
		    .vsync = vsync,
		    .visible = visible,
		});
	}

	void check_values(const SurfaceComponent &component)
	{
		expect_ne(std::get<SurfaceComponent::X11NativeHandle>(component.get_native_handle()), 0);
		expect_eq(component.get_size().x, width);
		expect_eq(component.get_size().y, height);
		expect_eq(component.get_title(), title);
		expect_eq(component.is_vsync(), vsync);
		expect_eq(component.is_visible(), visible);
	}

private:
	Ref<ecs::Registry> m_registry = create_ref<ecs::Registry>();
};

Suite raii = [] {
	Case { "happy path won't throw" } = [] {
		auto fixture = Fixture {};
		ignore = System { fixture.registry() };
	};

	Case { "many won't throw" } = [] {
		auto fixture = Fixture {};
		for (auto idx : std::views::iota(0, 100'001))
		{
			ignore = System { fixture.registry() };
		}
	};

	Case { "unhappy path throws" } = [] {
		expect_throw([] { ignore = System { {} }; });

		auto fixture = Fixture {};
		fixture.add_surface_component();
		expect_throw([&] { ignore = System { { fixture.registry() } }; });
	};

	Case { "post construct has correct state" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };
		expect_eq(fixture.registry()->view<SurfaceComponent>()->size(), 0);
	};
};

Suite system_events = [] {
	Case { "on_register won't throw" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };

		system.on_register();
		expect_eq(fixture.registry()->view<SurfaceComponent>().size(), 0);
	};

	Case { "on_unregister won't throw" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };
		system.on_register();

		system.on_unregister();
		expect_eq(fixture.registry()->view<SurfaceComponent>().size(), 0);
	};
};

Suite registry_events = [] {
	Case { "on_construct<SurfaceComponent> initializes component" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };

		const auto &component = fixture.add_surface_component();
		expect_eq(fixture.registry()->view<SurfaceComponent>().size(), 1);
		fixture.check_values(component);
	};

	Case { "on_destrroy<SurfaceComponent> cleans up component" } = [] {
		auto fixture = Fixture {};
		auto system = create_scope<System>(fixture.registry());

		const auto &component = fixture.add_surface_component();
		expect_eq(fixture.registry()->view<SurfaceComponent>().size(), 1);
		fixture.check_values(component);

		system.reset();
		expect_eq(fixture.registry()->view<SurfaceComponent>().size(), 0);
	};
};

Suite tick = [] {
	Case { "ticking on empty registry won't throw" } = [] {
		auto fixture = Fixture {};
		System { fixture.registry() }.tick();
	};

	Case { "ticking on non-empty registry won't throw" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };

		fixture.add_surface_component();
		system.tick();
	};

	Case { "ticking on chaotic registry won't throw" } = [] {
	}
};

Suite property_setters = [] {

};

Suite listeners = [] {
};

Suite fuzzy = [] {
};
