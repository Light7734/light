#if defined(LIGHT_PLATFORM_LINUX)
#elif defined(LIGHT_PLATFORM_WINDOWS)
	#include <Windows.h>
	#include <Winuser.h>

#else
	#error "Unsupported platform"
#endif

import test;
import time;
import input.codes;
import logger;
import surface.system;
import surface.events;
import surface.requests;
import ecs.registry;
import memory.scope;
import memory.reference;
import math.vec2;
import app.system;

using ::lt::surface::SurfaceComponent;
using ::lt::surface::System;

[[nodiscard]] auto tick_info() -> lt::app::TickInfo
{
	return {
		.delta_time = std::chrono::milliseconds { 16 },
		.budget = std::chrono::milliseconds { 10 },
		.start_time = std::chrono::steady_clock::now(),
	};
}


// void simulate_key_down(lt::surface::SurfaceComponent &surface, lt::Key key)
// {
// #if defined(LIGHT_PLATFORM_LINUX)
// #elif defined(LIGHT_PLATFORM_WINDOWS)
// #endif
// }
//
// void simulate_key_up(lt::Key key)
// {
// #if defined(LIGHT_PLATFORM_LINUX)
// #elif defined(LIGHT_PLATFORM_WINDOWS)
// #endif
// }

constexpr auto title = "TestWindow";
constexpr auto width = 800u;
constexpr auto height = 600u;
constexpr auto position_x = 100;
constexpr auto position_y = 200;
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
	        .position = { position_x, position_y },
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
	Case { "happy paths" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };
	};

	Case { "unhappy paths" } = [] {
		expect_throw([] { ignore = System { {} }; });
	};

	Case { "many" } = [] {
		auto fixture = Fixture {};
		for (auto idx : std::views::iota(0, 250))
		{
			ignore = idx;
			ignore = System { fixture.registry() };
		}
	};

	Case { "post construct has correct state" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };
		expect_eq(fixture.registry()->view<SurfaceComponent>().get_size(), 0);
	};

	Case { "post destruct has correct state" } = [] {
		auto fixture = Fixture {};
		auto system = lt::memory::create_scope<System>(fixture.registry());

		fixture.create_component();
		expect_eq(fixture.registry()->view<SurfaceComponent>().get_size(), 1);

		system.reset();
		expect_eq(fixture.registry()->view<SurfaceComponent>().get_size(), 0);
	};
};

Suite system_events = "system_events"_suite = [] {
	Case { "on_register won't throw" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };

		system.on_register();
		expect_eq(fixture.registry()->view<SurfaceComponent>().get_size(), 0);
	};

	Case { "on_unregister won't throw" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };

		system.on_register();
		system.on_unregister();
		expect_eq(fixture.registry()->view<SurfaceComponent>().get_size(), 0);
	};
};

Suite registry_events = "registry_events"_suite = [] {
	Case { "on_construct initializes component" } = [] {
		auto fixture = Fixture {};

		const auto &component = fixture.create_component();
		expect_eq(fixture.registry()->view<SurfaceComponent>().get_size(), 1);
		fixture.check_values(*component);
	};

	Case { "unhappy on_construct throws" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };

		expect_throw([&] { fixture.create_component({ .resolution = { width, 0 } }); });

		expect_throw([&] { fixture.create_component({ .resolution = { 0, height } }); });

		expect_throw([&] {
			fixture.create_component(
			    { .title = "", .resolution = { SurfaceComponent::max_dimension + 1, height } }
			);
		});

		expect_throw([&] {
			fixture.create_component(
			    { .title = "", .resolution = { width, SurfaceComponent::max_dimension + 1 } }
			);
		});

		auto big_str = std::string {};
		big_str.resize(SurfaceComponent::max_title_length + 1);
		expect_throw([&] {
			fixture.create_component({ .title = big_str, .resolution = { width, height } });
		});
	};

	Case { "unhappy on_construct removes component" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };

		expect_throw([&] { fixture.create_component({ .resolution = { width, 0 } }); });
		expect_eq(fixture.registry()->view<SurfaceComponent>().get_size(), 0);
	};

	Case { "on_destroy cleans up component" } = [] {
		auto fixture = Fixture {};
		auto system = lt::memory::create_scope<System>(fixture.registry());

		const auto &component = fixture.create_component();
		expect_eq(fixture.registry()->view<SurfaceComponent>().get_size(), 1);
		fixture.check_values(*component);

		system.reset();
		expect_eq(fixture.registry()->view<SurfaceComponent>().get_size(), 0);
	};
};

Suite tick = "ticking"_suite = [] {
	Case { "on empty registry won't throw" } = [] {
		auto fixture = Fixture {};
		System { fixture.registry() }.tick(tick_info());
	};

	Case { "on non-empty registry won't throw" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };

		fixture.create_component();
		system.tick(tick_info());
	};

	Case { "clears previous tick's events" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };
		auto &surface = **fixture.create_component();

		// flush window-creation events
		system.tick(tick_info());
		expect_eq(surface.peek_events().size(), 0);

		surface.push_event(lt::surface::MovedEvent({}, {}));
		expect_eq(surface.peek_events().size(), 1);

		surface.push_event(lt::surface::KeyPressedEvent({}));
		expect_eq(surface.peek_events().size(), 2);

		system.tick(tick_info());
		expect_eq(surface.peek_events().size(), 0);
	};

	Case { "clears requests" } = [] {
		auto fixture = Fixture {};
		auto system = System { fixture.registry() };
		auto &surface = **fixture.create_component();

		constexpr auto position = lt::math::vec2_i32 { 50, 50 };
		constexpr auto resolution = lt::math::vec2_u32 { width, height };

		expect_eq(surface.peek_requests().size(), 0);

		surface.push_request(lt::surface::ModifyVisibilityRequest(true));
		expect_eq(surface.peek_requests().size(), 1);
		system.tick(tick_info());
		expect_eq(surface.peek_requests().size(), 0);

		surface.push_request(lt::surface::ModifyTitleRequest(title));
		expect_eq(surface.peek_requests().size(), 1);

		surface.push_request(lt::surface::ModifyResolutionRequest(resolution));
		surface.push_request(lt::surface::ModifyPositionRequest(position));
		expect_eq(surface.peek_requests().size(), 1 + 2);

		surface.push_request(lt::surface::ModifyVisibilityRequest(false));
		surface.push_request(lt::surface::ModifyVisibilityRequest(true));
		surface.push_request(lt::surface::ModifyVisibilityRequest(false));
		expect_eq(surface.peek_requests().size(), 1 + 2 + 3);

		system.tick(tick_info());
		expect_eq(surface.peek_requests().size(), 0);

		expect_eq(surface.get_title(), title);
		expect_eq(surface.get_position(), position);
		expect_eq(surface.get_resolution(), resolution);
	};
};

#if defined(LIGHT_PLATFORM_WINDOWS)

Suite windows_window_proc = "windows_window_proc"_suite = [] {
	auto fixture = Fixture {};
	auto system = System { fixture.registry() };
	auto &surface = **fixture.create_component();
	auto [hwnd] = surface.get_native_data();
	const auto &events = surface.peek_events();

	system.tick({});
	Case { "WM_SETFOCUS" } = [&] {
		expect_eq(events.size(), 0u);
		::SendMessage(hwnd, WM_SETFOCUS, {}, {});
		expect_eq(events.size(), 1u);

		ignore = std::get<lt::surface::GainFocusEvent>(events.front());
	};

	system.tick({});
	Case { "WM_KILLFOCUS" } = [&] {
		expect_eq(events.size(), 0u);
		::SendMessage(hwnd, WM_KILLFOCUS, {}, {});
		expect_eq(events.size(), 1u);

		ignore = std::get<lt::surface::LostFocusEvent>(events.front());
	};

	system.tick({});
	Case { "WM_SIZE" } = [&] {
		const auto new_width = width + 50;
		const auto new_height = height + 60;

		expect_eq(events.size(), 0u);
		::SendMessage(hwnd, WM_SIZE, {}, MAKELPARAM(new_width, new_height));
		expect_eq(events.size(), 1u);

		const auto &event = std::get<lt::surface::ResizedEvent>(events.front());
		expect_eq(event.get_size().x, new_width);
		expect_eq(event.get_size().y, new_height);

		expect_eq(surface.get_resolution().x, new_width);
		expect_eq(surface.get_resolution().y, new_height);
	};

	system.tick({});
	Case { "WM_MOVE" } = [&] {
		const auto new_x = position_x + 120;
		const auto new_y = position_y + 150;

		expect_eq(events.size(), 0u);
		::SendMessage(hwnd, WM_MOVE, {}, MAKELPARAM(new_x, new_y));
		expect_eq(events.size(), 1u);

		const auto &event = std::get<lt::surface::MovedEvent>(events.front());
		expect_eq(event.get_position().x, new_x);
		expect_eq(event.get_position().y, new_y);

		expect_eq(surface.get_position().x, new_x);
		expect_eq(surface.get_position().y, new_y);
	};

	system.tick({});
	Case { "WM_MOUSEWHEEL" } = [&] {
	};

	system.tick({});
	Case { "WM_LBUTTONDOWN" } = [&] {
	};

	system.tick({});
	Case { "WM_LBUTTONUP" } = [&] {
	};

	system.tick({});
	Case { "WM_RBUTTONDOWN" } = [&] {
	};

	system.tick({});
	Case { "WM_RBUTTONUP" } = [&] {
	};

	system.tick({});
	Case { "WM_MBUTTONDOWN" } = [&] {
	};

	system.tick({});
	Case { "WM_MBUTTONUP" } = [&] {
	};

	system.tick({});
	Case { "WM_XBUTTONDOWN" } = [&] {
	};

	system.tick({});
	Case { "WM_XBUTTONUP" } = [&] {
	};

	system.tick({});
	Case { "WM_KEYDOWN" } = [&] {
		expect_eq(events.size(), 0u);
		::SendMessage(hwnd, WM_KEYDOWN, System::to_native_key(lt::Key::escape), {});
		expect_eq(events.size(), 1u);

		const auto &event = std::get<lt::surface::KeyPressedEvent>(events.front());
		expect_eq(event.get_key(), lt::Key::escape);
	};

	system.tick({});
	Case { "WM_KEYUP" } = [&] {
	};

	system.tick({});
	Case { "WM_CLOSE" } = [&] {
	};

	system.tick({});
	Case { "WM_DESTROY" } = [&] {
	};
};

#endif
