#include <ecs/entity.hpp>
#include <surface/components.hpp>
#include <surface/requests/surface.hpp>
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

template<class... Ts>
struct overloads: Ts...
{
	using Ts::operator()...;
};


class Fixture
{
public:
	[[nodiscard]] auto registry() -> Ref<ecs::Registry>
	{
		return m_registry;
	}

	auto add_surface_component(
	    SurfaceComponent::CreateInfo info = SurfaceComponent::CreateInfo {
	        .title = title,
	        .resolution = { width, height },
	        .vsync = vsync,
	        .visible = visible,
	    }
	) -> SurfaceComponent &
	{
		auto entity = m_registry->create_entity("");
		return entity.add_component<SurfaceComponent>(info);
	}

	void check_values(const SurfaceComponent &component)
	{
#ifdef LIGHT_PLATFORM_LINUX
		expect_not_nullptr(component.get_native_data().display);
		expect_ne(component.get_native_data().window, 0);
#endif

		expect_eq(component.get_resolution().x, width);
		expect_eq(component.get_resolution().y, height);
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

	Case { "many won't freeze/throw" } = [] {
		auto fixture = Fixture {};
		for (auto idx : std::views::iota(0, 250))
		{
			ignore = System { fixture.registry() };
		}
	};

	Case { "unhappy path throws" } = [] {
		expect_throw([] { ignore = System { {} }; });

		auto fixture = Fixture {};
		fixture.add_surface_component();
		expect_throw([&] { ignore = System { fixture.registry() }; });
	};

	Case { "post construct has correct state" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };
		expect_eq(fixture.registry()->view<SurfaceComponent>()->size(), 0);
	};

	Case { "post destruct has correct state" } = [] {
		auto fixture = Fixture {};
		auto system = create_scope<System>(fixture.registry());

		fixture.add_surface_component();
		expect_eq(fixture.registry()->view<SurfaceComponent>()->size(), 1);

		system.reset();
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

	Case { "unhappy on_construct<SurfaceComponent> throws" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };

		expect_throw([&] { fixture.add_surface_component({ .resolution = { width, 0 } }); });

		expect_throw([&] { fixture.add_surface_component({ .resolution = { 0, height } }); });

		expect_throw([&] {
			fixture.add_surface_component(
			    { .title = "", .resolution = { SurfaceComponent::max_dimension + 1, height } }
			);
		});

		expect_throw([&] {
			fixture.add_surface_component(
			    { .title = "", .resolution = { width, SurfaceComponent::max_dimension + 1 } }
			);
		});

		auto big_str = std::string {};
		big_str.resize(SurfaceComponent::max_title_length + 1);
		expect_throw([&] {
			fixture.add_surface_component({ .title = big_str, .resolution = { width, height } });
		});
	};

	Case { "unhappy on_construct<SurfaceComponent> removes component" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };

		expect_throw([&] { fixture.add_surface_component({ .resolution = { width, 0 } }); });
		expect_eq(fixture.registry()->view<SurfaceComponent>().size(), 0);
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
};

Suite tick_handles_events = [] {
	Case { "ticking clears previous tick's events" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };
		auto &surface = fixture.add_surface_component();

		// flush window-creation events
		system.tick();
		expect_eq(surface.peek_events().size(), 0);

		surface.push_event(surface::MovedEvent({}, {}));
		expect_eq(surface.peek_events().size(), 1);

		surface.push_event(surface::ButtonPressedEvent({}));
		expect_eq(surface.peek_events().size(), 2);

		system.tick();
		expect_eq(surface.peek_events().size(), 0);
	};
};

Suite tick_handles_requests = [] {
	Case { "ticking clears requests" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };
		auto &surface = fixture.add_surface_component();

		constexpr auto title = "ABC";
		constexpr auto position = math::ivec2 { 50, 50 };
		constexpr auto resolution = math::uvec2 { 50, 50 };

		expect_eq(surface.peek_requests().size(), 0);

		surface.push_request(surface::ModifyVisibilityRequest(true));
		expect_eq(surface.peek_requests().size(), 1);
		system.tick();
		expect_eq(surface.peek_requests().size(), 0);

		surface.push_request(surface::ModifyTitleRequest(title));
		expect_eq(surface.peek_requests().size(), 1);

		surface.push_request(surface::ModifyResolutionRequest(resolution));
		surface.push_request(surface::ModifyPositionRequest(position));
		expect_eq(surface.peek_requests().size(), 1 + 2);

		surface.push_request(surface::ModifyVisibilityRequest(false));
		surface.push_request(surface::ModifyVisibilityRequest(true));
		surface.push_request(surface::ModifyVisibilityRequest(false));
		expect_eq(surface.peek_requests().size(), 1 + 2 + 3);

		system.tick();
		expect_eq(surface.peek_requests().size(), 0);

		expect_eq(surface.get_title(), title);
		expect_eq(surface.get_position(), position);
		expect_eq(surface.get_resolution(), resolution);

		log_dbg("EVENT COUNT: {}", surface.peek_events().size());
		for (const auto &event : surface.peek_events())
		{
			const auto visitor = overloads {
				[&](auto event) { log_dbg("event: {}", event.to_string()); },
			};

			std::visit(visitor, event);
		}
	};
};
