import preliminary;
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

constexpr auto title = "TestWindow";
constexpr auto width = 800u;
constexpr auto height = 600u;
constexpr auto vsync = true;
constexpr auto visible = false;

auto main() -> i32
try
{
	auto registry = lt::memory::create_ref<lt::ecs::Registry>();
	auto system = lt::surface::System { registry };

	auto entity = registry->create_entity();

	system.create_surface_component(
	    entity,
	    lt::surface::SurfaceComponent::CreateInfo {
	        .title = title,
	        .resolution = { width, height },
	        .vsync = vsync,
	        .visible = visible,
	    }
	);

	auto timer = lt::time::Timer {};
	lt::log::trace("Ticking for 3 seconds...");
	while (timer.elapsed_time() < std::chrono::seconds { 30 })
	{
		system.tick({});
	}
	lt::log::trace("Three seconds passed, quitting...");
}
catch (const std::exception &exp)
{
	lt::log::critical("Aborting due to uncaught std::exception:");
	lt::log::critical("\twhat: {}", exp.what());
}
catch (...)
{
	lt::log::critical("Aborting due to uncaught non std::exception!");
}
