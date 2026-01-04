import test.test;
import time;
import test.expects;
import surface.system;
import surface.events;
import surface.requests;
import ecs.registry;
import memory.scope;
import memory.reference;
import logger;
import math.vec2;
import app.system;
import std;

using ::lt::surface::SurfaceComponent;
using ::lt::surface::System;
using ::lt::test::Case;
using ::lt::test::expect_eq;
using ::lt::test::expect_ne;
using ::lt::test::expect_not_nullptr;
using ::lt::test::expect_throw;
using ::lt::test::Suite;
using ::std::ignore;
using ::lt::test::operator""_suite;

[[nodiscard]] auto tick_info() -> lt::app::TickInfo
{
	return {
		.delta_time = std::chrono::milliseconds { 16 },
		.budget = std::chrono::milliseconds { 10 },
		.start_time = std::chrono::steady_clock::now(),
	};
}

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
	[[nodiscard]] auto registry() -> lt::memory::Ref<lt::ecs::Registry>
	{
		return m_registry;
	}

	auto create_component(
	    SurfaceComponent::CreateInfo info = SurfaceComponent::CreateInfo {
	        .title = title,
	        .resolution = { width, height },
	        .vsync = vsync,
	        .visible = visible,
	    }
	) -> std::optional<SurfaceComponent *>
	{
		auto entity = m_registry->create_entity();
		m_system.create_surface_component(entity, info);

		return &m_registry->get<SurfaceComponent>(entity);
	}

	void check_values(SurfaceComponent *component)
	{
#ifdef LIGHT_PLATFORM_LINUX
		expect_not_nullptr(component->get_native_data().display);
		expect_not_nullptr(component->get_native_data().surface);
#endif

		expect_eq(component->get_resolution().x, width);
		expect_eq(component->get_resolution().y, height);
		expect_eq(component->get_title(), title);
		expect_eq(component->is_vsync(), vsync);
		expect_eq(component->is_visible(), visible);
	}

private:
	lt::memory::Ref<lt::ecs::Registry> m_registry = lt::memory::create_ref<lt::ecs::Registry>();

	System m_system { m_registry };
};


Suite raii = "raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };

		auto timer = lt::time::Timer {};
		lt::log::trace("Ticking for 3 seconds...");
		while (timer.elapsed_time() < std::chrono::seconds { 3 })
		{
			system.tick({});
		}

		lt::log::trace("Three seconds passed, quitting...");
	};


	// Case { "many won't freeze/throw" } = [] {
	// 	auto fixture = Fixture {};
	// 	for (auto idx : std::views::iota(0, 250))
	// 	{
	// 		ignore = System { fixture.registry() };
	// 	}
	// };
	//
	// Case { "unhappy path throws" } = [] {
	// 	expect_throw([] { ignore = System { {} }; });
	// };
	//
	// Case { "post construct has correct state" } = [] {
	// 	auto fixture = Fixture {};
	// 	auto system = System { fixture.registry() };
	// 	expect_eq(fixture.registry()->view<SurfaceComponent>().get_size(), 0);
	// };
	//
	// Case { "post destruct has correct state" } = [] {
	// 	auto fixture = Fixture {};
	// 	auto system = lt::memory::create_scope<System>(fixture.registry());
	//
	// 	fixture.create_component();
	// 	expect_eq(fixture.registry()->view<SurfaceComponent>().get_size(), 1);
	//
	// 	system.reset();
	// 	expect_eq(fixture.registry()->view<SurfaceComponent>().get_size(), 0);
	// };
};

// Suite system_events = "system_events"_suite = [] {
// 	Case { "on_register won't throw" } = [] {
// 		auto fixture = Fixture {};
// 		auto system = System { fixture.registry() };
//
// 		system.on_register();
// 		expect_eq(fixture.registry()->view<SurfaceComponent>().get_size(), 0);
// 	};
//
// 	Case { "on_unregister won't throw" } = [] {
// 		auto fixture = Fixture {};
// 		auto system = System { fixture.registry() };
//
// 		system.on_register();
// 		system.on_unregister();
// 		expect_eq(fixture.registry()->view<SurfaceComponent>().get_size(), 0);
// 	};
// };
//
// Suite registry_events = "registry_events"_suite = [] {
// 	Case { "on_construct<SurfaceComponent> initializes component" } = [] {
// 		auto fixture = Fixture {};
//
// 		const auto &component = fixture.create_component();
// 		expect_eq(fixture.registry()->view<SurfaceComponent>().get_size(), 1);
// 		fixture.check_values(*component);
// 	};
//
// 	Case { "unhappy on_construct<SurfaceComponent> throws" } = [] {
// 		auto fixture = Fixture {};
// 		auto system = System { fixture.registry() };
//
// 		expect_throw([&] { fixture.create_component({ .resolution = { width, 0 } }); });
//
// 		expect_throw([&] { fixture.create_component({ .resolution = { 0, height } }); });
//
// 		expect_throw([&] {
// 			fixture.create_component(
// 			    { .title = "", .resolution = { SurfaceComponent::max_dimension + 1, height } }
// 			);
// 		});
//
// 		expect_throw([&] {
// 			fixture.create_component(
// 			    { .title = "", .resolution = { width, SurfaceComponent::max_dimension + 1 } }
// 			);
// 		});
//
// 		auto big_str = std::string {};
// 		big_str.resize(SurfaceComponent::max_title_length + 1);
// 		expect_throw([&] {
// 			fixture.create_component({ .title = big_str, .resolution = { width, height } });
// 		});
// 	};
//
// 	Case { "unhappy on_construct<SurfaceComponent> removes component" } = [] {
// 		auto fixture = Fixture {};
// 		auto system = System { fixture.registry() };
//
// 		expect_throw([&] { fixture.create_component({ .resolution = { width, 0 } }); });
// 		expect_eq(fixture.registry()->view<SurfaceComponent>().get_size(), 0);
// 	};
//
// 	Case { "on_destrroy<SurfaceComponent> cleans up component" } = [] {
// 		auto fixture = Fixture {};
// 		auto system = lt::memory::create_scope<System>(fixture.registry());
//
// 		const auto &component = fixture.create_component();
// 		expect_eq(fixture.registry()->view<SurfaceComponent>().get_size(), 1);
// 		fixture.check_values(*component);
//
// 		system.reset();
// 		expect_eq(fixture.registry()->view<SurfaceComponent>().get_size(), 0);
// 	};
// };
//
// Suite tick = "tick"_suite = [] {
// 	Case { "ticking on empty registry won't throw" } = [] {
// 		auto fixture = Fixture {};
// 		System { fixture.registry() }.tick(tick_info());
// 	};
//
// 	Case { "ticking on non-empty registry won't throw" } = [] {
// 		auto fixture = Fixture {};
// 		auto system = System { fixture.registry() };
//
// 		fixture.create_component();
// 		system.tick(tick_info());
// 	};
// };
//
// Suite tick_handles_events = "tick_handles_events"_suite = [] {
// 	Case { "ticking clears previous tick's events" } = [] {
// 		auto fixture = Fixture {};
// 		auto system = System { fixture.registry() };
// 		auto &surface = **fixture.create_component();
//
// 		// flush window-creation events
// 		system.tick(tick_info());
// 		expect_eq(surface.peek_events().size(), 0);
//
// 		surface.push_event(lt::surface::MovedEvent({}, {}));
// 		expect_eq(surface.peek_events().size(), 1);
//
// 		surface.push_event(lt::surface::ButtonPressedEvent({}));
// 		expect_eq(surface.peek_events().size(), 2);
//
// 		system.tick(tick_info());
// 		expect_eq(surface.peek_events().size(), 0);
// 	};
// };
//
// Suite tick_handles_requests = "tick_handles_requests"_suite = [] {
// 	Case { "ticking clears requests" } = [] {
// 		auto fixture = Fixture {};
// 		auto system = System { fixture.registry() };
// 		auto &surface = **fixture.create_component();
//
// 		constexpr auto title = "ABC";
// 		constexpr auto position = lt::math::ivec2 { 50, 50 };
// 		constexpr auto resolution = lt::math::uvec2 { 50, 50 };
//
// 		expect_eq(surface.peek_requests().size(), 0);
//
// 		surface.push_request(lt::surface::ModifyVisibilityRequest(true));
// 		expect_eq(surface.peek_requests().size(), 1);
// 		system.tick(tick_info());
// 		expect_eq(surface.peek_requests().size(), 0);
//
// 		surface.push_request(lt::surface::ModifyTitleRequest(title));
// 		expect_eq(surface.peek_requests().size(), 1);
//
// 		surface.push_request(lt::surface::ModifyResolutionRequest(resolution));
// 		surface.push_request(lt::surface::ModifyPositionRequest(position));
// 		expect_eq(surface.peek_requests().size(), 1 + 2);
//
// 		surface.push_request(lt::surface::ModifyVisibilityRequest(false));
// 		surface.push_request(lt::surface::ModifyVisibilityRequest(true));
// 		surface.push_request(lt::surface::ModifyVisibilityRequest(false));
// 		expect_eq(surface.peek_requests().size(), 1 + 2 + 3);
//
// 		system.tick(tick_info());
// 		expect_eq(surface.peek_requests().size(), 0);
//
// 		expect_eq(surface.get_title(), title);
// 		expect_eq(surface.get_position(), position);
// 		expect_eq(surface.get_resolution(), resolution);
//
// 		lt::log::debug("EVENT COUNT: {}", surface.peek_events().size());
// 		for (const auto &event : surface.peek_events())
// 		{
// 			const auto visitor = overloads {
// 				[&](auto event) { lt::log::debug("event: {}", event.to_string()); },
// 			};
//
// 			std::visit(visitor, event);
// 		}
// 	};
// };
